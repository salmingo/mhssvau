bin_PROGRAMS=mhssvau
mhssvau_SOURCES=IOServiceKeep.cpp tcpasio.cpp daemon.cpp GLog.cpp MessageQueue.cpp mhssvau.cpp

mhssvau_LDFLAGS = -L/usr/local/lib
BOOST_LIBS = -lboost_system-mt -lboost_thread-mt -lboost_filesystem-mt
mhssvau_LDADD = ${BOOST_LIBS} -lpthread
