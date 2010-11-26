/*-------------------------------------------------------------------------
 * rdbmsSrvTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_data_access.h,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVTABLE_DATA_ACCESS_H
#define RDBMSSRVTABLE_DATA_ACCESS_H

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
 *** Table rdbmsSrvTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvTable is subid 5 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.5, length: 9
*/


    int rdbmsSrvTable_init_data(rdbmsSrvTable_registration_ptr rdbmsSrvTable_reg);


/*
 * TODO:180:o: Review rdbmsSrvTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSSRVTABLE_CACHE_TIMEOUT   60

void rdbmsSrvTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsSrvTable_cache_load(netsnmp_container *container);
void rdbmsSrvTable_cache_free(netsnmp_container *container);

    int rdbmsSrvTable_row_prep( rdbmsSrvTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVTABLE_DATA_ACCESS_H */
