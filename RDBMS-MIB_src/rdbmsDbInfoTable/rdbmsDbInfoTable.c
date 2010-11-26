/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable.c
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable.c,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */
#include "pgsnmpd.h"

/* include our parent header */
#include "rdbmsDbInfoTable.h"
#include "rdbmsDbInfoTable_interface.h"

oid rdbmsDbInfoTable_oid[] = { RDBMSDBINFOTABLE_OID };
int rdbmsDbInfoTable_oid_size = OID_LENGTH(rdbmsDbInfoTable_oid);

void initialize_table_rdbmsDbInfoTable(void);


/**
 * Initializes the rdbmsDbInfoTable module
 */
void
init_rdbmsDbInfoTable(void)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:init_rdbmsDbInfoTable","called\n"));

    /*
     * TODO:300:o: Perform rdbmsDbInfoTable one-time module initialization.
     */
     
    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init("rdbmsDbInfoTable"))
        initialize_table_rdbmsDbInfoTable();

} /* init_rdbmsDbInfoTable */

/**
 * Initialize the table rdbmsDbInfoTable 
 *    (Define its contents and how it's structured)
 */
void
initialize_table_rdbmsDbInfoTable(void)
{
    rdbmsDbInfoTable_registration_ptr user_context;
    u_long flags;

    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:initialize_table_rdbmsDbInfoTable","called\n"));

    /*
     * TODO:301:o: Perform rdbmsDbInfoTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize rdbmsDbInfoTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    /*
     * a netsnmp_data_list is a simple way to store void pointers. A simple
     * string token is used to add, find or remove pointers.
     */
    user_context = netsnmp_create_data_list("rdbmsDbInfoTable", NULL, NULL);
    
    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;
    
    /*
     * call interface initialization code
     */
    _rdbmsDbInfoTable_initialize_interface(user_context, flags);
} /* initialize_table_rdbmsDbInfoTable */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int
rdbmsDbInfoTable_pre_request(rdbmsDbInfoTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_pre_request","called\n"));

    /*
     * TODO:510:o: Perform rdbmsDbInfoTable pre-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_pre_request */

/**
 * post-request callback
 *
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int
rdbmsDbInfoTable_post_request(rdbmsDbInfoTable_registration_ptr user_context)
{
    DEBUGMSGTL(("verbose:rdbmsDbInfoTable:rdbmsDbInfoTable_post_request","called\n"));

    /*
     * TODO:511:o: Perform rdbmsDbInfoTable pos-request actions.
     */

    return MFD_SUCCESS;
} /* rdbmsDbInfoTable_post_request */


/** @{ */
