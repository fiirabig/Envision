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
HEADERS += src/errorview.h \
    src/codeGeneration/ASTMapper.h \
    src/javaCodeGeneration/ExpressionGenerator.h \
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
    src/SourceToASTMap.h \
    src/precompiled.h \
    src/JavaExportException.h \
    src/javaexport_api.h \
    src/javaexport.h
SOURCES += src/errorview.cpp \
    src/codeGeneration/ASTMapper.cpp \
    src/javaCodeGeneration/ExpressionGenerator.cpp \
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
    src/SourceToASTMap.cpp \
    src/JavaExportException.cpp \
    src/javaexport.cpp \
    test/SimpleTest.cpp
FORMS = src/errorview.ui
