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
HEADERS += src/javaCodeGeneration/ExpressionGenerator.h \
    src/javaCodeGeneration/JavaDeclarationGenerator.h \
    src/codeGeneration/Config.h \
    src/codeGeneration/DeclarationGenerator.h \
    src/javaCodeGeneration/JavaStatementItemGenerator.h \
    src/codeGeneration/StatementItemGenerator.h \
    src/javaCodeGeneration/JavaElementGenerator.h \
    src/codeGeneration/ElementGenerator.h \
    src/javaCodeGeneration/JavaConfig.h \
    src/codeGeneration/ScopeLayout.h \
    src/codeGeneration/CodeElementGenerator.h \
    src/javaCodeGeneration/JavaCodeGenerator.h \
    src/codeGeneration/CodeElement.h \
    src/codeGeneration/CodeGenerator.h \
    src/codeGeneration/FileController.h \
    src/codeGeneration/FileCreator.h \
    src/StatementPrinter.h \
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
SOURCES += src/javaCodeGeneration/ExpressionGenerator.cpp \
    src/javaCodeGeneration/JavaDeclarationGenerator.cpp \
    src/codeGeneration/Config.cpp \
    src/codeGeneration/DeclarationGenerator.cpp \
    src/javaCodeGeneration/JavaStatementItemGenerator.cpp \
    src/codeGeneration/StatementItemGenerator.cpp \
    src/javaCodeGeneration/JavaElementGenerator.cpp \
    src/codeGeneration/ElementGenerator.cpp \
    src/javaCodeGeneration/JavaConfig.cpp \
    src/codeGeneration/ScopeLayout.cpp \
    src/codeGeneration/CodeElementGenerator.cpp \
    src/javaCodeGeneration/JavaCodeGenerator.cpp \
    src/codeGeneration/CodeElement.cpp \
    src/codeGeneration/CodeGenerator.cpp \
    src/codeGeneration/FileController.cpp \
    src/codeGeneration/FileCreator.cpp \
    src/StatementPrinter.cpp \
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
