#!/bin/sh
#for i in *.tbldef; do j=${i/tbldef/mib}; echo $i; perl ../pgsqlMibWriter.pl < $i > $j; done
#
#cat *.mib > PGSQL-MIB
for i in `ls *.tbldef|cut -f1 -d.`
do
     echo $i.tbldef;
     if [ ! -e $i.mib ]
     then
     	echo Reprocessing $i.mib
     	perl ../pgsqlMibWriter.pl < $i.tbldef > $i.mib;
     fi
done
cat *.mib > PGSQL-MIB
