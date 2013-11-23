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
#include "OOModel/src/declarations/NameImport.h"
#include "OOModel/src/declarations/TypeAlias.h"
#include "OOModel/src/declarations/ExplicitTemplateInstantiation.h"

namespace JavaExport
{


JavaDeclarationGenerator::JavaDeclarationGenerator() : DeclarationGenerator(javaConfig()){}


CodeElement* JavaDeclarationGenerator::generate(OOModel::Field* field) const
{
	//TODO ask mitko about difference from VariableDeclaration
	//TODO: try ; enter only here, instead of in vardecl

	/*
	ATTRIBUTE_OOP_ANNOTATIONS //TODO: ask Mitko
	ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations) //TODO: ask Mitko
	 */
	auto code = new Code(field);
	*code << generate(dynamic_cast<OOModel::VariableDeclaration*>(field))
		  << ";" << new NewLine(field);
	return code;
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

	*code << method->memberInitializers();

	return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Module* module) const
{

	/*
	 * //TODO: ask mitko
	 ATTRIBUTE_OOP_NAME_SYMBOL
	 ATTRIBUTE(Modifier, modifiers, setModifiers)
	 ATTRIBUTE_OOP_ANNOTATIONS
	 ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations)
	 */

	//qDebug() << "generating module " << module->name();

	SourceDirectory* dir = new SourceDirectory(module,module->name());

	//TODO: move to method addTopLevelClass(CodeElementContainer*, TypedList<Classes>)
	for(auto c : *module->classes())
	{
		auto file = new SourceFile(c,c->name(),"java");
		*dir << file;
		*file << c;
		//TODO: add package and import
	}
	*dir << new Ignore(module->classes());

	*dir << module->modules();
	for(auto m : *module->modules())
		*dir << m;

	*dir << notAllowed(module->methods());
	*dir << notAllowed(module->fields());

	*dir << new Ignore(module->libraries());

	return dir;

	//TODO: check for completeness
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::NameImport* import) const
{
	/*
	 * //TODO: ask Mitko
	 ATTRIBUTE_OOP_NAME_SYMBOL
	 ATTRIBUTE(Modifier, modifiers, setModifiers)
	 ATTRIBUTE_OOP_ANNOTATIONS
	 ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations)

	//import all
	*/

	auto code = new Code(import);
	*code << import->importedName();

	if(import->modifiers())
		*code << new NotAllowed(import,"in Java imports don't have modifiers");

	*code << notAllowed(import->subDeclarations());

	return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Project* project) const
{
	//Ignore subdeclaration -> import java lang
	/*//TODO: ask mitko
	 *	ATTRIBUTE_OOP_NAME_SYMBOL
	ATTRIBUTE(Modifier, modifiers, setModifiers)
	ATTRIBUTE_OOP_ANNOTATIONS
	ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations)
	 */
	qDebug() << "generating project " << project->name();
		auto dir = new SourceDirectory(project,project->name());

		//TODO: move to method
		for(auto c : *project->classes())
		{
			auto file = new SourceFile(c,c->name(),"java");
			*file << c;
			*dir << file;
			//TODO: add package and imports
		}

		*dir << project->projects();
		*dir << project->modules();

		*dir << notAllowed(project->methods());

		return dir;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::TypeAlias* alias) const
{
	return notAllowed(alias);
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::VariableDeclaration* decl) const
{
	/*
	 *
	 *
	 * //TODO: ask mitko
	 *	ATTRIBUTE_OOP_NAME_SYMBOL
	ATTRIBUTE_OOP_ANNOTATIONS
	ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations)
	 */
	auto code = new Code(decl);
	*code << decl->modifiers()  << decl->typeExpression() << " " << decl->name();

	if(auto initValue = decl->initialValue())
		*code << (" = ") << initValue;

	//*code << ";" << new NewLine(decl); //TODO: check without ;
	return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::Class* c) const
{
	/*
			 from Declaration
			ATTRIBUTE_OOP_ANNOTATIONS //TODO: ask mitko
			ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations) //TODO: ask mitko

			ATTRIBUTE(Model::TypedList<Expression>, baseClasses, setBaseClasses)//TODO: ask mitko about interfaces
			PRIVATE_ATTRIBUTE_VALUE(Model::Integer, cKind, setCKind, int) //TODO: ask mikto
		*/

			auto code = new Code(c);

			auto classHeader = new Code(c);
			*code << classHeader;
			*classHeader << c->modifiers() << " class " << c->name();

			*classHeader << new Sequence(c->typeArguments(),"<",", ",">");

			bool first = true;
			bool second = true;
			*classHeader << new Ignore(c->baseClasses());
			//TODO: check with mitko
			//cant extend on enum
			for(auto base :*c->baseClasses())
			{
				if(first)
				{
					//if name is object dont print it
					//if interface also implements
					*code << " extends " << base;
					first = false;
				}
				else if(second)
				{
					*code << " implements " << base;
					second = false;
				}
				else
					*code << " ," << base;
			}

			auto body = curlyBraces(c);
			*code << body;
			*body << c->classes()  << c->enumerators() << c->fields() << c->methods();

			//TODO: enum... testcases check for completeness...

			//TODO: check with mitko
			//Illegal in Java
			if(c->friends()->size())
				*code << new NotAllowed(c->friends(),"in Java there is no concept of friends");
			else
				*code << new Ignore(c->friends());

			return code;
}

CodeElement* JavaDeclarationGenerator::generate(OOModel::ExplicitTemplateInstantiation* declaration) const
{
	//TODO: check with Mitko is this generics?
	return notAllowed(declaration);
}

} /* namespace JavaExport */


