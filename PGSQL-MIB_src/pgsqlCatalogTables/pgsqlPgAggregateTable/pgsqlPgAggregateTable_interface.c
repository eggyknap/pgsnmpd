/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.43.2.3 $ of : mfd-interface.m2c,v $ 
 *
 * $Id: pgsqlPgAggregateTable_interface.c,v 1.1 2008/01/17 11:49:24 eggyknap Exp $
 */
/*
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 * ***                                                               ***
 * ***  NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE  ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THIS FILE DOES NOT CONTAIN ANY USER EDITABLE CODE.      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THE GENERATED CODE IS INTERNAL IMPLEMENTATION, AND      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***    IS SUBJECT TO CHANGE WITHOUT WARNING IN FUTURE RELEASES.   ***
 * ***                                                               ***
 * ***                                                               ***
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 */

/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "pgsqlPgAggregateTable.h"


#include <net-snmp/library/container.h>

#include "pgsqlPgAggregateTable_interface.h"

/**********************************************************************
 **********************************************************************
 ***
 *** Table pgsqlPgAggregateTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * pgsqlPgAggregateTable is subid 1 of pgsqlCatalogTables.
 * Its status is Current.
 * OID: .1.3.6.1.4.1.27645.1.2.1, length: 10
*/
typedef struct pgsqlPgAggregateTable_interface_ctx_s {

   netsnmp_container              *container;
   netsnmp_cache                  *cache; /* optional cache */

   pgsqlPgAggregateTable_registration_ptr      user_ctx;
   
   netsnmp_table_registration_info  tbl_info;

   netsnmp_baby_steps_access_methods access_multiplexer;

} pgsqlPgAggregateTable_interface_ctx;

static pgsqlPgAggregateTable_interface_ctx pgsqlPgAggregateTable_if_ctx;

static void _pgsqlPgAggregateTable_container_init(
    pgsqlPgAggregateTable_interface_ctx *if_ctx);


static Netsnmp_Node_Handler _mfd_pgsqlPgAggregateTable_pre_request;
static Netsnmp_Node_Handler _mfd_pgsqlPgAggregateTable_post_request;
static Netsnmp_Node_Handler _mfd_pgsqlPgAggregateTable_object_lookup;
static Netsnmp_Node_Handler _mfd_pgsqlPgAggregateTable_get_values;
/**
 * @internal
 * Initialize the table pgsqlPgAggregateTable 
 *    (Define its contents and how it's structured)
 */
void
_pgsqlPgAggregateTable_initialize_interface(pgsqlPgAggregateTable_registration_ptr reg_ptr,  u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &pgsqlPgAggregateTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info = &pgsqlPgAggregateTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int    mfd_modes = 0;

    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_pgsqlPgAggregateTable_initialize_interface","called\n"));


    /*************************************************
     *
     * save interface context for pgsqlPgAggregateTable
     */
    /*
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(tbl_info,
                                  ASN_OCTET_STR, /** index: pgsnmpdConnID */
                                  ASN_INTEGER, /** index: rdbmsDbIndex */
                                  ASN_INTEGER, /** index: pgsqlPgAggregateEntryOID */
                             0);

    /*  Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    tbl_info->min_column = PGSQLPGAGGREGATETABLE_MIN_COL;
    tbl_info->max_column = PGSQLPGAGGREGATETABLE_MAX_COL;

    /*
     * save users context
     */
    pgsqlPgAggregateTable_if_ctx.user_ctx = reg_ptr;

    /*
     * call data access initialization code
     */
    pgsqlPgAggregateTable_init_data(reg_ptr);

    /*
     * set up the container
     */
    _pgsqlPgAggregateTable_container_init(&pgsqlPgAggregateTable_if_ctx);
    if (NULL == pgsqlPgAggregateTable_if_ctx.container) {
        snmp_log(LOG_ERR,"could not initialize container for pgsqlPgAggregateTable\n");
        return;
    }
    
    /*
     * access_multiplexer: REQUIRED wrapper for get request handling
     */
    access_multiplexer->object_lookup = _mfd_pgsqlPgAggregateTable_object_lookup;
    access_multiplexer->get_values = _mfd_pgsqlPgAggregateTable_get_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->pre_request = _mfd_pgsqlPgAggregateTable_pre_request;
    access_multiplexer->post_request = _mfd_pgsqlPgAggregateTable_post_request;


    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
    DEBUGMSGTL(("pgsqlPgAggregateTable:init_pgsqlPgAggregateTable",
                "Registering pgsqlPgAggregateTable as a mibs-for-dummies table.\n"));		 
    handler = netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo = netsnmp_handler_registration_create("pgsqlPgAggregateTable", handler,
                                                  pgsqlPgAggregateTable_oid,
                                                  pgsqlPgAggregateTable_oid_size,
                                                  HANDLER_CAN_BABY_STEP |
                                                  HANDLER_CAN_RONLY
                                                  );
    if(NULL == reginfo) {
        snmp_log(LOG_ERR,"error registering table pgsqlPgAggregateTable\n");
        return;
    }
    reginfo->my_reg_void = &pgsqlPgAggregateTable_if_ctx;

    /*************************************************
     *
     * set up baby steps handler, create it and inject it
     */
    if( access_multiplexer->object_lookup )
        mfd_modes |= BABY_STEP_OBJECT_LOOKUP;
    if( access_multiplexer->set_values )
        mfd_modes |= BABY_STEP_SET_VALUES;
    if( access_multiplexer->irreversible_commit )
        mfd_modes |= BABY_STEP_IRREVERSIBLE_COMMIT;
    if( access_multiplexer->object_syntax_checks )
        mfd_modes |= BABY_STEP_CHECK_OBJECT;

    if( access_multiplexer->pre_request )
        mfd_modes |= BABY_STEP_PRE_REQUEST;
    if( access_multiplexer->post_request )
        mfd_modes |= BABY_STEP_POST_REQUEST;
    
    if( access_multiplexer->undo_setup )
        mfd_modes |= BABY_STEP_UNDO_SETUP;
    if( access_multiplexer->undo_cleanup )
        mfd_modes |= BABY_STEP_UNDO_CLEANUP;
    if( access_multiplexer->undo_sets )
        mfd_modes |= BABY_STEP_UNDO_SETS;
    
    if( access_multiplexer->row_creation )
        mfd_modes |= BABY_STEP_ROW_CREATE;
    if( access_multiplexer->consistency_checks )
        mfd_modes |= BABY_STEP_CHECK_CONSISTENCY;
    if( access_multiplexer->commit )
        mfd_modes |= BABY_STEP_COMMIT;
    if( access_multiplexer->undo_commit )
        mfd_modes |= BABY_STEP_UNDO_COMMIT;
    
    handler = netsnmp_baby_steps_handler_get(mfd_modes);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject row_merge helper with prefix rootoid_len + 2 (entry.col)
     */
    handler = netsnmp_get_row_merge_handler(reginfo->rootoid_len + 2);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject container_table helper
     */
    handler =
        netsnmp_container_table_handler_get(tbl_info,
                                            pgsqlPgAggregateTable_if_ctx.container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler( reginfo, handler );

    /*************************************************
     *
     * inject cache helper
     */
    if(NULL != pgsqlPgAggregateTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(pgsqlPgAggregateTable_if_ctx.cache);
        netsnmp_inject_handler( reginfo, handler );
    }

    /*
     * register table
     */
    netsnmp_register_table(reginfo, tbl_info);
} /* _pgsqlPgAggregateTable_initialize_interface */

void
pgsqlPgAggregateTable_valid_columns_set(netsnmp_column_info *vc)
{
    pgsqlPgAggregateTable_if_ctx.tbl_info.valid_columns = vc;
} /* pgsqlPgAggregateTable_valid_columns_set */

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
pgsqlPgAggregateTable_index_to_oid(netsnmp_index *oid_idx,
                         pgsqlPgAggregateTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;
    
    /*
     * temp storage for parsing indexes
     */
    /*
     * pgsnmpdConnID(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
     */
    netsnmp_variable_list var_pgsnmpdConnID;
    /*
     * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsDbIndex;
    /*
     * pgsqlPgAggregateEntryOID(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/r/d/h
     */
    netsnmp_variable_list var_pgsqlPgAggregateEntryOID;

    /*
     * set up varbinds
     */
    memset( &var_pgsnmpdConnID, 0x00, sizeof(var_pgsnmpdConnID) );
    var_pgsnmpdConnID.type = ASN_OCTET_STR;
    memset( &var_rdbmsDbIndex, 0x00, sizeof(var_rdbmsDbIndex) );
    var_rdbmsDbIndex.type = ASN_INTEGER;
    memset( &var_pgsqlPgAggregateEntryOID, 0x00, sizeof(var_pgsqlPgAggregateEntryOID) );
    var_pgsqlPgAggregateEntryOID.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_pgsnmpdConnID.next_variable =  &var_rdbmsDbIndex; var_rdbmsDbIndex.next_variable =  &var_pgsqlPgAggregateEntryOID; var_pgsqlPgAggregateEntryOID.next_variable =  NULL;


    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_index_to_oid","called\n"));

        /* pgsnmpdConnID(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H */
    snmp_set_var_value(&var_pgsnmpdConnID, (u_char*)&mib_idx->pgsnmpdConnID,
                       mib_idx->pgsnmpdConnID_len * sizeof(mib_idx->pgsnmpdConnID[0]));

        /* rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h */
    snmp_set_var_value(&var_rdbmsDbIndex, (u_char*)&mib_idx->rdbmsDbIndex,
                       sizeof(mib_idx->rdbmsDbIndex));

        /* pgsqlPgAggregateEntryOID(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/r/d/h */
    snmp_set_var_value(&var_pgsqlPgAggregateEntryOID, (u_char*)&mib_idx->pgsqlPgAggregateEntryOID,
                       sizeof(mib_idx->pgsqlPgAggregateEntryOID));


    err = build_oid_noalloc(oid_idx->oids, oid_idx->len, (size_t *)&oid_idx->len,
                           NULL, 0, &var_pgsnmpdConnID);
    if(err)
        snmp_log(LOG_ERR,"error %d converting index to oid\n", err);

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_pgsnmpdConnID );

    return err;
} /* pgsqlPgAggregateTable_index_to_oid */

/**
 * extract pgsqlPgAggregateTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
pgsqlPgAggregateTable_index_from_oid(netsnmp_index *oid_idx,
                         pgsqlPgAggregateTable_mib_index *mib_idx)
{
    int err = SNMP_ERR_NOERROR;
    
    /*
     * temp storage for parsing indexes
     */
    /*
     * pgsnmpdConnID(1)/DisplayString/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/H
     */
    netsnmp_variable_list var_pgsnmpdConnID;
    /*
     * rdbmsDbIndex(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/R/d/h
     */
    netsnmp_variable_list var_rdbmsDbIndex;
    /*
     * pgsqlPgAggregateEntryOID(1)/INTEGER/ASN_INTEGER/long(long)//l/a/w/e/r/d/h
     */
    netsnmp_variable_list var_pgsqlPgAggregateEntryOID;

    /*
     * set up varbinds
     */
    memset( &var_pgsnmpdConnID, 0x00, sizeof(var_pgsnmpdConnID) );
    var_pgsnmpdConnID.type = ASN_OCTET_STR;
    memset( &var_rdbmsDbIndex, 0x00, sizeof(var_rdbmsDbIndex) );
    var_rdbmsDbIndex.type = ASN_INTEGER;
    memset( &var_pgsqlPgAggregateEntryOID, 0x00, sizeof(var_pgsqlPgAggregateEntryOID) );
    var_pgsqlPgAggregateEntryOID.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_pgsnmpdConnID.next_variable =  &var_rdbmsDbIndex; var_rdbmsDbIndex.next_variable =  &var_pgsqlPgAggregateEntryOID; var_pgsqlPgAggregateEntryOID.next_variable =  NULL;


    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_index_from_oid","called\n"));

    /*
     * parse the oid into the individual index components
     */
    err = parse_oid_indexes( oid_idx->oids, oid_idx->len,
                             &var_pgsnmpdConnID );
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy out values
         */
    /*
     * NOTE: val_len is in bytes, pgsnmpdConnID_len might not be
     */
         if(var_pgsnmpdConnID.val_len > sizeof(mib_idx->pgsnmpdConnID))
             err = SNMP_ERR_GENERR;
         else {
             memcpy(mib_idx->pgsnmpdConnID, var_pgsnmpdConnID.val.string, var_pgsnmpdConnID.val_len);
             mib_idx->pgsnmpdConnID_len = var_pgsnmpdConnID.val_len / sizeof(mib_idx->pgsnmpdConnID[0]);
         }
    mib_idx->rdbmsDbIndex = *((long *)var_rdbmsDbIndex.val.string);
    mib_idx->pgsqlPgAggregateEntryOID = *((long *)var_pgsqlPgAggregateEntryOID.val.string);


    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_pgsnmpdConnID );

    return err;
} /* pgsqlPgAggregateTable_index_from_oid */


/* *********************************************************************
 * @internal
 * allocate resources for a pgsqlPgAggregateTable_rowreq_ctx
 */
pgsqlPgAggregateTable_rowreq_ctx *
pgsqlPgAggregateTable_allocate_rowreq_ctx(void)
{
    pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx =
                  SNMP_MALLOC_TYPEDEF(pgsqlPgAggregateTable_rowreq_ctx);

    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:pgsqlPgAggregateTable_allocate_rowreq_ctx","called\n"));

    if(NULL == rowreq_ctx) {
        snmp_log(LOG_ERR,"Couldn't allocate memory for a "
                 "pgsqlPgAggregateTable_rowreq_ctx.\n");
    }

    rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

    rowreq_ctx->pgsqlPgAggregateTable_data_list = NULL;
    rowreq_ctx->pgsqlPgAggregateTable_reg = pgsqlPgAggregateTable_if_ctx.user_ctx;


    return rowreq_ctx;
} /* pgsqlPgAggregateTable_allocate_rowreq_ctx */

/*
 * @internal
 * release resources for a pgsqlPgAggregateTable_rowreq_ctx
 */
void
pgsqlPgAggregateTable_release_rowreq_ctx(pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:pgsqlPgAggregateTable_release_rowreq_ctx","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);
    

    /*
     * free index oid pointer
     */
    if(rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
        free(rowreq_ctx->oid_idx.oids);

    SNMP_FREE(rowreq_ctx);
} /* pgsqlPgAggregateTable_release_rowreq_ctx */

/**
 * @internal
 * wrapper
 */
static int
_mfd_pgsqlPgAggregateTable_pre_request(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *agtreq_info,
                            netsnmp_request_info *requests)
{
    int rc = pgsqlPgAggregateTable_pre_request(pgsqlPgAggregateTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:pgsqlPgAggregateTable","error %d from "
                    "pgsqlPgAggregateTable_pre_request\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    }
    
    return SNMP_ERR_NOERROR;
} /* _mfd_pgsqlPgAggregateTable_pre_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_pgsqlPgAggregateTable_post_request(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *agtreq_info,
                             netsnmp_request_info *requests)
{
    pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx;
    int rc = pgsqlPgAggregateTable_post_request(pgsqlPgAggregateTable_if_ctx.user_ctx);
    if (MFD_SUCCESS != rc) {
        /*
         * nothing we can do about it but log it
         */
        DEBUGMSGTL(("internal:pgsqlPgAggregateTable","error %d from "
                    "pgsqlPgAggregateTable_post_request\n", rc));
    }
    
    /*
     * if there are no errors, check for and handle row creation/deletion
     */
    rc = netsnmp_check_requests_error(requests);
    if ((SNMP_ERR_NOERROR == rc) &&
        (NULL !=
         (rowreq_ctx = netsnmp_container_table_row_extract(requests)))) {
        if (rowreq_ctx->rowreq_flags & MFD_ROW_CREATED) {
            rowreq_ctx->rowreq_flags &= ~MFD_ROW_CREATED;
            CONTAINER_INSERT(pgsqlPgAggregateTable_if_ctx.container, rowreq_ctx);
        }
        else if (rowreq_ctx->rowreq_flags & MFD_ROW_DELETED) {
            CONTAINER_REMOVE(pgsqlPgAggregateTable_if_ctx.container, rowreq_ctx);
            pgsqlPgAggregateTable_release_rowreq_ctx(rowreq_ctx);
        }
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_pgsqlPgAggregateTable_post_request */

/**
 * @internal
 * wrapper
 */
static int
_mfd_pgsqlPgAggregateTable_object_lookup(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_mfd_pgsqlPgAggregateTable_object_lookup","called\n"));

    /*
     * get our context from mfd
     * pgsqlPgAggregateTable_interface_ctx *if_ctx =
     *             (pgsqlPgAggregateTable_interface_ctx *)reginfo->my_reg_void;
     */

    if(NULL == rowreq_ctx) {
        netsnmp_request_set_error_all(requests, SNMP_ERR_NOCREATION);
    }
    else {
        pgsqlPgAggregateTable_row_prep(rowreq_ctx);
    }

    return SNMP_ERR_NOERROR;
} /* _mfd_pgsqlPgAggregateTable_object_lookup */

/***********************************************************************
 *
 * GET processing
 *
 ***********************************************************************/
/*
 * @internal
 * Retrieve the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_pgsqlPgAggregateTable_get_column( pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx,
                       netsnmp_variable_list *var, int column )
{
    int rc = SNMPERR_SUCCESS;
    
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_mfd_pgsqlPgAggregateTable_get_column","called\n"));


    netsnmp_assert(NULL != rowreq_ctx);

    switch(column) {

    /* pgsqlPgAggregateAggfnoid(2)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/r/d/h */
    case COLUMN_PGSQLPGAGGREGATEAGGFNOID:
    var->val_len = sizeof(long);
    var->type = ASN_INTEGER;
rc = pgsqlPgAggregateAggfnoid_get(rowreq_ctx, (long *)var->val.string );
        break;

    /* pgsqlPgAggregateAggtransfn(3)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/r/d/h */
    case COLUMN_PGSQLPGAGGREGATEAGGTRANSFN:
    var->val_len = sizeof(long);
    var->type = ASN_INTEGER;
rc = pgsqlPgAggregateAggtransfn_get(rowreq_ctx, (long *)var->val.string );
        break;

    /* pgsqlPgAggregateAggfinalfn(4)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/r/d/h */
    case COLUMN_PGSQLPGAGGREGATEAGGFINALFN:
    var->val_len = sizeof(long);
    var->type = ASN_INTEGER;
rc = pgsqlPgAggregateAggfinalfn_get(rowreq_ctx, (long *)var->val.string );
        break;

    /* pgsqlPgAggregateAggsortop(5)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/r/d/h */
    case COLUMN_PGSQLPGAGGREGATEAGGSORTOP:
    var->val_len = sizeof(long);
    var->type = ASN_INTEGER;
rc = pgsqlPgAggregateAggsortop_get(rowreq_ctx, (long *)var->val.string );
        break;

    /* pgsqlPgAggregateAggtranstype(6)/INTEGER/ASN_INTEGER/long(long)//l/A/w/e/r/d/h */
    case COLUMN_PGSQLPGAGGREGATEAGGTRANSTYPE:
    var->val_len = sizeof(long);
    var->type = ASN_INTEGER;
rc = pgsqlPgAggregateAggtranstype_get(rowreq_ctx, (long *)var->val.string );
        break;

    /* pgsqlPgAggregateAgginitval(7)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H */
    case COLUMN_PGSQLPGAGGREGATEAGGINITVAL:
    var->type = ASN_OCTET_STR;
rc = pgsqlPgAggregateAgginitval_get(rowreq_ctx, (char **)&var->val.string, &var->val_len );
        break;

     default:
         snmp_log(LOG_ERR,"unknown column %d in _pgsqlPgAggregateTable_get_column\n", column);
         break;
    }

    return rc;
} /* _pgsqlPgAggregateTable_get_column */

int
_mfd_pgsqlPgAggregateTable_get_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx =
                  netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info * tri;
    u_char                     * old_string;
    void                      (*dataFreeHook)(void *);
    int                        rc;

    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_mfd_pgsqlPgAggregateTable_get_values","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);
    
    for(;requests; requests = requests->next) {
        /*
         * save old pointer, so we can free it if replaced
         */
        old_string = requests->requestvb->val.string;
        dataFreeHook = requests->requestvb->dataFreeHook;
        if(NULL == requests->requestvb->val.string) {
            requests->requestvb->val.string = requests->requestvb->buf;
            requests->requestvb->val_len = sizeof(requests->requestvb->buf);
        }
        else if(requests->requestvb->buf == requests->requestvb->val.string) {
            if(requests->requestvb->val_len != sizeof(requests->requestvb->buf))
                requests->requestvb->val_len = sizeof(requests->requestvb->buf);
        }

        /*
         * get column data
         */
        tri = netsnmp_extract_table_info(requests);
        if(NULL == tri)
            continue;
        
        rc = _pgsqlPgAggregateTable_get_column(rowreq_ctx, requests->requestvb, tri->colnum);
        if(rc) {
            if(MFD_SKIP == rc) {
                requests->requestvb->type = ASN_PRIV_RETRY;
                rc = SNMP_ERR_NOERROR;
            }
        }
        else if (NULL == requests->requestvb->val.string) {
            snmp_log(LOG_ERR,"NULL varbind data pointer!\n");
            rc = SNMP_ERR_GENERR;
        }
        if(rc)
            netsnmp_request_set_error(requests, SNMP_VALIDATE_ERR(rc));

        /*
         * if the buffer wasn't used previously for the old data (i.e. it
         * was allcoated memory)  and the get routine replaced the pointer,
         * we need to free the previous pointer.
         */
        if(old_string && (old_string != requests->requestvb->buf) &&
           (requests->requestvb->val.string != old_string)) {
            if(dataFreeHook)
                (*dataFreeHook)(old_string);
            else
                free(old_string);
        }
    } /* for results */

    return SNMP_ERR_NOERROR;
} /* _mfd_pgsqlPgAggregateTable_get_values */

/***********************************************************************
 *
 * SET processing
 *
 ***********************************************************************/

/*
 * NOT APPLICABLE (per MIB or user setting)
 */
/***********************************************************************
 *
 * DATA ACCESS
 *
 ***********************************************************************/
/**
 * @internal
 */
static int
_cache_load(netsnmp_cache *cache, void *vmagic)
{
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_cache_load","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for pgsqlPgAggregateTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));
    
    /*
     * call user code
     */
    return pgsqlPgAggregateTable_cache_load((netsnmp_container*)cache->magic);
} /* _cache_load */

/**
 * @internal
 */
static void
_cache_item_free(pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx, void *context)
{
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_cache_item_free","called\n"));

    if(NULL == rowreq_ctx)
        return;

    pgsqlPgAggregateTable_release_rowreq_ctx(rowreq_ctx);
} /* _cache_item_free */

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache *cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_cache_free","called\n"));

    if((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in pgsqlPgAggregateTable_cache_free\n");
        return;
    }

    container = (netsnmp_container*)cache->magic;

    /*
     * call user code
     */
    pgsqlPgAggregateTable_cache_free(container);
    
    /*
     * free all items. inefficient, but easy.
     */
    CONTAINER_CLEAR(container,
                    (netsnmp_container_obj_func *)_cache_item_free,
                    NULL);
} /* _cache_free */

/**
 * @internal
 * initialize the iterator container with functions or wrappers
 */
void
_pgsqlPgAggregateTable_container_init(pgsqlPgAggregateTable_interface_ctx *if_ctx)
{
    DEBUGMSGTL(("internal:pgsqlPgAggregateTable:_pgsqlPgAggregateTable_container_init","called\n"));
    
    /*
     * set up the cache
     */
    if_ctx->cache = netsnmp_cache_create(30, /* timeout in seconds */
                                         _cache_load, _cache_free,
                                         pgsqlPgAggregateTable_oid,
                                         pgsqlPgAggregateTable_oid_size);

    if(NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for pgsqlPgAggregateTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    pgsqlPgAggregateTable_container_init(&if_ctx->container, if_ctx->cache);
    if(NULL == if_ctx->container)
        if_ctx->container = netsnmp_container_find("pgsqlPgAggregateTable:table_container");
    if(NULL == if_ctx->container) {
        snmp_log(LOG_ERR,"error creating container in "
                 "pgsqlPgAggregateTable_container_init\n");
        return;
    }
    if_ctx->cache->magic = (void*)if_ctx->container;
} /* _pgsqlPgAggregateTable_container_init */
