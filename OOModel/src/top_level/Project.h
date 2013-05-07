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

#include "../oomodel_api.h"

#include "../attributeMacros.h"
#include "Module.h"
#include "Class.h"
#include "Method.h"
#include "Field.h"

#include "ModelBase/src/nodes/Extendable/ExtendableNode.h"
#include "ModelBase/src/nodes/Text.h"
#include "ModelBase/src/nodes/TypedList.h"
#include "ModelBase/src/nodes/nodeMacros.h"

DECLARE_TYPED_LIST(OOMODEL_API, OOModel, Project)

namespace OOModel {

class OOMODEL_API Project : public Reflect<Model::ExtendableNode>
{
	EXTENDABLENODE_DECLARE_STANDARD_METHODS(Project)

	ATTRIBUTE_OOP_NAME
	ATTRIBUTE(Model::TypedList<Project>, projects, setProjects)
	ATTRIBUTE(Model::TypedList<Module>, modules, setModules)
	ATTRIBUTE(Model::TypedList<Class>, classes, setClasses)
	ATTRIBUTE(Model::TypedList<Method>, methods, setMethods)
	ATTRIBUTE(Model::TypedList<Field>, fields, setFields)

	public:
		Project(const QString& name);

		virtual bool definesSymbol() const;
		virtual const QString& symbolName() const;

		virtual QList<Node*> findSymbols(const QRegExp& symbolExp, Node* source, FindSymbolMode mode,
				bool exhaustAllScopes) override;
};

}
