/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_interface.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVINFOTABLE_INTERFACE_H
#define RDBMSSRVINFOTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsSrvInfoTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsSrvInfoTable_initialize_interface(rdbmsSrvInfoTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsSrvInfoTable_rowreq_ctx * rdbmsSrvInfoTable_allocate_rowreq_ctx(void);
void rdbmsSrvInfoTable_release_rowreq_ctx(rdbmsSrvInfoTable_rowreq_ctx *rowreq_ctx);

int rdbmsSrvInfoTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsSrvInfoTable_mib_index *mib_idx);
int rdbmsSrvInfoTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsSrvInfoTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsSrvInfoTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVINFOTABLE_INTERFACE_H */
