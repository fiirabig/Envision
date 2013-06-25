/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 **      following disclaimer.
 **    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 **      following disclaimer in the documentation and/or other materials provided with the distribution.
 **    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
 **      derived from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 ** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 ** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 ** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 **********************************************************************************************************************/

#include "javaexport.h"
#include "SourceToASTMap.h"
#include "SourcePrinter.h"
#include "SelfTest/src/SelfTestSuite.h"
#include "OOModel/src/allOOModelNodes.h"
#include "SourceBuilder.h"
#include "FilePersistence/src/FileStore.h"
using namespace OOModel;

namespace JavaExport {

TEST(JavaExport, SimpleTest)
{
	/*Model::Model* model = new Model::Model();
	auto prj = dynamic_cast<Project*> (model->createRoot("Project"));
	model->beginModification(prj, "create a few classes");
	*/

	qDebug() << "***************************************************";
	// test writing file
	QDir dir;
	dir.mkdir("bla");
	QFile file("bla/bla2.txt");
	QTextStream out(&file);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	out << "hallo";

	// test loading project
	QString testDir = "projects/";
	Model::Model* model = new Model::Model();
	FilePersistence::FileStore store;
	store.setBaseFolder(testDir);

	model->load(&store, "large");
	auto prj = dynamic_cast<OOModel::Project*> (model->root());
	qDebug() << "building source for project: " << prj->name() << endl;

	SourceBuilder* builder = new SourceBuilder("output");
	qDebug() << "builder ok " << builder << endl;

	builder->createSourceFromModel(model, "output");

	/*Class* baseClass = new Class("BaseClass",Visibility::PUBLIC);
		prj->classes()->append(baseClass);

	Class* testClass = new Class("TestClass",Visibility::PUBLIC);
		testClass->baseClasses()->append(new ReferenceExpression("BaseClass"));
		prj->classes()->append(testClass);

	Class* genericClassWithNoBounds = new Class("GenericClassWithNoBounds",Visibility::PUBLIC);
		prj->classes()->append(genericClassWithNoBounds);
		auto genericTypeWithNoBounds = new FormalTypeArgument("T",nullptr,nullptr);
		genericClassWithNoBounds->typeArguments()->append(genericTypeWithNoBounds);

	Class* genericClassWith2TypeArgs = new Class("GenericClassWith2TypeArgs",Visibility::PUBLIC);
		prj->classes()->append(genericClassWith2TypeArgs);
		auto genericTypeWithNoBounds1 = new FormalTypeArgument("T",nullptr,nullptr);
		genericClassWith2TypeArgs->typeArguments()->append(genericTypeWithNoBounds1);
		auto genericTypeWithNoBounds2 = new FormalTypeArgument("G",nullptr,nullptr);
		genericClassWith2TypeArgs->typeArguments()->append(genericTypeWithNoBounds2);

	Class* genericClassWith3TypeArgs = new Class("GenericClassWith3TypeArgs",Visibility::PUBLIC);
		prj->classes()->append(genericClassWith3TypeArgs);
		auto genericTypeWithNoBounds1a = new FormalTypeArgument("T",nullptr,nullptr);
		genericClassWith3TypeArgs->typeArguments()->append(genericTypeWithNoBounds1a);
		auto genericTypeWithNoBounds2a = new FormalTypeArgument("G",nullptr,nullptr);
		genericClassWith3TypeArgs->typeArguments()->append(genericTypeWithNoBounds2a);
		auto genericTypeWithNoBounds3a = new FormalTypeArgument("H",nullptr,nullptr);
		genericClassWith3TypeArgs->typeArguments()->append(genericTypeWithNoBounds3a);

	Class* classWithFields = new Class("ClassWithFields",Visibility::PUBLIC);
			prj -> classes()->append(classWithFields);

		Field* fieldWithClassType = new Field("fieldWithClassType",
			new ClassTypeExpression(new ReferenceExpression("BaseClass")));
			classWithFields->fields()->append(fieldWithClassType);

		Field* fieldWithIntType = new Field("fieldWithIntType",
			new PrimitiveTypeExpression(PrimitiveType::INT), Visibility::PUBLIC);
			classWithFields->fields()->append(fieldWithIntType);

		Field* fieldPublicBoolean = new Field("fieldPublicBoolean",
			new PrimitiveTypeExpression(PrimitiveType::BOOLEAN), Visibility::PUBLIC);
			classWithFields->fields()->append(fieldPublicBoolean);

		Field* fieldprivateFloat = new Field("fieldprivateFloat",
			new PrimitiveTypeExpression(PrimitiveType::FLOAT), Visibility::PRIVATE);
			classWithFields->fields()->append(fieldprivateFloat);

		Field* fieldprotectedLong = new Field("fieldprotectedLong",
			new PrimitiveTypeExpression(PrimitiveType::LONG), Visibility::PROTECTED);
			classWithFields->fields()->append(fieldprotectedLong);

		Field* fieldDouble = new Field("fieldDouble",
			new PrimitiveTypeExpression(PrimitiveType::DOUBLE), Visibility::DEFAULT);
			classWithFields->fields()->append(fieldDouble);

		Field* fieldChar = new Field("fieldChar",
			new PrimitiveTypeExpression(PrimitiveType::CHAR), Visibility::DEFAULT);
			classWithFields->fields()->append(fieldChar);

			auto arrayTypeExpr = new ArrayTypeExpression();
			arrayTypeExpr->setTypeExpression(new PrimitiveTypeExpression(PrimitiveType::INT));
		Field* fieldIntArray = new Field("fieldIntArray",
			arrayTypeExpr, Visibility::PRIVATE);
			classWithFields->fields()->append(fieldIntArray);

			auto arrayTypeExpr1Dim = new ArrayTypeExpression();
			arrayTypeExpr1Dim->setTypeExpression(new PrimitiveTypeExpression(PrimitiveType::FLOAT));
			auto arrayTypeExpr2Dim = new ArrayTypeExpression();
			arrayTypeExpr2Dim->setTypeExpression(arrayTypeExpr1Dim);
		Field* field2dimArray = new Field("field2dimArray",
			arrayTypeExpr, Visibility::PRIVATE);
			classWithFields->fields()->append(field2dimArray);



	//TODO: test all the types
	// -> what about types that do not exist in java?
	//TODO: field with generic type
	//TODO: multidimensional array
	//TODO: initialized fields


	model->endModification();

	SourceBuilder* sb = new SourceBuilder("source",0);
	sb->createSourceFromClass(testClass);
	sb->createSourceFromClass(baseClass);
	sb->createSourceFromClass(classWithFields);
	sb->createSourceFromClass(genericClassWithNoBounds);
	sb->createSourceFromClass(genericClassWith2TypeArgs);
	sb->createSourceFromClass(genericClassWith3TypeArgs);


	delete sb;
*/
	qDebug() << "************************************************";
	CHECK_INT_EQUAL(1,1);
	//TODO: remove
	Q_ASSERT(false && "test finished");
}

}
