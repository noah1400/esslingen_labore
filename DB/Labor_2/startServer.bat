db2start
db2stop
db2 terminate
set db2instance=DEVELOP
db2set DB2COMM=TCPIP
update dbm cfg using SVCENAME db2c_develop
db2start
