#include <yaml.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "query_reader.h"

/* TODO: Return value checking of strdup, etc. is fairly haphazard. */

void print_error(yaml_parser_t *parser);

typedef enum query_reader_state_s {
    INIT,
    READ_QUERY,
    NAME_VALUE,
    QUERY_VALUE,
    OID_VALUE,
    INDEXES_VALUE,
    MINCOL_VALUE,
    TYPES_VALUE,
    TYPE_MAPPING_VALUE
} query_reader_state_t;

typedef struct string_to_int_struct {
    char *name;
    int   value;
} string_to_int;

char *yaml_get_event_type(yaml_event_type_t t);

char *
yaml_get_event_type (yaml_event_type_t t) {
    switch (t) {
        case YAML_NO_EVENT:
            return "YAML_NO_EVENT";
        case YAML_STREAM_START_EVENT:
            return "YAML_STREAM_START_EVENT";
        case YAML_STREAM_END_EVENT:
            return "YAML_STREAM_END_EVENT";
        case YAML_DOCUMENT_START_EVENT:
            return "YAML_DOCUMENT_START_EVENT";
        case YAML_DOCUMENT_END_EVENT:
            return "YAML_DOCUMENT_END_EVENT";
        case YAML_ALIAS_EVENT:
            return "YAML_ALIAS_EVENT";
        case YAML_SCALAR_EVENT:
            return "YAML_SCALAR_EVENT";
        case YAML_SEQUENCE_START_EVENT:
            return "YAML_SEQUENCE_START_EVENT";
        case YAML_SEQUENCE_END_EVENT:
            return "YAML_SEQUENCE_END_EVENT";
        case YAML_MAPPING_START_EVENT:
            return "YAML_MAPPING_START_EVENT";
        case YAML_MAPPING_END_EVENT:
            return "YAML_MAPPING_END_EVENT";
        default:
            return "Unknown yaml event type";
    };
}

pgsnmpd_query *
parse_config(const char *filename) {
    FILE *inputfile;
    u_char *types;
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0, i, error = 0, found = 0;
    pgsnmpd_query *head = NULL, *cur, *newquery;
    query_reader_state_t st = INIT;
    char *name_str = NULL, *query_str = NULL, *oid_str = NULL;
    int indexes_val, mincol_val, query_count = 0;
    oid *oid_arr;
    int oid_len = 1, typecol, typeslen;
    int yaml_type_map_len = 6;
    string_to_int yaml_type_map[6] = {
        { "name",       NAME_VALUE },
        { "query",      QUERY_VALUE },
        { "oid",        OID_VALUE },
        { "indexes",    INDEXES_VALUE },
        { "min_column", MINCOL_VALUE },
        { "types",      TYPES_VALUE }
    };

    int snmp_type_map_len = 5;
    string_to_int snmp_type_map[5] = {
        { "ASN_INTEGER",   ASN_INTEGER },
        { "ASN_FLOAT",     ASN_FLOAT },
        { "ASN_BOOLEAN",   ASN_BOOLEAN },
        { "ASN_OBJECT_ID", ASN_OBJECT_ID },
        { "ASN_OCTET_STR", ASN_OCTET_STR },
    };

    yaml_parser_initialize(&parser);
    inputfile = fopen(filename, "rb");
    if (inputfile == NULL) {
        snmp_log(LOG_ERR, "Problem opening input file \"%s\": %s\n", filename, strerror(errno));
        return 0;
    }
    yaml_parser_set_input_file(&parser, inputfile);

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            error = 1;
            break;
        }
        done = (event.type == YAML_STREAM_END_EVENT);
        /*snmp_log(LOG_INFO, "Found a %s value\n", yaml_get_event_type(event.type));*/
        /* head = process_event(&event); */
        switch (st) {
            case INIT:
                if (event.type == YAML_SCALAR_EVENT &&
                    strcmp((char *)event.data.scalar.value, "queries") == 0) {
                    st = READ_QUERY;
                    if (name_str  != NULL) free(name_str);
                    if (query_str != NULL) free(query_str);
                    if (oid_str   != NULL) free(oid_str);

                    name_str    = NULL;
                    query_str   = NULL;
                    oid_str     = NULL;

                    indexes_val = -1;
                    mincol_val  = -1;
                }
                query_count++;
                break;
            case READ_QUERY:
                if (event.type == YAML_SCALAR_EVENT) {
                    typeslen = -1;
                    types = NULL;
                    found = 0;
                    for (i = 0; i < yaml_type_map_len; i++) {
                        if (strcmp(yaml_type_map[i].name, (char*) event.data.scalar.value) == 0) {
                            st = yaml_type_map[i].value;
                            found = 1;
                            break;
                        }
                    }
                    if (found != 1) {
                        snmp_log(LOG_ERR, "Unexpected data object reading query %d: %s\n", query_count, (char *) event.data.scalar.value);
                        return NULL;
                    }
                }
                else if (event.type == YAML_MAPPING_END_EVENT) {
                    if (indexes_val == -1 ||
                        mincol_val  == -1 ||
                        name_str    == NULL ||
                        oid_str     == NULL ||
                        query_str   == NULL) {
                        snmp_log(LOG_ERR, "Error reading query %d (%s): %s%s%s%s%s\n",
                            query_count,
                            name_str    == NULL ? "Name Unknown" : name_str,
                            name_str    == NULL ? "Name not specified"    : "",
                            oid_str     == NULL ? "OID not specified"     : "",
                            query_str   == NULL ? "Query not specified"   : "",
                            indexes_val == -1   ? "Indexes not specified" : "",
                            mincol_val  == -1   ? "Min column not specified" : "");
                        return NULL;
                    }

                    oid_arr = parse_oid(oid_str, &oid_len);

                    newquery = alloc_custom_query(name_str, query_str, oid_arr, oid_len);
                    newquery->num_indexes = indexes_val;
                    newquery->min_colnum  = mincol_val;
                    newquery->types       = types;
                    newquery->typeslen    = typeslen;

                    if (head == NULL) {
                        head = newquery;
                        cur = head;
                    }
                    else {
                        cur->next = newquery;
                        cur = newquery;
                    }
                }
                else if (event.type == YAML_SEQUENCE_END_EVENT)
                    st = INIT;
                break;
            case NAME_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    name_str = strdup((char *)event.data.scalar.value);
                    st = READ_QUERY;
                }
                else {
                    snmp_log(LOG_ERR, "Unexpected YAML event trying to read name of query %d\n", query_count);
                    return NULL;
                }
                break;
            case QUERY_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    query_str = strdup((char *)event.data.scalar.value);
                    st = READ_QUERY;
                }
                else {
                    snmp_log(LOG_ERR,"Unexpected YAML event trying to read query string of query %d\n", query_count);
                    return NULL;
                }
                break;
            case OID_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    oid_str = strdup((char *)event.data.scalar.value);
                    st = READ_QUERY;
                }
                else {
                    snmp_log(LOG_ERR, "Unexpected YAML event trying to read OID of query %d\n", query_count);
                    return NULL;
                }
                break;
            case INDEXES_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    indexes_val = atoi((char *)event.data.scalar.value);
                    st = READ_QUERY;
                }
                else {
                    snmp_log(LOG_ERR, "Unexpected YAML event trying to read indexes of query %d\n", query_count);
                    return NULL;
                }
                break;
            case MINCOL_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    mincol_val = atoi((char *)event.data.scalar.value);
                    st = READ_QUERY;
                }
                else {
                    snmp_log(LOG_ERR, "Unexpected YAML event trying to read min_column of query %d\n", query_count);
                    return NULL;
                }
                break;
            case TYPES_VALUE:
                if (event.type == YAML_SCALAR_EVENT) {
                    typecol = atoi((char *)event.data.scalar.value);
                    if (typecol < 1)
                        /* LOG_CRIT or higher? */
                        snmp_log(LOG_ERR, "Invalid column number (must be > 0): %d\n", typecol);
                    st = TYPE_MAPPING_VALUE;
                }
                else if (event.type == YAML_SEQUENCE_END_EVENT)
                    st = READ_QUERY;
                break;
            case TYPE_MAPPING_VALUE:
                st = TYPES_VALUE;
                if (typeslen < typecol) {
                    types = realloc(types, sizeof(u_char *) * typecol);
                    if (types == NULL) {
                        /* Perhaps LOG_CRIT or higher? */
                        snmp_log(LOG_ERR, "Couldn't allocate enough memory for column types\n");
                    }
                    else {
                        init_types_array(types, typeslen, typecol);
                        if (typeslen != -1)
                            for (i = typeslen; i < typecol; i++)
                                types[i] = (u_char) 255;
                        typeslen = typecol;
                    }
                }
                types[typecol-1] = 255;
                for (i = 0; i < snmp_type_map_len; i++) {
                    if (strcmp((char *) event.data.scalar.value, snmp_type_map[i].name) == 0)
                        types[typecol-1] = (u_char) snmp_type_map[i].value;
                }
                if (types[typecol-1] == 255)
                    snmp_log(LOG_ERR, "Couldn't understand SNMP type \"%s\"\n", (char *) event.data.scalar.value);
                break;
        }
        yaml_event_delete(&event);
    }
    
    if (error)
        print_error(&parser);

    yaml_parser_delete(&parser);
    fclose(inputfile);



    /* Print out results
    cur = head;
    while (cur != NULL) {
        printf("Query:\n\tname: %s\n\tquery: %s\n\toid len: %d\n\tindexes: %d\n\tmin_col: %d\n",
            cur->table_name,
            cur->query_text,
            cur->oid_len,
            cur->num_indexes,
            cur->min_colnum);
        printf("\tOID: ");
        done = 0;
        while (done < cur->oid_len)
            printf(".%u", (u_int) cur->table_oid[done++]);
        printf("\n");
        cur = cur->next;
    }
    */
    return head;
}

void print_error(yaml_parser_t *parser) {
    snmp_log(LOG_ERR, "YAML parse error: %s at offset %d, value %d, context \"%s\"\n",
        parser->problem, parser->problem_offset, parser->problem_value, parser->context);

    snmp_log(LOG_ERR, "Problem mark: index %d, line %d, column %d\n", 
        parser->problem_mark.index, parser->problem_mark.line, parser->problem_mark.column);
    snmp_log(LOG_ERR, "Context marK: index %d, line %d, column %d\n", 
        parser->context_mark.index, parser->context_mark.line, parser->context_mark.column);

    switch (parser->error) {
        case YAML_NO_ERROR:
            snmp_log(LOG_ERR, "\tYAML_NO_ERROR\n");
            break;
        case YAML_MEMORY_ERROR:
            snmp_log(LOG_ERR, "\tYAML_MEMORY_ERROR\n");
            break;
        case YAML_READER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_READER_ERROR\n");
            break;
        case YAML_SCANNER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_SCANNER_ERROR\n");
            break;
        case YAML_PARSER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_PARSER_ERROR\n");
            break;
        case YAML_COMPOSER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_COMPOSER_ERROR\n");
            break;
        case YAML_WRITER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_WRITER_ERROR\n");
            break;
        case YAML_EMITTER_ERROR:
            snmp_log(LOG_ERR, "\tYAML_EMITTER_ERROR\n");
            break;
    }
}
