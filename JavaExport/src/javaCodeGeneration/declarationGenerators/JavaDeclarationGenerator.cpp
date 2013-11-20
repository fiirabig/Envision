/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 **      disclaimer.
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
 ***********************************************************************************************************************/

#include "JavaDeclarationGenerator.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/declarations/Project.h"
#include "OOModel/src/declarations/Module.h"
#include "OOModel/src/declarations/Class.h"
#include "OOModel/src/declarations/VariableDeclaration.h"

namespace JavaExport
{


JavaDeclarationGenerator::JavaDeclarationGenerator() : AbstractDeclarationGenerator(javaConfig())
{
	// TODO Auto-generated constructor stub
}

JavaDeclarationGenerator::~JavaDeclarationGenerator()
{
	// TODO Auto-generated destructor stub
}


CodeElement* JavaDeclarationGenerator::generate(OOModel::Field* field) const
{
	//TODO ask mitko about difference from VariableDeclaration
	return variableDeclarationGenerator_.generate(field);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Method* method) const
{
	/*
	 * from declaration:
	ATTRIBUTE_OOP_ANNOTATIONS //TODO: ask Mitko
	ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations) //TODO: ask Mitko
	 *
	PRIVATE_ATTRIBUTE_VALUE(Model::Integer, mthKind, setMthKind, int) //TODO: ask mitko
	 */

	auto code = new Code(method);
	*code << method->modifiers()
		  << new Sequence(method->typeArguments(),"<",", ",">");


	if(method->results()->size()==1)
		*code << method->results() << " ";
	//TODO: ask Mitko
//	else if(method->results()== 0 && method->methodKind() == OOModel::Method::MethodKind::Constructor)
//		*code << new Ignore(method->results());
//	else
//		*code << new NotAllowed(method->results(), "in Java a method can have only one result and this method has " +
//				QString::number(method->results()->size()));

	//enum class MethodKind : int {Default, Constructor, Destructor, Conversion};
	switch(method->methodKind())
	{
	case OOModel::Method::MethodKind::Default :
	case OOModel::Method::MethodKind::Constructor :
		//*code << new Ignore(method->mthKind()); TODO: ask Mitko to make CodeElementGenerator friend?
		break;
	case OOModel::Method::MethodKind::Destructor :
		//*code << new NotAllowed(method->mthKind(), "There are no Destructors in Java");
		break;
	case OOModel::Method::MethodKind::Conversion :
		//*code << new NotAllowed(method->mthKind(), "There are no Conversions in Java");
		break;
	default :
		Q_ASSERT(false && "missing case in switch on MethodKind");
	}

	*code << method->name()
		  << "(" << new Sequence(method->arguments(),", ") << ")";

	*code << method->items();

	//TODO: ask Mitko
	if(method->memberInitializers()->size())
		*code << notAllowed(method->memberInitializers());
	else
		*code << new Ignore(method->memberInitializers());

	return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Module* module) const
{
	return moduleGenerator_.generate(module);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::NameImport* import) const
{
	/*
	ATTRIBUTE_OOP_NAME //TODO: ask mitko
	ATTRIBUTE_OOP_ANNOTATIONS //TODO: ask mitko

	ATTRIBUTE(ReferenceExpression, importedName, setImportedName)
	*/

	auto code = new Code(import);
	*code << import->importedName();

	//TODO: ask mitko
	if(import->modifiers()) *code << new NotAllowed(import,"in Java imports don't have modifiers");
	else *code << new Ignore(import->modifiers());

	//TODO: ask mitko
	if(import->subDeclarations()->size()) *code << new NotAllowed(import, "in Java imports don't have subdeclarations");
	else *code << new Ignore(import->subDeclarations());

	return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Project* project) const
{
	return projectGenerator_.generate(project);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::TypeAlias* alias) const
{
	//TODO: ask Mitko
	return notAllowed(alias);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::VariableDeclaration* varDecl) const
{
	return variableDeclarationGenerator_.generate(varDecl);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Class* c) const
{
	return classGenerator_.generate(c);
}


} /* namespace JavaExport */
