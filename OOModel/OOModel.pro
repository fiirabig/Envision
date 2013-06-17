TARGET = oomodel
include(../Core/common_plugin.pri)
DEFINES += OOMODEL_LIBRARY
win32:LIBS += -llogger \
    -lselftest \
    -lmodelbase
HEADERS += src/elements/Modifier.h \
    src/declarations/NameImport.h \
    src/expressions/types/FunctionTypeExpression.h \
    src/types/FunctionType.h \
    src/expressions/types/TypeQualifierExpression.h \
    src/statements/DeclarationStatement.h \
    src/declarations/Field.h \
    src/declarations/Module.h \
    src/declarations/Project.h \
    src/elements/Enumerator.h \
    src/declarations/Class.h \
    src/declarations/Method.h \
    src/expressions/LambdaExpression.h \
    src/elements/CatchClause.h \
    src/statements/TryCatchFinallyStatement.h \
    src/types/ThrownExceptionType.h \
    src/expressions/ThrowExpression.h \
    src/elements/FormalTypeArgument.h \
    src/types/StringType.h \
    src/types/NullType.h \
    src/types/SymbolProviderType.h \
    src/types/ClassType.h \
    src/types/ErrorType.h \
    src/types/ArrayType.h \
    src/types/PrimitiveType.h \
    src/types/Type.h \
    src/expressions/types/ArrayTypeExpression.h \
    src/expressions/types/ClassTypeExpression.h \
    src/expressions/types/PrimitiveTypeExpression.h \
    src/expressions/types/TypeExpression.h \
    src/elements/OOReference.h \
    src/expressions/ConditionalExpression.h \
    src/OOModelException.h \
    src/allOOModelNodes.h \
    src/attributeMacros.h \
    src/elements/FormalArgument.h \
    src/elements/FormalResult.h \
    src/elements/StatementItem.h \
    src/elements/StatementItemList.h \
    src/expressions/ArrayInitializer.h \
    src/expressions/AssignmentExpression.h \
    src/expressions/BinaryOperation.h \
    src/expressions/BooleanLiteral.h \
    src/expressions/CastExpression.h \
    src/expressions/CharacterLiteral.h \
    src/expressions/CommaExpression.h \
    src/expressions/EmptyExpression.h \
    src/expressions/ErrorExpression.h \
    src/expressions/Expression.h \
    src/expressions/FloatLiteral.h \
    src/expressions/IntegerLiteral.h \
    src/expressions/MethodCallExpression.h \
    src/expressions/NewExpression.h \
    src/expressions/NullLiteral.h \
    src/expressions/ReferenceExpression.h \
    src/expressions/StringLiteral.h \
    src/expressions/ThisExpression.h \
    src/expressions/UnaryOperation.h \
    src/expressions/UnfinishedOperator.h \
    src/oomodel_api.h \
    src/precompiled.h \
    src/statements/Block.h \
    src/statements/BreakStatement.h \
    src/statements/ContinueStatement.h \
    src/statements/ExpressionStatement.h \
    src/statements/ForEachStatement.h \
    src/statements/IfStatement.h \
    src/statements/LoopStatement.h \
    src/statements/ReturnStatement.h \
    src/statements/Statement.h \
    src/statements/SwitchCase.h \
    src/statements/SwitchStatement.h \
    src/oomodel.h \
    src/types/ReferenceType.h \
    src/types/PointerType.h \
    src/expressions/types/PointerTypeExpression.h \
    src/expressions/types/ReferenceTypeExpression.h \
    src/expressions/DeleteExpression.h \
    src/declarations/Declaration.h \
    src/declarations/VariableDeclaration.h \
    src/expressions/VariableDeclarationExpression.h \
    src/declarations/TypeAlias.h \
    src/expressions/types/AutoTypeExpression.h \
    src/elements/MemberInitializer.h \
    src/expressions/TypeTraitExpression.h \
    src/expressions/TypeNameOperator.h \
    src/expressions/GlobalScopeExpression.h
SOURCES += src/elements/Modifier.cpp \
    src/declarations/NameImport.cpp \
    src/expressions/types/FunctionTypeExpression.cpp \
    src/types/FunctionType.cpp \
    src/expressions/types/TypeQualifierExpression.cpp \
    src/statements/DeclarationStatement.cpp \
    src/declarations/Field.cpp \
    src/declarations/Module.cpp \
    src/declarations/Project.cpp \
    src/elements/Enumerator.cpp \
    src/declarations/Class.cpp \
    src/declarations/Method.cpp \
    src/expressions/LambdaExpression.cpp \
    src/elements/CatchClause.cpp \
    src/statements/TryCatchFinallyStatement.cpp \
    src/types/ThrownExceptionType.cpp \
    src/expressions/ThrowExpression.cpp \
    src/elements/FormalTypeArgument.cpp \
    src/types/StringType.cpp \
    src/types/NullType.cpp \
    src/types/SymbolProviderType.cpp \
    src/types/ClassType.cpp \
    src/types/ErrorType.cpp \
    src/types/ArrayType.cpp \
    src/types/PrimitiveType.cpp \
    src/types/Type.cpp \
    src/expressions/types/ArrayTypeExpression.cpp \
    src/expressions/types/ClassTypeExpression.cpp \
    src/expressions/types/PrimitiveTypeExpression.cpp \
    src/expressions/types/TypeExpression.cpp \
    src/elements/OOReference.cpp \
    src/expressions/ConditionalExpression.cpp \
    src/expressions/AssignmentExpression.cpp \
    src/statements/ExpressionStatement.cpp \
    src/expressions/CommaExpression.cpp \
    src/expressions/UnfinishedOperator.cpp \
    src/expressions/ErrorExpression.cpp \
    src/expressions/EmptyExpression.cpp \
    src/elements/StatementItemList.cpp \
    src/expressions/ArrayInitializer.cpp \
    src/elements/FormalArgument.cpp \
    src/elements/FormalResult.cpp \
    src/elements/StatementItem.cpp \
    src/statements/ForEachStatement.cpp \
    src/expressions/UnaryOperation.cpp \
    src/expressions/ReferenceExpression.cpp \
    src/expressions/MethodCallExpression.cpp \
    test/JavaTest.cpp \
    src/statements/ReturnStatement.cpp \
    src/statements/SwitchCase.cpp \
    src/statements/SwitchStatement.cpp \
    src/statements/ContinueStatement.cpp \
    src/statements/BreakStatement.cpp \
    src/statements/LoopStatement.cpp \
    src/statements/IfStatement.cpp \
    src/statements/Block.cpp \
    src/expressions/CastExpression.cpp \
    src/expressions/BinaryOperation.cpp \
    src/expressions/NewExpression.cpp \
    src/expressions/ThisExpression.cpp \
    src/expressions/NullLiteral.cpp \
    src/expressions/CharacterLiteral.cpp \
    src/expressions/BooleanLiteral.cpp \
    src/expressions/StringLiteral.cpp \
    src/expressions/FloatLiteral.cpp \
    src/expressions/IntegerLiteral.cpp \
    src/statements/Statement.cpp \
    src/expressions/Expression.cpp \
    src/OOModelException.cpp \
    src/oomodel.cpp \
    test/SimpleTest.cpp \
    src/types/ReferenceType.cpp \
    src/types/PointerType.cpp \
    src/expressions/types/PointerTypeExpression.cpp \
    src/expressions/types/ReferenceTypeExpression.cpp \
    src/expressions/DeleteExpression.cpp \
    src/declarations/VariableDeclaration.cpp \
    src/declarations/Declaration.cpp \
    src/expressions/VariableDeclarationExpression.cpp \
    src/declarations/TypeAlias.cpp \
    src/expressions/types/AutoTypeExpression.cpp \
    src/elements/MemberInitializer.cpp \
    src/expressions/TypeTraitExpression.cpp \
    src/expressions/TypeNameOperator.cpp \
    src/expressions/GlobalScopeExpression.cpp
