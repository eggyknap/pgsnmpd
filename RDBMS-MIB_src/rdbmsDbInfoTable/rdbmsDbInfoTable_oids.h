/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_oids.h,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_OIDS_H
#define RDBMSDBINFOTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsDbInfoTable */
#define RDBMSDBINFOTABLE_OID              1,3,6,1,2,1,39,1,2
#define COLUMN_RDBMSDBINFOPRODUCTNAME		1
#define COLUMN_RDBMSDBINFOVERSION		2
#define COLUMN_RDBMSDBINFOSIZEUNITS		3
#define COLUMN_RDBMSDBINFOSIZEALLOCATED		4
#define COLUMN_RDBMSDBINFOSIZEUSED		5
#define COLUMN_RDBMSDBINFOLASTBACKUP		6

#define RDBMSDBINFOTABLE_MIN_COL		COLUMN_RDBMSDBINFOPRODUCTNAME
#define RDBMSDBINFOTABLE_MAX_COL		COLUMN_RDBMSDBINFOLASTBACKUP


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBINFOTABLE_OIDS_H */
