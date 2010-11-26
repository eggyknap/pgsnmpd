/*-------------------------------------------------------------------------
 * rdbmsDbLimitedResourceTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbLimitedResourceTable_oids.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBLIMITEDRESOURCETABLE_OIDS_H
#define RDBMSDBLIMITEDRESOURCETABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsDbLimitedResourceTable */
#define RDBMSDBLIMITEDRESOURCETABLE_OID              1,3,6,1,2,1,39,1,4
#define COLUMN_RDBMSDBLIMITEDRESOURCENAME		1
#define COLUMN_RDBMSDBLIMITEDRESOURCEID		2
#define COLUMN_RDBMSDBLIMITEDRESOURCELIMIT		3
#define COLUMN_RDBMSDBLIMITEDRESOURCECURRENT		4
#define COLUMN_RDBMSDBLIMITEDRESOURCEHIGHWATER		5
#define COLUMN_RDBMSDBLIMITEDRESOURCEFAILURES		6
#define COLUMN_RDBMSDBLIMITEDRESOURCEDESCRIPTION		7

#define RDBMSDBLIMITEDRESOURCETABLE_MIN_COL		COLUMN_RDBMSDBLIMITEDRESOURCEID
#define RDBMSDBLIMITEDRESOURCETABLE_MAX_COL		COLUMN_RDBMSDBLIMITEDRESOURCEDESCRIPTION


#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBLIMITEDRESOURCETABLE_OIDS_H */
