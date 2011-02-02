/***********************************************************************************************************************
 * HelloWorldTest.cpp
 *
 *  Created on: Feb 1, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "oovisualization.h"
#include "SelfTest/headers/SelfTestSuite.h"
#include "vis/VVisibility.h"
#include "vis/VStatic.h"
#include "vis/VOOReference.h"

#include "OOModel/headers/Project.h"
#include "OOModel/headers/Class.h"
#include "OOModel/headers/Module.h"
#include "OOModel/headers/FormalArgument.h"
#include "OOModel/headers/Field.h"
#include "OOModel/headers/types/NamedType.h"
#include "OOModel/headers/expressions/StringLiteral.h"
#include "OOModel/headers/expressions/VariableAccess.h"
#include "OOModel/headers/expressions/ReferenceExpression.h"
#include "OOModel/headers/statements/MethodCallStatement.h"
#include "OOModel/headers/TypedListInstantiations.h"
#include "OOModel/headers/common/Visibility.h"
#include "OOModel/headers/common/Static.h"

#include "VisualizationBase/headers/VisualizationManager.h"
#include "VisualizationBase/headers/Scene.h"
#include "VisualizationBase/headers/views/MainView.h"
#include "VisualizationBase/headers/ModelRenderer.h"
#include "VisualizationBase/headers/items/VExtendable.h"
#include "VisualizationBase/headers/items/VText.h"
#include "VisualizationBase/headers/items/VList.h"

#include "ModelBase/headers/Model.h"

#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

using namespace OOModel;
using namespace Visualization;

namespace OOVisualization {

TEST(OOVisualization, JavaLibraryAndHelloWorldTest)
{
	Scene* scene = new Scene();

	scene->defaultRenderer()->registerVisualization(Visibility::typeIdStatic(), createVisualization<VVisibility, Visibility>);
	scene->defaultRenderer()->registerVisualization(Static::typeIdStatic(), createVisualization<VStatic, Static>);
	scene->defaultRenderer()->registerVisualization(OOReference::typeIdStatic(), createVisualization<VOOReference, OOReference>);

	////////////////////////////////////////////////// Create Model
	Model::Model* model = new Model::Model();
	Project* prj = dynamic_cast<Project*> (model->createRoot("Project"));

	model->beginModification(prj, "build simple java library and a hello world app");
	prj->setName("HelloWorld");

	// Build a simple Java Library
	Project* java = prj->libraries()->append<Project>();
	java->setName("Java");

	Class* string = java->classes()->append<Class>();
	string->setName("String");
	string->setVisibility(Visibility::PUBLIC);

	Module* io = java->modules()->append<Module>();
	io->setName("io");

	Class* printstream = io->classes()->append<Class>();
	printstream->setName("PrintStream");
	printstream->setVisibility(Visibility::PUBLIC);

	Method* println = printstream->methods()->append<Method>();
	println->setName("println");
	println->setVisibility(Visibility::PUBLIC);

	FormalArgument* arg = println->arguments()->append<FormalArgument>();
	arg->setName("x");
	NamedType* argType = arg->setType<NamedType>();
	argType->type()->set("class:String");

	Class* system = java->classes()->append<Class>();
	system->setName("System");
	system->setVisibility(Visibility::PUBLIC);
	Field* out = system->fields()->append<Field>();
	out->setName("out");
	out->setVisibility(Visibility::PUBLIC);
	out->setStat(Static::CLASS_VARIABLE);
	NamedType* outtype = out->setType<NamedType>();
	outtype->type()->set("mod:io,class:PrintStream");

	// Build a simple HelloWorld Application
	Class* hello = prj->classes()->append<Class>();
	hello->setName("HelloWorld");
	hello->setVisibility(Visibility::PUBLIC);
	Method* main = hello->methods()->append<Method>();

	main->setName("main");
	main->setVisibility(Visibility::PUBLIC);
	main->setStat(Static::CLASS_VARIABLE);
	//TODO make an array argument

	MethodCallStatement* callPrintln = main->items()->append<MethodCallStatement>();
	StringLiteral* helloStr = callPrintln->arguments()->append<StringLiteral>();
	helloStr->setValue("Hello World");
	callPrintln->ref()->set("met:println");

	VariableAccess* va = callPrintln->setPrefix<VariableAccess>();
	va->ref()->set("field:out");

	ReferenceExpression* ref = va->setPrefix<ReferenceExpression>();
	ref->ref()->set("lib:Java,class:System");

	model->endModification();
	CHECK_STR_EQUAL("Java", java->name());

	////////////////////////////////////////////////// Set Scene

	scene->addTopLevelItem( scene->defaultRenderer()->render(NULL, prj) );
	scene->scheduleUpdate();

	// Create view
	MainView* view = new MainView(scene);

	CHECK_CONDITION(view != NULL);
}

}
