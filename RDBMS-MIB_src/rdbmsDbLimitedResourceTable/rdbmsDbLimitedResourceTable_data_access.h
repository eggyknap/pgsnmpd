/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable_data_access.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBLIMITEDRESOURCETABLE_DATA_ACCESS_H
#define RDBMSDBLIMITEDRESOURCETABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern "C" {
#endif


/* *********************************************************************
 * function declarations
 */

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table rdbmsDbLimitedResourceTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbLimitedResourceTable is subid 4 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.4, length: 9
*/


    int rdbmsDbLimitedResourceTable_init_data(rdbmsDbLimitedResourceTable_registration_ptr rdbmsDbLimitedResourceTable_reg);


/*
 * TODO:180:o: Review rdbmsDbLimitedResourceTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSDBLIMITEDRESOURCETABLE_CACHE_TIMEOUT   60

void rdbmsDbLimitedResourceTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsDbLimitedResourceTable_cache_load(netsnmp_container *container);
void rdbmsDbLimitedResourceTable_cache_free(netsnmp_container *container);

    int rdbmsDbLimitedResourceTable_row_prep( rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBLIMITEDRESOURCETABLE_DATA_ACCESS_H */
