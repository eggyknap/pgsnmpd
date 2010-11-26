/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_interface.h,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_INTERFACE_H
#define RDBMSDBINFOTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsDbInfoTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsDbInfoTable_initialize_interface(rdbmsDbInfoTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsDbInfoTable_rowreq_ctx * rdbmsDbInfoTable_allocate_rowreq_ctx(void);
void rdbmsDbInfoTable_release_rowreq_ctx(rdbmsDbInfoTable_rowreq_ctx *rowreq_ctx);

int rdbmsDbInfoTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsDbInfoTable_mib_index *mib_idx);
int rdbmsDbInfoTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsDbInfoTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsDbInfoTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBINFOTABLE_INTERFACE_H */
