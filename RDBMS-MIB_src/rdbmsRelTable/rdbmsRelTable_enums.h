/*-------------------------------------------------------------------------
 * rdbmsRelTable_enums.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsRelTable_enums.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSRELTABLE_ENUMS_H
#define RDBMSRELTABLE_ENUMS_H

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
 * enum definitions for table rdbmsRelTable
 *
 *************************************************************************
 *************************************************************************/

/*************************************************************
 * constants for enums for the MIB node
 * rdbmsRelState (INTEGER / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef RDBMSRELSTATE_ENUMS
#define RDBMSRELSTATE_ENUMS

#define RDBMSRELSTATE_OTHER  1 
#define RDBMSRELSTATE_ACTIVE  2 
#define RDBMSRELSTATE_AVAILABLE  3 
#define RDBMSRELSTATE_RESTRICTED  4 
#define RDBMSRELSTATE_UNAVAILABLE  5 


#endif /* RDBMSRELSTATE_ENUMS */

    /*
     * TODO:140:o: Define interal representation of rdbmsRelState enums.
     * (used for value mapping; see notes at top of file)
     */
#define INTERNAL_RDBMSRELSTATE_OTHER  1 
#define INTERNAL_RDBMSRELSTATE_ACTIVE  2 
#define INTERNAL_RDBMSRELSTATE_AVAILABLE  3 
#define INTERNAL_RDBMSRELSTATE_RESTRICTED  4 
#define INTERNAL_RDBMSRELSTATE_UNAVAILABLE  5 



#ifdef __cplusplus
}
#endif

#endif /* RDBMSRELTABLE_ENUMS_H */
