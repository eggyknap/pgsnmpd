/*-------------------------------------------------------------------------
 * rdbmsSrvTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvTable_oids.h,v 1.4 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVTABLE_OIDS_H
#define RDBMSSRVTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsSrvTable */
#define RDBMSSRVTABLE_OID              1,3,6,1,2,1,39,1,5
#define COLUMN_RDBMSSRVPRIVATEMIBOID		1
#define COLUMN_RDBMSSRVVENDORNAME		2
#define COLUMN_RDBMSSRVPRODUCTNAME		3
#define COLUMN_RDBMSSRVCONTACT		4

#define RDBMSSRVTABLE_MIN_COL		COLUMN_RDBMSSRVPRIVATEMIBOID
#define RDBMSSRVTABLE_MAX_COL		COLUMN_RDBMSSRVCONTACT


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVTABLE_OIDS_H */
