/*-------------------------------------------------------------------------
 * rdbmsSrvInfoTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvInfoTable_oids.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVINFOTABLE_OIDS_H
#define RDBMSSRVINFOTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsSrvInfoTable */
#define RDBMSSRVINFOTABLE_OID              1,3,6,1,2,1,39,1,6
#define COLUMN_RDBMSSRVINFOSTARTUPTIME		1
#define COLUMN_RDBMSSRVINFOFINISHEDTRANSACTIONS		2
#define COLUMN_RDBMSSRVINFODISKREADS		3
#define COLUMN_RDBMSSRVINFOLOGICALREADS		4
#define COLUMN_RDBMSSRVINFODISKWRITES		5
#define COLUMN_RDBMSSRVINFOLOGICALWRITES		6
#define COLUMN_RDBMSSRVINFOPAGEREADS		7
#define COLUMN_RDBMSSRVINFOPAGEWRITES		8
#define COLUMN_RDBMSSRVINFODISKOUTOFSPACES		9
#define COLUMN_RDBMSSRVINFOHANDLEDREQUESTS		10
#define COLUMN_RDBMSSRVINFOREQUESTRECVS		11
#define COLUMN_RDBMSSRVINFOREQUESTSENDS		12
#define COLUMN_RDBMSSRVINFOHIGHWATERINBOUNDASSOCIATIONS		13
#define COLUMN_RDBMSSRVINFOMAXINBOUNDASSOCIATIONS		14

#define RDBMSSRVINFOTABLE_MIN_COL		COLUMN_RDBMSSRVINFOSTARTUPTIME
#define RDBMSSRVINFOTABLE_MAX_COL		COLUMN_RDBMSSRVINFOMAXINBOUNDASSOCIATIONS


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVINFOTABLE_OIDS_H */
