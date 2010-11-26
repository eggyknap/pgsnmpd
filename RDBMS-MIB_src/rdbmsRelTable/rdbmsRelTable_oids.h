/*-------------------------------------------------------------------------
 * rdbmsRelTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_oids.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSRELTABLE_OIDS_H
#define RDBMSRELTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsRelTable */
#define RDBMSRELTABLE_OID              1,3,6,1,2,1,39,1,9
#define COLUMN_RDBMSRELSTATE		1
#define COLUMN_RDBMSRELACTIVETIME		2

#define RDBMSRELTABLE_MIN_COL		COLUMN_RDBMSRELSTATE
#define RDBMSRELTABLE_MAX_COL		COLUMN_RDBMSRELACTIVETIME


#ifdef __cplusplus
}
#endif

#endif /* RDBMSRELTABLE_OIDS_H */
