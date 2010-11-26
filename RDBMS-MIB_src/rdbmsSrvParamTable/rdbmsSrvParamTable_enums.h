/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_enums.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_enums.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVPARAMTABLE_ENUMS_H
#define RDBMSSRVPARAMTABLE_ENUMS_H

#ifdef __cplusplus
extern "C" {
#endif

 /*
 * NOTES on enums
 * ==============
 *
 * Value Mapping
 * -------------
 * If the values for your data type don't exactly match the
 * possible values defined by the mib, you should map them
 * below. For example, a boolean flag (1/0) is usually represented
 * as a TruthValue in a MIB, which maps to the values (1/2).
 *
 */
/*************************************************************************
 *************************************************************************
 *
 * enum definitions for table rdbmsSrvParamTable
 *
 *************************************************************************
 *************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVPARAMTABLE_ENUMS_H */
