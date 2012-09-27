TARGET = interactionbase
include(../Core/common_plugin.pri)
DEFINES += INTERACTIONBASE_LIBRARY
win32:LIBS += -llogger \
    -lselftest \
    -lmodelbase \
    -lfilepersistence \
    -lvisualizationbase
HEADERS += src/handlers/HActionPrompt.h \
    src/actions/ActionPromptStyle.h \
    src/actions/ActionPrompt.h \
    src/actions/Action.h \
    src/events/DetectMainSceneActivated.h \
    src/events/ShowCommandPromptEvent.h \
    src/events/SetCursorEvent.h \
    src/commands/CreateNamedObjectWithAttributes.h \
    src/expression_editor/tree_builder/LeaveUnfinished.h \
    test/HBinaryNode.h \
    src/autocomplete/AutoComplete.h \
    src/autocomplete/AutoCompleteVisStyle.h \
    src/autocomplete/AutoCompleteVis.h \
    src/autocomplete/AutoCompleteEntry.h \
    src/handlers/HRootItem.h \
    src/InteractionBaseException.h \
    src/commands/CSceneHandlerItemExit.h \
    src/commands/Command.h \
    src/commands/CommandError.h \
    src/commands/CommandExecutionEngine.h \
    src/commands/CommandHelp.h \
    src/commands/CommandResult.h \
    src/commands/CommandSuggestion.h \
    src/expression_editor/Empty.h \
    src/expression_editor/ErrorDescriptor.h \
    src/expression_editor/Expression.h \
    src/expression_editor/ExpressionContext.h \
    src/expression_editor/ExpressionEditor.h \
    src/expression_editor/ExpressionTreeUtils.h \
    src/expression_editor/ExpressionVisitor.h \
    src/expression_editor/Operator.h \
    src/expression_editor/OperatorDescriptor.h \
    src/expression_editor/OperatorDescriptorList.h \
    src/expression_editor/UnfinishedOperator.h \
    src/expression_editor/Value.h \
    src/expression_editor/parser/ParseResult.h \
    src/expression_editor/parser/Parser.h \
    src/expression_editor/parser/Token.h \
    src/expression_editor/tree_builder/AddEmptyValue.h \
    src/expression_editor/tree_builder/AddErrorOperator.h \
    src/expression_editor/tree_builder/AddOperator.h \
    src/expression_editor/tree_builder/AddValue.h \
    src/expression_editor/tree_builder/ExpressionTreeBuildInstruction.h \
    src/expression_editor/tree_builder/ExpressionTreeBuilder.h \
    src/expression_editor/tree_builder/FinishOperator.h \
    src/expression_editor/tree_builder/SkipOperatorDelimiter.h \
    src/handlers/GenericHandler.h \
    src/handlers/HCommandPrompt.h \
    src/handlers/HExtendable.h \
    src/handlers/HList.h \
    src/handlers/HPositionLayout.h \
    src/handlers/HSceneHandlerItem.h \
    src/handlers/HText.h \
    src/interactionbase_api.h \
    src/precompiled.h \
    src/vis/CommandPrompt.h \
    src/vis/CommandPromptStyle.h \
    src/vis/TextAndDescription.h \
    src/vis/TextAndDescriptionStyle.h \
    src/interactionbase.h
SOURCES += src/handlers/HActionPrompt.cpp \
    src/actions/ActionPromptStyle.cpp \
    src/actions/ActionPrompt.cpp \
    src/actions/Action.cpp \
    src/events/DetectMainSceneActivated.cpp \
    src/events/ShowCommandPromptEvent.cpp \
    src/events/SetCursorEvent.cpp \
    src/commands/CreateNamedObjectWithAttributes.cpp \
    src/expression_editor/tree_builder/LeaveUnfinished.cpp \
    test/HBinaryNode.cpp \
    src/autocomplete/AutoComplete.cpp \
    src/autocomplete/AutoCompleteVisStyle.cpp \
    src/autocomplete/AutoCompleteVis.cpp \
    src/autocomplete/AutoCompleteEntry.cpp \
    src/handlers/HRootItem.cpp \
    src/expression_editor/ExpressionVisitor.cpp \
    src/expression_editor/ExpressionEditor.cpp \
    src/expression_editor/ExpressionTreeUtils.cpp \
    src/expression_editor/parser/Parser.cpp \
    src/expression_editor/parser/ParseResult.cpp \
    src/expression_editor/parser/Token.cpp \
    src/expression_editor/tree_builder/FinishOperator.cpp \
    src/expression_editor/tree_builder/SkipOperatorDelimiter.cpp \
    src/expression_editor/tree_builder/AddValue.cpp \
    src/expression_editor/tree_builder/AddEmptyValue.cpp \
    src/expression_editor/tree_builder/AddErrorOperator.cpp \
    src/expression_editor/tree_builder/AddOperator.cpp \
    src/expression_editor/tree_builder/ExpressionTreeBuildInstruction.cpp \
    src/expression_editor/tree_builder/ExpressionTreeBuilder.cpp \
    src/expression_editor/UnfinishedOperator.cpp \
    src/expression_editor/ErrorDescriptor.cpp \
    src/expression_editor/Empty.cpp \
    src/expression_editor/ExpressionContext.cpp \
    src/expression_editor/Value.cpp \
    src/InteractionBaseException.cpp \
    src/expression_editor/Operator.cpp \
    src/expression_editor/Expression.cpp \
    src/expression_editor/OperatorDescriptorList.cpp \
    src/expression_editor/OperatorDescriptor.cpp \
    src/handlers/HPositionLayout.cpp \
    src/handlers/HList.cpp \
    src/commands/CSceneHandlerItemExit.cpp \
    src/handlers/HSceneHandlerItem.cpp \
    src/handlers/GenericHandler.cpp \
    src/handlers/HCommandPrompt.cpp \
    src/handlers/HExtendable.cpp \
    src/handlers/HText.cpp \
    src/vis/CommandPromptStyle.cpp \
    src/vis/CommandPrompt.cpp \
    src/vis/TextAndDescriptionStyle.cpp \
    src/vis/TextAndDescription.cpp \
    src/commands/CommandExecutionEngine.cpp \
    src/commands/CommandHelp.cpp \
    src/commands/CommandError.cpp \
    src/commands/CommandSuggestion.cpp \
    src/commands/CommandResult.cpp \
    src/commands/Command.cpp \
    test/SimpleTest.cpp \
    src/interactionbase.cpp
