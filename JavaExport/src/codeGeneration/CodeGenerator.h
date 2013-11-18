/*
 * CodeGenerator.h
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#pragma once
#include "FileController.h"
#include "FileCreator.h"
#include "LayoutConfig.h"
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
	CodeGenerator();
	virtual ~CodeGenerator();
	void printSourceFiles(Model::Node* root, const QString outputDirectory);
	virtual LayoutConfig& layoutConfig() = 0;

private:
	bool removeDir(const QString & dirName);
	CodeElement* print(CodeElement* element);
	void map(FileController::Cursor cursor, Model::Node* node);
	virtual CodeElement* generate(Model::Node* node) const{return new CodeElement(node);};

	class ScopeElement : public CodeElement
	{
	public:
		ScopeElement(Model::Node* owner, LayoutConfig::ScopeLayout scopeLayout):
			CodeElement(owner), scopeLayout_(scopeLayout){}
	inline const LayoutConfig::ScopeLayout& scopeLayout() const{ return scopeLayout_; }
	private:
		const LayoutConfig::ScopeLayout scopeLayout_;
	};

	class OpenScope : public ScopeElement
	{
	public:
		OpenScope(Model::Node* owner,LayoutConfig::ScopeLayout scopeLayout):
			ScopeElement(owner,scopeLayout){}
	};

	class CloseScope : public ScopeElement
	{
	public:
		CloseScope(Model::Node* owner, LayoutConfig::ScopeLayout scopeLayout):
			ScopeElement(owner,scopeLayout){}
	};

};

} /* namespace JavaExport */
