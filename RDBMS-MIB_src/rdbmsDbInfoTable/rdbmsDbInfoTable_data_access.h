/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_data_access.h,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_DATA_ACCESS_H
#define RDBMSDBINFOTABLE_DATA_ACCESS_H

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
 *** Table rdbmsDbInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsDbInfoTable is subid 2 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.2, length: 9
*/


    int rdbmsDbInfoTable_init_data(rdbmsDbInfoTable_registration_ptr rdbmsDbInfoTable_reg);


/*
 * TODO:180:o: Review rdbmsDbInfoTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSDBINFOTABLE_CACHE_TIMEOUT   60

void rdbmsDbInfoTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsDbInfoTable_cache_load(netsnmp_container *container);
void rdbmsDbInfoTable_cache_free(netsnmp_container *container);

    /*
    ***************************************************
    ***             START EXAMPLE CODE              ***
    ***---------------------------------------------***/
/* *********************************************************************
 * Since we have no idea how you really access your data, we'll go with
 * a worst case example: a flat text file.
 */
#define MAX_LINE_SIZE 256
    /*
    ***---------------------------------------------***
    ***              END  EXAMPLE CODE              ***
    ***************************************************/
    int rdbmsDbInfoTable_row_prep( rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBINFOTABLE_DATA_ACCESS_H */
