/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.12 $ of : mfd-data-access.m2c,v $ 
 *
 * $Id: pgsqlPgAggregateTable_data_access.c,v 1.2 2008/01/17 12:29:36 eggyknap Exp $
 */
#include "pgsnmpd.h"

/* include our parent header */
#include "pgsqlPgAggregateTable.h"
#include "pgsqlPgAggregateTable_data_access.h"

/** @defgroup data_access data_access: Routines to access data
 *
 * These routines are used to locate the data used to satisfy
 * requests.
 * 
 * @{
 */
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

/**
 * initialization for pgsqlPgAggregateTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param pgsqlPgAggregateTable_reg
 *        Pointer to pgsqlPgAggregateTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
pgsqlPgAggregateTable_init_data(pgsqlPgAggregateTable_registration_ptr pgsqlPgAggregateTable_reg)
{
    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_init_data","called\n"));

    /*
     * TODO:303:o: Initialize pgsqlPgAggregateTable data.
     */

    return MFD_SUCCESS;
} /* pgsqlPgAggregateTable_init_data */

/**
 * container-cached overview
 *
 */

/***********************************************************************
 *
 * cache
 *
 ***********************************************************************/
/**
 * container initialization
 *
 * @param container_ptr_ptr A pointer to a container pointer. If you
 *        create a custom container, use this parameter to return it
 *        to the MFD helper. If set to NULL, the MFD helper will
 *        allocate a container for you.
 * @param  cache A pointer to a cache structure. You can set the timeout
 *         and other cache flags using this pointer.
 *
 *  This function is called at startup to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases. If no custom
 *  container is allocated, the MFD code will create one for your.
 *
 *  This is also the place to set up cache behavior. The default, to
 *  simply set the cache timeout, will work well with the default
 *  container. If you are using a custom container, you may want to
 *  look at the cache helper documentation to see if there are any
 *  flags you want to set.
 *
 * @remark
 *  This would also be a good place to do any initialization needed
 *  for you data source. For example, opening a connection to another
 *  process that will supply the data, opening a database, etc.
 */
void
pgsqlPgAggregateTable_container_init(netsnmp_container **container_ptr_ptr,
                        netsnmp_cache *cache)
{
    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_container_init","called\n"));
    
    if((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,"bad params to pgsqlPgAggregateTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up pgsqlPgAggregateTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = PGSQLPGAGGREGATETABLE_CACHE_TIMEOUT; /* seconds */
} /* pgsqlPgAggregateTable_container_init */

/**
 * load cache data
 *
 * TODO:350:M: Implement pgsqlPgAggregateTable cache load
 *
 * @param container container to which items should be inserted
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_RESOURCE_UNAVAILABLE : Can't access data source
 * @retval MFD_ERROR                : other error.
 *
 *  This function is called to cache the index(es) (and data, optionally)
 *  for the every row in the data set.
 *
 * @remark
 *  While loading the cache, the only important thing is the indexes.
 *  If access to your data is cheap/fast (e.g. you have a pointer to a
 *  structure in memory), it would make sense to update the data here.
 *  If, however, the accessing the data invovles more work (e.g. parsing
 *  some other existing data, or peforming calculations to derive the data),
 *  then you can limit yourself to setting the indexes and saving any
 *  information you will need later. Then use the saved information in
 *  pgsqlPgAggregateTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
pgsqlPgAggregateTable_cache_load(netsnmp_container *container)
{
    pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx;
    size_t                 count = 0;
    
   char   pgsnmpdConnID[112] = "Default conn ID";
   size_t      pgsnmpdConnID_len = strlen(pgsnmpdConnID);
   long   rdbmsDbIndex = 1;
   int i, resultCount, tmpInt;
   char *tmpString;
   PGresult *pg_db_qry;

snmp_log(LOG_INFO, "Running pgsqlPgAggregateTable\n");
   if (PQstatus(dbconn) == CONNECTION_OK) 
	   pg_db_qry = PQexec(dbconn, "SELECT aggfnoid::INTEGER, aggfnoid, aggtransfn, aggfinalfn, aggsortop, aggtranstype, agginitval FROM pg_aggregate ORDER BY 1 ASC");
	else {
		snmp_log(LOG_ERR, "Can't get connected to database\n");
		return MFD_RESOURCE_UNAVAILABLE;
	}

    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_cache_load","called\n"));

	if (PQresultStatus(pg_db_qry) != PGRES_TUPLES_OK) {
		snmp_log(LOG_ERR, "Didn't get any results from the database\n");
		PQclear(pg_db_qry);
		return MFD_RESOURCE_UNAVAILABLE;
	}
    resultCount = PQntuples(pg_db_qry);

    /*
     * TODO:351:M: |-> Load/update data in the pgsqlPgAggregateTable container.
     * loop over your pgsqlPgAggregateTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    for (i = 0; i < resultCount; i++) {

        /*
         * TODO:352:M: |   |-> set indexes in new pgsqlPgAggregateTable rowreq context.
         */
        rowreq_ctx = pgsqlPgAggregateTable_allocate_rowreq_ctx();
        if (NULL == rowreq_ctx) {
            snmp_log(LOG_ERR, "memory allocation failed\n");
            return MFD_RESOURCE_UNAVAILABLE;
        }
        if(MFD_SUCCESS != pgsqlPgAggregateTable_indexes_set(rowreq_ctx
                               , pgsnmpdConnID, pgsnmpdConnID_len
                               , rdbmsDbIndex
                               , atol(PQgetvalue(pg_db_qry, i, 0))
               )) {
            snmp_log(LOG_ERR,"error setting index while loading "
                     "pgsqlPgAggregateTable cache.\n");
            pgsqlPgAggregateTable_release_rowreq_ctx(rowreq_ctx);
            continue;
        }
	rowreq_ctx->data.pgsqlPgAggregateAgginitval_len = 255;

    rowreq_ctx->data.pgsqlPgAggregateAggfnoid = strtoul(PQgetvalue(pg_db_qry, i, 1), NULL, 10);
    
    rowreq_ctx->data.pgsqlPgAggregateAggtransfn = strtoul(PQgetvalue(pg_db_qry, i, 2), NULL, 10);
    
    rowreq_ctx->data.pgsqlPgAggregateAggfinalfn = strtoul(PQgetvalue(pg_db_qry, i, 3), NULL, 10);
    
    rowreq_ctx->data.pgsqlPgAggregateAggsortop = strtoul(PQgetvalue(pg_db_qry, i, 4), NULL, 10);
    
    rowreq_ctx->data.pgsqlPgAggregateAggtranstype = strtoul(PQgetvalue(pg_db_qry, i, 5), NULL, 10);

    tmpString = PQgetvalue(pg_db_qry, i, 6);
    tmpInt = strlen(tmpString);
    if ((NULL == rowreq_ctx->data.pgsqlPgAggregateAgginitval) ||
        (rowreq_ctx->data.pgsqlPgAggregateAgginitval_len < (tmpInt * sizeof(rowreq_ctx->data.pgsqlPgAggregateAgginitval[0])))) {
        snmp_log(LOG_ERR,"not enough space for value\n");
        return MFD_ERROR;
    }
    rowreq_ctx->data.pgsqlPgAggregateAgginitval_len = tmpInt * sizeof(rowreq_ctx->data.pgsqlPgAggregateAgginitval[0]);
    memcpy( rowreq_ctx->data.pgsqlPgAggregateAgginitval, tmpString, rowreq_ctx->data.pgsqlPgAggregateAgginitval_len );
    
        
        /*
         * insert into table container
         */
        CONTAINER_INSERT(container, rowreq_ctx);
        ++count;
    }


    DEBUGMSGT(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_cache_load",
               "inserted %d records\n", count));
    PQclear(pg_db_qry);

    return MFD_SUCCESS;
} /* pgsqlPgAggregateTable_cache_load */

/**
 * cache clean up
 *
 * @param container container with all current items
 *
 *  This optional callback is called prior to all
 *  item's being removed from the container. If you
 *  need to do any processing before that, do it here.
 *
 * @note
 *  The MFD helper will take care of releasing all the row contexts.
 *
 */
void
pgsqlPgAggregateTable_cache_free(netsnmp_container *container)
{
    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_cache_free","called\n"));

    /*
     * TODO:380:M: Free pgsqlPgAggregateTable cache.
     */
} /* pgsqlPgAggregateTable_cache_free */

/**
 * prepare row for processing.
 *
 *  When the agent has located the row for a request, this function is
 *  called to prepare the row for processing. If you fully populated
 *  the data context during the index setup phase, you may not need to
 *  do anything.
 *
 * @param rowreq_ctx pointer to a context.
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 */
int
pgsqlPgAggregateTable_row_prep( pgsqlPgAggregateTable_rowreq_ctx *rowreq_ctx)
{
    DEBUGMSGTL(("verbose:pgsqlPgAggregateTable:pgsqlPgAggregateTable_row_prep","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
} /* pgsqlPgAggregateTable_row_prep */

/** @} */