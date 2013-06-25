TARGET = javaexport
include(../Core/common_plugin.pri)
DEFINES += JAVAEXPORT_LIBRARY
win32:LIBS += -llogger \
    -lselftest \
    -lmodelbase \
    -loomodel \
    -lvisualizationbase \
    -linteractionbase \
    -loovisualization \
    -loointeraction
HEADERS += src/StatementPrinter.h \
    src/ExpressionPrinter.h \
    src/ModifierPrinter.h \
    src/ClassPrinter.h \
    src/ProjectPrinter.h \
    src/SourcePrinter.h \
    src/SourceToASTMap.h \
    src/SourceBuilder.h \
    src/precompiled.h \
    src/JavaExportException.h \
    src/javaexport_api.h \
    src/javaexport.h \
    src/ModulePrinter.h
SOURCES += src/StatementPrinter.cpp \
    src/ExpressionPrinter.cpp \
    src/ModifierPrinter.cpp \
    src/ClassPrinter.cpp \
    src/ProjectPrinter.cpp \
    src/SourcePrinter.cpp \
    src/SourceToASTMap.cpp \
    src/SourceBuilder.cpp \
    src/JavaExportException.cpp \
    src/javaexport.cpp \
    src/ModulePrinter.cpp \
    test/SimpleTest.cpp
