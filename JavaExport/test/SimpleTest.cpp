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

#include "src/errorview.h"
#include <QtCore/QProcess>

#include "VisualizationBase/src/VisualizationManager.h"
#include "VisualizationBase/src/Scene.h"
#include "VisualizationBase/src/items/RootItem.h"

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
using namespace Visualization;
namespace JavaExport {

TEST(JavaExport, SimpleTest)
{

	QString testDir = "/home/marti/git/Envision/DebugBuild/persisted_tests";
	Model::Model* model = new Model::Model();
	auto store = new FilePersistence::SimpleTextFileStore();
	store->setBaseFolder(testDir);

	model->load(store, "test",false);


	JavaCodeGenerator generator;
	generator.printSourceFiles(model->root(), "source_code");

	CHECK_CONDITION(true);

}

}