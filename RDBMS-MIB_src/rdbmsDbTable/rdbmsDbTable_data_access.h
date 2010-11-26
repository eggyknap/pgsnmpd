/*-------------------------------------------------------------------------
 * rdbmsDbTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_data_access.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_DATA_ACCESS_H
#define RDBMSDBTABLE_DATA_ACCESS_H

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
 *** Table rdbmsDbTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbTable is subid 1 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.1, length: 9
*/


    int rdbmsDbTable_init_data(rdbmsDbTable_registration_ptr rdbmsDbTable_reg);


/*
 * TODO:180:o: Review rdbmsDbTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSDBTABLE_CACHE_TIMEOUT   60

void rdbmsDbTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsDbTable_cache_load(netsnmp_container *container);
void rdbmsDbTable_cache_free(netsnmp_container *container);

int rdbmsDbTable_row_prep( rdbmsDbTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_DATA_ACCESS_H */
