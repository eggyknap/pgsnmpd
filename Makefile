# $PostgreSQL: pgsql/contrib/pgsnmp/Makefile,v 1.05 2005/11/10 11:03:07 saito Exp $

PROGRAM = pgsnmpd

OBJS	= pgsnmpd.o \
          RDBMS-MIB_src/rdbmsDbTable/rdbmsDbTable.o RDBMS-MIB_src/rdbmsDbTable/rdbmsDbTable_data_access.o  RDBMS-MIB_src/rdbmsDbTable/rdbmsDbTable_data_get.o \
          RDBMS-MIB_src/rdbmsDbTable/rdbmsDbTable_data_set.o  RDBMS-MIB_src/rdbmsDbTable/rdbmsDbTable_interface.o \
          RDBMS-MIB_src/rdbmsDbInfoTable/rdbmsDbInfoTable.o RDBMS-MIB_src/rdbmsDbInfoTable/rdbmsDbInfoTable_data_access.o  \
    	  RDBMS-MIB_src/rdbmsDbInfoTable/rdbmsDbInfoTable_data_get.o  RDBMS-MIB_src/rdbmsDbInfoTable/rdbmsDbInfoTable_interface.o \
          RDBMS-MIB_src/rdbmsDbParamTable/rdbmsDbParamTable.o RDBMS-MIB_src/rdbmsDbParamTable/rdbmsDbParamTable_data_access.o \
    	  RDBMS-MIB_src/rdbmsDbParamTable/rdbmsDbParamTable_data_get.o  RDBMS-MIB_src/rdbmsDbParamTable/rdbmsDbParamTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsDbParamTable/rdbmsDbParamTable_interface.o \
          RDBMS-MIB_src/rdbmsSrvTable/rdbmsSrvTable_interface.o \
    	  RDBMS-MIB_src/rdbmsSrvTable/rdbmsSrvTable.o RDBMS-MIB_src/rdbmsSrvTable/rdbmsSrvTable_data_access.o \
    	  RDBMS-MIB_src/rdbmsSrvTable/rdbmsSrvTable_data_get.o RDBMS-MIB_src/rdbmsSrvTable/rdbmsSrvTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsSrvParamTable/rdbmsSrvParamTable.o RDBMS-MIB_src/rdbmsSrvParamTable/rdbmsSrvParamTable_data_access.o \
    	  RDBMS-MIB_src/rdbmsSrvParamTable/rdbmsSrvParamTable_data_get.o RDBMS-MIB_src/rdbmsSrvParamTable/rdbmsSrvParamTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsSrvParamTable/rdbmsSrvParamTable_interface.o \
    	  RDBMS-MIB_src/rdbmsSrvInfoTable/rdbmsSrvInfoTable.o RDBMS-MIB_src/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_access.o \
    	  RDBMS-MIB_src/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_get.o RDBMS-MIB_src/rdbmsSrvInfoTable/rdbmsSrvInfoTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsSrvInfoTable/rdbmsSrvInfoTable_interface.o \
    	  RDBMS-MIB_src/rdbmsRelTable/rdbmsRelTable.o RDBMS-MIB_src/rdbmsRelTable/rdbmsRelTable_data_access.o \
    	  RDBMS-MIB_src/rdbmsRelTable/rdbmsRelTable_data_get.o RDBMS-MIB_src/rdbmsRelTable/rdbmsRelTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsRelTable/rdbmsRelTable_interface.o \
    	  RDBMS-MIB_src/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable.o RDBMS-MIB_src/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_set.o \
    	  RDBMS-MIB_src/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_access.o RDBMS-MIB_src/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_interface.o \
    	  RDBMS-MIB_src/rdbmsDbLimitedResourceTable/rdbmsDbLimitedResourceTable_data_get.o  \
          customquery.o \
          query_reader.o \
    	  pg_array.o

SNMPFLAGS=-I. -I./RDBMS-MIB_src $(shell net-snmp-config --cflags)
AGENTLIBS=$(shell net-snmp-config --agent-libs)

PG_CPPFLAGS = -O0 -g -I$(libpq_srcdir) $(SNMPFLAGS)
PG_LIBS = $(libpq_pgport) $(AGENTLIBS) -lyaml

DOCS = README.pgsnmpd

DATA = pgsnmpd.conf pgsnmpd.sql 

ifndef DONT_USE_PGXS
PGXS := $(shell pg_config --pgxs)
include $(PGXS)
else
subdir = contrib/pgsnmpd
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
