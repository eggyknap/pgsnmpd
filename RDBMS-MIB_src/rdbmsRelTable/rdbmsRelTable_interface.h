/*-------------------------------------------------------------------------
 * rdbmsRelTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_interface.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSRELTABLE_INTERFACE_H
#define RDBMSRELTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsRelTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsRelTable_initialize_interface(rdbmsRelTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsRelTable_rowreq_ctx * rdbmsRelTable_allocate_rowreq_ctx(void);
void rdbmsRelTable_release_rowreq_ctx(rdbmsRelTable_rowreq_ctx *rowreq_ctx);

int rdbmsRelTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsRelTable_mib_index *mib_idx);
int rdbmsRelTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsRelTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsRelTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSRELTABLE_INTERFACE_H */
