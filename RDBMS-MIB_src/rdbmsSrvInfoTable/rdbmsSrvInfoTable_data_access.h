/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_data_access.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_data_access.h,v 1.3 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVINFOTABLE_DATA_ACCESS_H
#define RDBMSSRVINFOTABLE_DATA_ACCESS_H

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
 *** Table rdbmsSrvInfoTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * rdbmsSrvInfoTable is subid 6 of rdbmsObjects.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.39.1.6, length: 9
*/


    int rdbmsSrvInfoTable_init_data(rdbmsSrvInfoTable_registration_ptr rdbmsSrvInfoTable_reg);


/*
 * TODO:180:o: Review rdbmsSrvInfoTable cache timeout.
 * The number of seconds before the cache times out
 */
#define RDBMSSRVINFOTABLE_CACHE_TIMEOUT   10

void rdbmsSrvInfoTable_container_init(netsnmp_container **container_ptr_ptr,
                             netsnmp_cache *cache);
int rdbmsSrvInfoTable_cache_load(netsnmp_container *container);
void rdbmsSrvInfoTable_cache_free(netsnmp_container *container);

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
    int rdbmsSrvInfoTable_row_prep( rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVINFOTABLE_DATA_ACCESS_H */
