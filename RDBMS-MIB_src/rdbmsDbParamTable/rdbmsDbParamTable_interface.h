/*-------------------------------------------------------------------------
 * rdbmsDbParamTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable_interface.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBPARAMTABLE_INTERFACE_H
#define RDBMSDBPARAMTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsDbParamTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsDbParamTable_initialize_interface(rdbmsDbParamTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsDbParamTable_rowreq_ctx * rdbmsDbParamTable_allocate_rowreq_ctx(void);
void rdbmsDbParamTable_release_rowreq_ctx(rdbmsDbParamTable_rowreq_ctx *rowreq_ctx);

int rdbmsDbParamTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsDbParamTable_mib_index *mib_idx);
int rdbmsDbParamTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsDbParamTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsDbParamTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBPARAMTABLE_INTERFACE_H */
