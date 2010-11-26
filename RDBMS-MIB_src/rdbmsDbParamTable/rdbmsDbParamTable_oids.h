/*-------------------------------------------------------------------------
 * rdbmsDbParamTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbParamTable_oids.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBPARAMTABLE_OIDS_H
#define RDBMSDBPARAMTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsDbParamTable */
#define RDBMSDBPARAMTABLE_OID              1,3,6,1,2,1,39,1,3
#define COLUMN_RDBMSDBPARAMNAME		1
#define COLUMN_RDBMSDBPARAMSUBINDEX		2
#define COLUMN_RDBMSDBPARAMID		3
#define COLUMN_RDBMSDBPARAMCURRVALUE		4
#define COLUMN_RDBMSDBPARAMCOMMENT		5

#define RDBMSDBPARAMTABLE_MIN_COL		COLUMN_RDBMSDBPARAMID
#define RDBMSDBPARAMTABLE_MAX_COL		COLUMN_RDBMSDBPARAMCOMMENT


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBPARAMTABLE_OIDS_H */
