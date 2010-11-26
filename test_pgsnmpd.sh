sudo ./pgsnmpd -s -C "user=josh" -Q pgsnmpd.yaml 2>&1 &
A=$!
echo "PID: $A"
sleep 2
#snmpwalk -v 2c -c public localhost RDBMS-MIB::rdbmsDbInfoTable
#snmpwalk -v 2c -c public localhost  1.3.6.1.4.1.27645.1.3.2
#sudo strace -p $A &> strace.out &
#B=$!
#snmpwalk -v 2c -c public localhost 1.3.6.1.4.1.27645.1.3.2.1.2.1.1
snmpwalk -On -v 2c -c public localhost  1.3.6.1.4.1.27645.1.2.1
snmpwalk -On -v 2c -c public localhost  1.3.6.1.4.1.27645.1.2.2
#snmpwalk -v 2c -c public localhost  1.3.6.1.4.1.27645.1.3.3
#snmpwalk -v 2c -c public localhost  1.3.6.1.4.1.27646.1.1
#snmpwalk -v 2c -c public localhost  1.3.6.1.4.1.27646.1.2
sleep 4
sudo kill -9 $A $B
