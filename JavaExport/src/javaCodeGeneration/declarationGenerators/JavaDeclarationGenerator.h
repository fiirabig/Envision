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

#pragma once
#include "codeGeneration/AbstractDeclarationGenerator.h"
#include "ProjectGenerator.h"
#include "ModuleGenerator.h"
#include "ClassGenerator.h"
#include "VariableDeclarationGenerator.h"
#include "javaCodeGeneration/JavaConfig.h"

namespace OOModel
{
	class Declaration;
	class Class;
	class Field;
	class Method;
	class Module;
	class NameImport;
	class Project;
	class TypeAlias;
	class VariableDeclaration;
	class FormalTypeArgument;
}

namespace JavaExport
{

class JavaDeclarationGenerator: public AbstractDeclarationGenerator
{
public:
	JavaDeclarationGenerator();
	virtual ~JavaDeclarationGenerator();
	virtual CodeElement* generate(OOModel::Class* declaration) const override;
	virtual CodeElement* generate(OOModel::Field* declaration) const override;
	virtual CodeElement* generate(OOModel::Method* declaration) const override;
	virtual CodeElement* generate(OOModel::Module* declaration) const override;
	virtual CodeElement* generate(OOModel::NameImport* declaration) const override;
	virtual CodeElement* generate(OOModel::Project* declaration) const override;
	virtual CodeElement* generate(OOModel::TypeAlias* declaration) const override;
	virtual CodeElement* generate(OOModel::VariableDeclaration* declaration) const override;

private:
	const ProjectGenerator projectGenerator_{javaConfig()};
	const ModuleGenerator moduleGenerator_{javaConfig()};
	const ClassGenerator classGenerator_{javaConfig()};
	const VariableDeclarationGenerator variableDeclarationGenerator_{javaConfig()};
};


} /* namespace JavaExport */
