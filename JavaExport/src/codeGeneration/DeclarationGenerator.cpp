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

#include "DeclarationGenerator.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/declarations/Class.h"
#include "OOModel/src/declarations/Project.h"
#include "OOModel/src/declarations/TypeAlias.h"
#include "OOModel/src/declarations/Module.h"
#include "OOModel/src/declarations/NameImport.h"
#include "OOModel/src/declarations/VariableDeclaration.h"
#include "OOModel/src/declarations/ExplicitTemplateInstantiation.h"
namespace JavaExport
{

DeclarationGenerator::DeclarationGenerator(Config config)
	:CodeElementGenerator(config)
{
	// TODO Auto-generated constructor stub
}

DeclarationGenerator::~DeclarationGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* DeclarationGenerator::generate(OOModel::Declaration* declaration) const
{

	if(auto c = dynamic_cast<OOModel::Class*>(declaration))
		return generate(c);
	else if(auto tmpl = dynamic_cast<OOModel::ExplicitTemplateInstantiation*>(declaration))
			return generate(tmpl);
	else if(auto field = dynamic_cast<OOModel::Field*>(declaration))
		return generate(field);
	else if(auto method = dynamic_cast<OOModel::Method*>(declaration))
		return generate(method);
	else if(auto module = dynamic_cast<OOModel::Module*>(declaration))
		return generate(module);
	else if(auto nameImport = dynamic_cast<OOModel::NameImport*>(declaration))
		return generate(nameImport);
	else if(auto project = dynamic_cast<OOModel::Project*>(declaration))
		return generate(project);
	else if(auto typeAlias = dynamic_cast<OOModel::TypeAlias*>(declaration))
		return generate(typeAlias);
	else if(auto variableDeclaration = dynamic_cast<OOModel::VariableDeclaration*>(declaration))
		return generate(variableDeclaration);
	else
		return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::Class* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::Field* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::Method* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::Module* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::NameImport* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::Project* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::TypeAlias* declaration) const
{
	return unimplemented(declaration);
}

CodeElement* DeclarationGenerator::generate(OOModel::VariableDeclaration* declaration) const
{
	return unimplemented(declaration);
}


CodeElement* JavaExport::DeclarationGenerator::generate(OOModel::ExplicitTemplateInstantiation* declaration) const
{
	return unimplemented(declaration);
}

} /* namespace JavaExport */
