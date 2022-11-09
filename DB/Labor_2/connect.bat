db2 uncatalog node rmtnode2
db2 uncatalog database rmtsamp2
db2 catalog tcpip node rmtnode2 remote 3.122.231.91 SERVER 50004 REMOTE_INSTANCE DEVELOP
db2 catalog database sample as rmtsamp2 at node rmtnode2 AUTHENTICATION SERVER
db2 connect to rmtsamp2 USER Administrator USING Database22ws
