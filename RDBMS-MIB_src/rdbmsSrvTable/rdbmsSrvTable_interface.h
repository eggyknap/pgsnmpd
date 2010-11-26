/*-------------------------------------------------------------------------
 * rdbmsSrvTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_interface.h,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVTABLE_INTERFACE_H
#define RDBMSSRVTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsSrvTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsSrvTable_initialize_interface(rdbmsSrvTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsSrvTable_rowreq_ctx * rdbmsSrvTable_allocate_rowreq_ctx(void);
void rdbmsSrvTable_release_rowreq_ctx(rdbmsSrvTable_rowreq_ctx *rowreq_ctx);

int rdbmsSrvTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsSrvTable_mib_index *mib_idx);
int rdbmsSrvTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsSrvTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsSrvTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVTABLE_INTERFACE_H */
