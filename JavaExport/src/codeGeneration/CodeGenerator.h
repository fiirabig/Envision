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
#include "FileController.h"
#include "FileCreator.h"
#include "Config.h"
#include "CodeElement.h"

namespace OOModel
{
	class Declaration;
	class Statement;
	class Expression;
}
namespace Model
{
	class Node;
}
namespace JavaExport
{

class SourceDirectory;

class CodeGenerator
{
public:
	CodeGenerator(Config config);
	virtual ~CodeGenerator();
	void printSourceFiles(Model::Node* root, const QString outputDirectory);
	virtual Config& config();
	virtual CodeElement* generate(Model::Node* node) const{return new CodeElement(node);};

private:
	bool removeDir(const QString & dirName);
	CodeElement* print(CodeElement* element);
	void map(FileController::Cursor cursor, Model::Node* node);
	Config config_;

	class ScopeElement : public CodeElement
	{
	public:
		ScopeElement(Model::Node* owner, ScopeLayout scopeLayout):
			CodeElement(owner), scopeLayout_(scopeLayout){}
	inline const ScopeLayout& scopeLayout() const{ return scopeLayout_; }
	private:
		const ScopeLayout scopeLayout_;
	};

	class OpenScope : public ScopeElement
	{
	public:
		OpenScope(Model::Node* owner,ScopeLayout scopeLayout):
			ScopeElement(owner,scopeLayout){}
	};

	class CloseScope : public ScopeElement
	{
	public:
		CloseScope(Model::Node* owner, ScopeLayout scopeLayout):
			ScopeElement(owner,scopeLayout){}
	};

};

inline Config& CodeGenerator::config() {return config_;}


} /* namespace JavaExport */
