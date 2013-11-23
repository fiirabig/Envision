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

//#include "filepersistence.h"
//#include "FileStore.h"
//#include "simple/SimpleTextFileStore.h"
//#include "SelfTest/src/SelfTestSuite.h"

#include "ModelBase/src/persistence/PersistedNode.h"
#include "ModelBase/src/persistence/PersistedValue.h"

#include "SelfTest/src/SelfTestSuite.h"
#include "OOModel/src/allOOModelNodes.h"

#include "FilePersistence/src/FileStore.h"
#include "FilePersistence/src/simple/SimpleTextFileStore.h"


#include "FilePersistence/src/filepersistence.h"
#include "SelfTest/src/SelfTestSuite.h"

#include "javaCodeGeneration/JavaCodeGenerator.h"
#include "src/codeGeneration/FileController.h"

using namespace OOModel;

namespace JavaExport {

TEST(JavaExport, SimpleTest)
{
	/*
	 * 	{
		PersistentStore* store{};

		if (i==0)
		{

			s->setBaseFolder(":/FilePersistence/test/persisted");
			store = s;
		}
		else if (i==1)
		{
			auto s = new SimpleTextFileStore();
			s->setBaseFolder(":/FilePersistence/test/persisted/simple");
			store = s;
		}

		typedef PersistedValue< QString >* String;
		typedef PersistedValue< QList<PersistedNode*> >* Composite;

		// Root Node
		Composite root = dynamic_cast<Composite> (store->loadCompleteNodeSubtree("units", nullptr));
	 */

//	//PersistentStore* store{};
//	auto s = new FilePersistence::SimpleTextFileStore();
//	s->setBaseFolder("/home/marti/git/Envision/DebugBuild");
//	//store = s;
//
//	//typedef Model::PersistedValue< QList<Model::PersistedNode*> >* Composite;
//	auto root = dynamic_cast<Model::Node*> (s->loadCompleteNodeSubtree("marti", nullptr));

	QString testDir = "/home/marti/git/Envision/DebugBuild";
	Model::Model* model = new Model::Model();
	FilePersistence::SimpleTextFileStore store;
	store.setBaseFolder(testDir);

	model->load(&store, "marti",false);

	JavaCodeGenerator generator;
	generator.printSourceFiles(model->root(), "source_code");
	CHECK_CONDITION(true);
	Q_ASSERT(false && "test finished");
}

}
