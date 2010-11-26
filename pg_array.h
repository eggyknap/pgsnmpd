/*-------------------------------------------------------------------------
 * pg_array.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: pg_array.h,v 1.5 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef PG_ARRAY_H
#define PG_ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **pg_text_array_parse(char* input, int *len);
void pg_text_array_free(char **array, int len);

#endif
