/*-------------------------------------------------------------------------
 * rdbmsDbTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_interface.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_INTERFACE_H
#define RDBMSDBTABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsDbTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsDbTable_initialize_interface(rdbmsDbTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsDbTable_rowreq_ctx * rdbmsDbTable_allocate_rowreq_ctx(void);
void rdbmsDbTable_release_rowreq_ctx(rdbmsDbTable_rowreq_ctx *rowreq_ctx);

int rdbmsDbTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsDbTable_mib_index *mib_idx);
int rdbmsDbTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsDbTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsDbTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_INTERFACE_H */
