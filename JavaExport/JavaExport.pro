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
HEADERS += src/javaCodeGeneration/JavaStatementItemGenerator.h \
    src/codeGeneration/StatementItemGenerator.h \
    src/javaCodeGeneration/JavaElementGenerator.h \
    src/codeGeneration/ElementGenerator.h \
    src/javaCodeGeneration/JavaConfig.h \
    src/codeGeneration/ScopeLayout.h \
    src/codeGeneration/CodeElementGenerator.h \
    src/codeGeneration/AbstractDeclarationGenerator.h \
    src/javaCodeGeneration/declarationGenerators/JavaDeclarationGenerator.h \
    src/javaCodeGeneration/expressionGenerators/ExpressionGenerator.h \
    src/javaCodeGeneration/declarationGenerators/VariableDeclarationGenerator.h \
    src/javaCodeGeneration/elementGenerators/ModifierGenerator.h \
    src/javaCodeGeneration/declarationGenerators/ModuleGenerator.h \
    src/javaCodeGeneration/declarationGenerators/ClassGenerator.h \
    src/javaCodeGeneration/declarationGenerators/ProjectGenerator.h \
    src/javaCodeGeneration/JavaCodeGenerator.h \
    src/codeGeneration/CodeElement.h \
    src/codeGeneration/CodeGenerator.h \
    src/codeGeneration/FileController.h \
    src/codeGeneration/FileCreator.h \
    src/codeGeneration/LayoutConfig.h \
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
SOURCES += src/javaCodeGeneration/JavaStatementItemGenerator.cpp \
    src/codeGeneration/StatementItemGenerator.cpp \
    src/javaCodeGeneration/JavaElementGenerator.cpp \
    src/codeGeneration/ElementGenerator.cpp \
    src/javaCodeGeneration/JavaConfig.cpp \
    src/codeGeneration/ScopeLayout.cpp \
    src/codeGeneration/CodeElementGenerator.cpp \
    src/codeGeneration/AbstractDeclarationGenerator.cpp \
    src/javaCodeGeneration/declarationGenerators/JavaDeclarationGenerator.cpp \
    src/javaCodeGeneration/expressionGenerators/ExpressionGenerator.cpp \
    src/javaCodeGeneration/declarationGenerators/VariableDeclarationGenerator.cpp \
    src/javaCodeGeneration/elementGenerators/ModifierGenerator.cpp \
    src/javaCodeGeneration/declarationGenerators/ModuleGenerator.cpp \
    src/javaCodeGeneration/declarationGenerators/ClassGenerator.cpp \
    src/javaCodeGeneration/declarationGenerators/ProjectGenerator.cpp \
    src/javaCodeGeneration/JavaCodeGenerator.cpp \
    src/codeGeneration/CodeElement.cpp \
    src/codeGeneration/CodeGenerator.cpp \
    src/codeGeneration/FileController.cpp \
    src/codeGeneration/FileCreator.cpp \
    src/codeGeneration/LayoutConfig.cpp \
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
