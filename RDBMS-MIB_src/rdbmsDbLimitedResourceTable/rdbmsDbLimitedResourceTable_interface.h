/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable_interface.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable_interface.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBLIMITEDRESOURCETABLE_INTERFACE_H
#define RDBMSDBLIMITEDRESOURCETABLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rdbmsDbLimitedResourceTable.h"

/* ********************************************************************
 * Table declarations
 */

/* PUBLIC interface initialization routine */
void _rdbmsDbLimitedResourceTable_initialize_interface(rdbmsDbLimitedResourceTable_registration_ptr user_ctx,
                                    u_long flags);

    rdbmsDbLimitedResourceTable_rowreq_ctx * rdbmsDbLimitedResourceTable_allocate_rowreq_ctx(void);
void rdbmsDbLimitedResourceTable_release_rowreq_ctx(rdbmsDbLimitedResourceTable_rowreq_ctx *rowreq_ctx);

int rdbmsDbLimitedResourceTable_index_to_oid(netsnmp_index *oid_idx,
                            rdbmsDbLimitedResourceTable_mib_index *mib_idx);
int rdbmsDbLimitedResourceTable_index_from_oid(netsnmp_index *oid_idx,
                              rdbmsDbLimitedResourceTable_mib_index *mib_idx);

/*
 * access to certain internals. use with caution!
 */
void rdbmsDbLimitedResourceTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBLIMITEDRESOURCETABLE_INTERFACE_H */
