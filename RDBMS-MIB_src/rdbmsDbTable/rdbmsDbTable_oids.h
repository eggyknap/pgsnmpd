/*-------------------------------------------------------------------------
 * rdbmsDbTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbTable_oids.h,v 1.2 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBTABLE_OIDS_H
#define RDBMSDBTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsDbTable */
#define RDBMSDBTABLE_OID              1,3,6,1,2,1,39,1,1
#define COLUMN_RDBMSDBINDEX		1
#define COLUMN_RDBMSDBPRIVATEMIBOID		2
#define COLUMN_RDBMSDBVENDORNAME		3
#define COLUMN_RDBMSDBNAME		4
#define COLUMN_RDBMSDBCONTACT		5

#define RDBMSDBTABLE_MIN_COL		COLUMN_RDBMSDBPRIVATEMIBOID
#define RDBMSDBTABLE_MAX_COL		COLUMN_RDBMSDBCONTACT

    /*
     * change flags for writable columns
     */
#define FLAG_RDBMSDBCONTACT       (0x1 << 0)

#define FLAG_MAX_RDBMSDBTABLE 1

    

#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBTABLE_OIDS_H */
