#include "pgsnmpd.h"
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/library/snmp_assert.h>
#include <time.h>
#include "customquery.h"
#include "query_reader.h"

    /* TODO: if this works, move it to pgsnmpd.h */
#define CQ_MAX_LEN   255
/* TODO: change this when we support multiple connections */
const int pgsnmpdConnID = 1;
/* TODO: change this when we support row slices in rdbmsDbTable */
const int rdbmsDbIndex = 1;

char *custom_query_config_file = NULL;

/* This makes it easier to account for rdbmsDbIndex and pgsnmpdConnID */
const int extra_idx_count = 2;

    /*
     * Note: this code uses net-snmp containers. See
     * http://net-snmp.sourceforge.net/wiki/index.php/Containers for a helpful
     * reference on the subject
     */

oid *
parse_oid(const char *oid_str_orig, int *oid_len) {
    int len = strlen(oid_str_orig), i;
    char *a, *b, *oid_str;
    oid *result;

    oid_str = strdup((char *)oid_str_orig);
    if (oid_str == NULL) {
        snmp_log(LOG_ERR, "Couldn't allocate copy of OID string\n");
        exit(1);
    }
    a = oid_str;

    result = malloc(len * sizeof(oid));
    if (result == NULL) {
        snmp_log(LOG_ERR, "Couldn't allocate array of %d OIDs\n", *oid_len);
        exit(1);
    }
    i = 0;

    a = oid_str;
    *oid_len = 0;
    while (a - oid_str < len) {
        b = strpbrk(a, ".");
        if (b == NULL) {
            result[i] = atoi(a);
            (*oid_len)++;
            break;
        }
        else {
            *b = '\0';
            result[i++] = atoi(a);
            a = b+1;
            (*oid_len)++;
        }
    }
    free(oid_str);
    return result;
}

typedef struct cust_query_row {
    netsnmp_index row_index;
    oid *myoids;
    pgsnmpd_query *query;
    int rownum;
} cust_query_row;

pgsnmpd_query *head;

pgsnmpd_query *read_custom_queries(void);
void free_query(pgsnmpd_query *query);
void fill_query_column_types(pgsnmpd_query *query);
void fill_query_container(pgsnmpd_query *query);

int custom_query_get_value(
            netsnmp_request_info *request,
            netsnmp_index *item,
            netsnmp_table_request_info *table_info );

int run_query(pgsnmpd_query *query);
int set_val_from_string(netsnmp_variable_list *var, u_char type, char *val);

/* 
 * Frees memory associated with an allocated (or partially allocated)
 * pgsnmpd_query structure, and all such structures following it in the 
 * query list
*/
void free_query(pgsnmpd_query *query) {
    if (query == NULL) return;
    if (query->table_name != NULL) free(query->table_name);
    if (query->query_text != NULL) free(query->query_text);
    if (query->table_oid  != NULL) free(query->table_oid);
    if (query->types      != NULL) free(query->types);
    if (query->result     != NULL) PQclear(query->result);
    if (query->next       != NULL) free_query(query->next);
    free(query);
}

/* Allocates a pgsnmpd_query struct */
pgsnmpd_query *
alloc_custom_query(char *table_name, char *query_text, oid *table_oid, int oid_len) {
    pgsnmpd_query *query;
    int i;

    query = malloc(sizeof(pgsnmpd_query));
    if (query == NULL) return NULL;
    query->result = NULL;
    query->next = NULL;
    query->last_refresh = 0;
    query->cache_timeout = -1;
    query->my_handler = NULL;
    query->typeslen = 0;

    i = strnlen(table_name, CQ_MAX_LEN);
    query->table_name = strndup(table_name, i);
    if (query->table_name == NULL) {
        free_query(query);
        return NULL;
    }

    i = strnlen(query_text, CQ_MAX_LEN);
    query->query_text = strndup(query_text, i);
    if (query->query_text == NULL) {
        free_query(query);
        return NULL;
    }

    query->table_oid = malloc(sizeof(oid) * oid_len);
    if (query->table_oid == NULL) {
        free_query(query);
        return NULL;
    }
    for (i = 0; i < oid_len; i++) {
        query->table_oid[i] = table_oid[i];
    }
    query->oid_len = oid_len;

    return query;
}

int run_query(pgsnmpd_query *query) {
    /* TODO: remember to destroy all old rows when updating query. */
    time_t curtime;

    if (query == NULL) return -1;
    if (PQstatus(dbconn) != CONNECTION_OK) 
        return -1;
    if (query->result != NULL)
        PQclear(query->result);

    query->result = PQexec(dbconn, query->query_text);
    if (PQresultStatus(query->result) != PGRES_TUPLES_OK) {
        snmp_log(LOG_ERR, "Failed to run query \"%s\"\n", query->query_text);
        PQclear(query->result);
        return -1;
    }
    curtime = time(NULL);
    query->last_refresh = curtime;
    query->colcount = PQnfields(query->result);
    query->rowcount = PQntuples(query->result);

    return 1;
}

void fill_query_column_types(pgsnmpd_query *query)
{
    int i;
    Oid type;  /* NB! PostgreSQL's Oid, not Net-SNMP's oid */
    PGresult *res;
    const char *values[1];
    char param[10];
    
    /* This translates SQL types to SNMP types, as follows:
     * Conversions for these four types are obvious
     * ASN_INTEGER
     * ASN_FLOAT
     * ASN_BOOLEAN
     * ASN_OBJECT_ID
     * 
     * Everything else becomes a string:
     * ASN_OCTET_STR
     * 
     * Perhaps one day we'll also use ASN_DOUBLE
     */

    if (query->result == NULL)
        return;

    values[0] = param;

    for (i = 0; i < query->colcount; i++) {
        if (query->types[i] != 255) {
            continue;
        }
        type = PQftype(query->result, i);
        /* 
         * TODO: query pg_type table (including pg_type.h to use builtin
         * constants got all kinds of errors I'd rather not deal with
         */
        sprintf(param, "%d", type);
        res = PQexecPrepared(dbconn, "TYPEQUERY", 1, values, NULL, NULL, 0);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
            snmp_log(LOG_ERR, "Couldn't determine column type\n");
        else {
            switch (atoi(PQgetvalue(res, 0, 0))) {
                case 0:
                    query->types[i] = ASN_INTEGER;
                    break;
                case 1:
                    query->types[i] = ASN_FLOAT;
                    break;
                case 2: 
                    query->types[i] = ASN_BOOLEAN;
                    break;
                case 3: 
                    query->types[i] = ASN_OCTET_STR;
                    break;
                default: /* If we get here, it's because the TYPEQUERY is b0rken */
                    snmp_log(LOG_ERR, "Unknown column type translation. This is a bug.\n");
            }
        }
        PQclear(res);
    }
}

void
init_types_array(u_char *types, int start, int end) {
    int i = (start < 0 ? 0 : start);

    for (; i <= end; i++)
        types[i] = 255;
}

/* General initialization */
void init_custom_queries(void)
{
    netsnmp_table_registration_info *table_info;
    pgsnmpd_query *curquery;
    int i;
    PGresult *res;

    if (custom_query_config_file == NULL) 
        return;

    /*
        ASN_INTEGER = 0
        ASN_FLOAT = 1
        ASN_BOOLEAN = 2
        ASN_OCTET_STR = 3
    */

    res = PQprepare(dbconn, "TYPEQUERY", 
        "SELECT CASE "
            "WHEN typname LIKE 'int%' OR typname = 'xid' OR typname = 'oid'"
                "THEN 0 "
            "WHEN typname LIKE 'float%' THEN 1 "
            "WHEN typname = 'bool' THEN 2 "
            "ELSE 3 "
        "END "
        "FROM pg_catalog.pg_type WHERE oid = $1", 1, NULL);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        snmp_log(LOG_ERR, "Failed to prepare statement (error: %s)\n", PQresStatus(PQresultStatus(res)));
        return;
    }
    PQclear(res);

    head = parse_config(custom_query_config_file);
    if (head == NULL) {
        snmp_log(LOG_INFO, "No custom queries initialized\n");
        return;
    }

    for (curquery = head; curquery != NULL; curquery = curquery->next) {
        run_query(curquery);
        if (curquery->typeslen < curquery->colcount)
            curquery->types = realloc(curquery->types, sizeof(u_char) * curquery->colcount);
        if (curquery->types == NULL) {
            snmp_log(LOG_ERR, "Memory allocation problem");
            return;
        }
        init_types_array(curquery->types, curquery->typeslen, curquery->colcount);
        fill_query_column_types(curquery);
        if (curquery->my_handler) {
            snmp_log(LOG_ERR,
                "init_custom_queries called again for query %s\n",
                curquery->table_name);
            return;
        }

        memset(&(curquery->cb), 0x00, sizeof(curquery->cb));

        /** create the table structure itself */
        snmp_log(LOG_INFO, "Initializing table name %s\n", curquery->table_name);
        table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
        curquery->my_handler = netsnmp_create_handler_registration(
            curquery->table_name,
            netsnmp_table_array_helper_handler,
            curquery->table_oid,
            curquery->oid_len,
            HANDLER_CAN_RONLY
        );

        if (!curquery->my_handler || !table_info) {
            snmp_log(LOG_ERR, "malloc failed in init_custom_queries\n");
            return; /** mallocs failed */
        }

        netsnmp_table_helper_add_index(table_info, ASN_INTEGER); /* pgsnmpdConnID */
        netsnmp_table_helper_add_index(table_info, ASN_INTEGER); /* rdbmsDbIndex */
        for (i = 0; i < curquery->num_indexes; i++)
            netsnmp_table_helper_add_index(table_info, curquery->types[i]);

        table_info->min_column = curquery->min_colnum;
        table_info->max_column = curquery->colcount;

        curquery->cb.get_value = custom_query_get_value;
        curquery->cb.container = netsnmp_container_find("table_container");

        DEBUGMSGTL(("init_custom_queries",
                    "Registering table for query "
                    "as a table array\n"));
        switch (netsnmp_table_container_register(curquery->my_handler,
                    table_info, &curquery->cb,
                    curquery->cb.container, 1)) {
            case MIB_REGISTRATION_FAILED:
                snmp_log(LOG_INFO, "Failed to register table %s\n", curquery->table_name);
                break;
            case MIB_DUPLICATE_REGISTRATION:
                snmp_log(LOG_INFO, "Duplicate registration for table %s\n", curquery->table_name);
                break;
            case MIB_REGISTERED_OK:
                DEBUGMSGTL(("init_custom_queries",
                            "Successfully registered table %s\n", curquery->table_name));
                break;
            default:
                snmp_log(LOG_INFO, "Unknown registration result for table %s\n", curquery->table_name);
        }

        /* Having set everything up, fill the table's container with data */
        fill_query_container(curquery);
    }
    snmp_log(LOG_DEBUG, "Finished intializing queries\n");
}

void fill_query_container(pgsnmpd_query *query)
{
    /* TODO: Make this work */
    cust_query_row *row;
    int i, j, string_idx_count, string_idx_len;
    netsnmp_variable_list var_rdbmsDbIndex, var_pgsnmpdConnID, *var_otherIndexes;
    int err = SNMP_ERR_NOERROR;
    char *val;

    memset( &var_pgsnmpdConnID, 0x00, sizeof(var_pgsnmpdConnID) );
    var_pgsnmpdConnID.type = ASN_INTEGER;
    memset( &var_rdbmsDbIndex, 0x00, sizeof(var_rdbmsDbIndex) );
    var_rdbmsDbIndex.type = ASN_INTEGER;

    var_otherIndexes = malloc(sizeof(netsnmp_variable_list) * query->num_indexes);
    if (var_otherIndexes == NULL) {
        snmp_log(LOG_ERR, "Memory allocation error\n");
        return;
    }
    memset(var_otherIndexes, 0, sizeof(netsnmp_variable_list) * query->num_indexes);

    string_idx_count = 0;
    for (i = 0; i < query->num_indexes; i++) {
        if (i < query->num_indexes - 1)
            var_otherIndexes[i].next_variable = &var_otherIndexes[i+1];
        var_otherIndexes[i].type = query->types[i];
        if (query->types[i] == ASN_OCTET_STR)
            string_idx_count++;
    }

    var_pgsnmpdConnID.next_variable    = &var_rdbmsDbIndex;
    var_rdbmsDbIndex.next_variable     = var_otherIndexes;

    snmp_set_var_typed_value(&var_rdbmsDbIndex, ASN_INTEGER, (u_char *) &rdbmsDbIndex, sizeof(int));
    snmp_set_var_typed_value(&var_pgsnmpdConnID, ASN_INTEGER, (u_char *) &pgsnmpdConnID, sizeof(int));

    for (i = 0; i < query->rowcount; i++) {
        string_idx_len = 0;
        for (j = 0; j < query->num_indexes; j++) {
            val = PQgetvalue(query->result, i, j);
            /* TODO: Floats and OIDs also need more than the usual memory.
             * Learn to handle them. Until then we can expect problems using
             * OIDs and Floats as indexes  */
            if (query->types[j] == ASN_OCTET_STR) string_idx_len += strlen(val);
            set_val_from_string(&var_otherIndexes[j], query->types[j], val);
        }
        row = SNMP_MALLOC_TYPEDEF(cust_query_row);
        row->myoids = malloc(sizeof(oid) * 
            (query->num_indexes + extra_idx_count + string_idx_count + string_idx_len));
        if (row->myoids == NULL) {
            snmp_log(LOG_ERR, "memory allocation problem \n");
            return;
        }

        row->row_index.len = query->num_indexes + extra_idx_count + string_idx_len + string_idx_count;
        row->row_index.oids = row->myoids;

        err = build_oid_noalloc(row->row_index.oids, row->row_index.len,
                     (size_t *) &(row->row_index.len), NULL, 0, &var_pgsnmpdConnID);
        if (err)
            snmp_log(LOG_ERR,"error %d converting index to oid, query %s\n", err,
                query->table_name);

        row->query = query;
        row->rownum = i;

        CONTAINER_INSERT(query->cb.container, row);
    }
}

/*
 * custom_query_get_value
 *
 * This routine is called for get requests to copy the data
 * from the context to the varbind for the request. If the
 * context has been properly maintained, you don't need to
 * change in code in this fuction.
 */
int custom_query_get_value(
            netsnmp_request_info *request,
            netsnmp_index *item,
            netsnmp_table_request_info *table_info )
{
    int column = table_info->colnum;
    netsnmp_variable_list *var = request->requestvb;
    cust_query_row *context = (cust_query_row *)item;

    if (context->query->result == NULL) {
        snmp_log(LOG_ERR, "No valid result for table\n");
        /* TODO: Make this less fatal? */
        return SNMP_ERR_GENERR;
    }
    if (column > context->query->colcount + extra_idx_count) {
        snmp_log(LOG_ERR, "Unknown column in requested table\n");
        return SNMP_ERR_GENERR;
    }

    return 
        set_val_from_string(var, context->query->types[column - context->query->min_colnum],
            PQgetvalue(context->query->result, context->rownum, column - context->query->min_colnum));
}

int set_val_from_string(netsnmp_variable_list *var, u_char type, char *val) {
    int i;
    float f;
    u_char myoid[] = { 1, 3, 6, 1, 3, 1 };

    switch (type) {
        case ASN_INTEGER:
            i = atoi(val);
            snmp_set_var_typed_value(var, ASN_INTEGER,
                    (u_char *) &i, sizeof(int));
            break;
        case ASN_FLOAT:
            f = strtof(val, NULL);
            snmp_set_var_typed_value(var, ASN_OPAQUE_FLOAT,
                    (u_char *) &f, sizeof(float));
            break;
        case ASN_BOOLEAN:
            if (val[0] == 't')
                i = 1;
            else i = 2;
            snmp_set_var_typed_value(var, ASN_INTEGER,
                    (u_char *) &i, sizeof(int));
            break;
        case ASN_OCTET_STR:
            snmp_set_var_typed_value(var, type,
                    (u_char *) val, strlen(val) * sizeof(char));
            break;
        case ASN_OBJECT_ID:
            snmp_log(LOG_ERR, "Passing back an OBJECT_ID\n");
            snmp_set_var_typed_value(var, type, myoid, sizeof(u_char) * 6); /* (u_char *) val, 5); strlen(val) * sizeof(char)); */
            break;
        default:
            snmp_log(LOG_ERR, "Unknown data type returning result. This is a bug.\n");
            return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}
