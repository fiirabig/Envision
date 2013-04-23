TARGET = javaexport
include(../Core/common_plugin.pri)

DEFINES += JAVAEXPORT_LIBRARY
win32:LIBS += -llogger \
    -lselftest

HEADERS += src/precompiled.h \
    src/JavaExportException.h \
	src/javaexport_api.h \
    src/javaexport.h
SOURCES += src/JavaExportException.cpp \
	src/javaexport.cpp \
	test/SimpleTest.cpp
