/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_interface.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVPARAMTABLE_INTERFACE_H
#define RDBMSSRVPARAMTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsSrvParamTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsSrvParamTable_initialize_interface(rdbmsSrvParamTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsSrvParamTable_rowreq_ctx * rdbmsSrvParamTable_allocate_rowreq_ctx(void);
void rdbmsSrvParamTable_release_rowreq_ctx(rdbmsSrvParamTable_rowreq_ctx *rowreq_ctx);

int rdbmsSrvParamTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsSrvParamTable_mib_index *mib_idx);
int rdbmsSrvParamTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsSrvParamTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsSrvParamTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVPARAMTABLE_INTERFACE_H */
