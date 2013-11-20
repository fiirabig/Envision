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
	CodeGenerator(Config config);
	virtual ~CodeGenerator();
	void printSourceFiles(Model::Node* root, const QString outputDirectory);
	virtual Config& config();

private:
	bool removeDir(const QString & dirName);
	CodeElement* print(CodeElement* element);
	void map(FileController::Cursor cursor, Model::Node* node);
	virtual CodeElement* generate(Model::Node* node) const{return new CodeElement(node);};
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
