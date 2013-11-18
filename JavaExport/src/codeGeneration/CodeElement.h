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

#pragma once
#include "LayoutConfig.h"
#include "FileController.h"
#include <QDir>
#include "ModelBase/src/nodes/Node.h"
#include "ModelBase/src/nodes/composite/CompositeNode.h"
#include "ModelBase/src/nodes/composite/AttributeChain.h"

namespace JavaExport {
class SourceDirectory;
class SourceFile;

class CodeElement {
	public:
		CodeElement(Model::Node* owner);
		virtual ~CodeElement();
		inline Model::Node* owner() const { return owner_;}
		SourceDirectory* parentDirectory();

		void setParentDirectory(SourceDirectory* dir);
		SourceFile* sourceFile();
		void setSourceFile(SourceFile* file);
		virtual void initializeParentDirectory(CodeElement* child);
		virtual const QString toString()
		{
			return "CodeElement(" + ownerToString() + ")";
		}
		QString ownerToString() const
		{
			if(!owner()) return "nullptr";
			if(auto comp = dynamic_cast<Model::CompositeNode*>(owner()))
				return "CompositeNode(typeName: " + comp->getMetaData().typeName()
						+ " , symbolName: " + comp->symbolName() + ")";
			else return "Node(symbolName: " + owner()->symbolName() + ")";
			return "";

		}
	protected:
		Model::Node* const owner_;
		SourceDirectory* parentDirectory_{};
		SourceFile* sourceFile_{};
};
inline void CodeElement::initializeParentDirectory(CodeElement* child) {child->setParentDirectory(parentDirectory_);}
inline SourceDirectory* CodeElement::parentDirectory() {return parentDirectory_;}
inline void CodeElement::setParentDirectory(SourceDirectory* dir) {parentDirectory_ = dir;}
inline void CodeElement::setSourceFile(SourceFile* file) {sourceFile_ = file;}
inline SourceFile* CodeElement::sourceFile() {return sourceFile_;}


class SourceCodeSnippet : public CodeElement {
	public:
		SourceCodeSnippet(Model::Node* owner ,QString text)
	: CodeElement(owner),text_(text){}
		const QString& text() { return text_; }
		virtual const QString toString() override {return "SouceCodeSnippet(" + text_ + ")";}
	private:
		const QString text_;
};


class CodeElementContainer : public CodeElement {
	public:
		CodeElementContainer(Model::Node* owner) : CodeElement(owner){};
		virtual ~CodeElementContainer(){ Q_ASSERT(content().isEmpty());};
		QList<CodeElement*>& content();

		CodeElementContainer& operator<< (Model::Node* node) ;
		CodeElementContainer& operator<< (CodeElement* element) ;
		CodeElementContainer& operator<< (QString text);
		virtual const QString toString() override {
			QString string = "CodeElementContainer(";
			bool first = true;
			for(auto element : content_)
			{
				if(first) first = false;
				else string += ", ";
				string+= element->toString();
			}
			string += ")";
			return string;
		}

	protected:
		QList<CodeElement*> content_;

};

inline CodeElementContainer& CodeElementContainer::operator<< (Model::Node* node) {
	content_.append(new CodeElement(node));
	return *this;
}
inline CodeElementContainer& CodeElementContainer::operator<< (CodeElement* element) {
	content_.append(element);
	return *this;
}

inline CodeElementContainer& CodeElementContainer::operator<< (QString text) {
	content_.append(new SourceCodeSnippet(owner_,text));
	return *this;
}


inline QList<CodeElement*>& CodeElementContainer::content(){ return content_;}

class SourceDirectory : public CodeElementContainer {
	public:
		SourceDirectory(Model::Node* owner, QString name) :
			CodeElementContainer(owner),name_(name){}
		virtual ~SourceDirectory() {}
		const QString& name() const {return name_; }
		QDir& qDir();

		void setPath(QString path);
		virtual const QString toString() override
		{
			return "SourceDirectory(" + name_ + ", " + CodeElementContainer::toString() + ")";
		}

	private:
		const QString name_;
		SourceDirectory* parent_{};
		QDir qDir_{};

};


inline QDir& SourceDirectory::qDir() {return qDir_;}

inline void SourceDirectory::setPath(QString path) {qDir_.setPath(path) ;}



class SourceFile : public CodeElementContainer{
	public:
		SourceFile(Model::Node* owner, QString name,QString fileExtension):
			CodeElementContainer(owner),name_(name),fileExtension_(fileExtension){}
		virtual ~SourceFile() {delete fileController_;}
		const QString name() const {return name_;}
		const QString fileExtension() const {return fileExtension_;}
		virtual const QString toString() override {
			return "SourceFile(" + name_ + fileExtension_ + " ," + CodeElementContainer::toString() + ")";
		}
		FileController* fileController() {return fileController_;}
		void setFileController(FileController* fc) {fileController_ = fc;}
	private:
		const QString name_;
		const QString fileExtension_;
		FileController* fileController_{};
};



class Scope : public CodeElementContainer {
	public:
		Scope(Model::Node* owner, LayoutConfig::ScopeLayout scopeLayout):
			CodeElementContainer(owner), scopeLayout_(scopeLayout){};
		virtual ~Scope(){};
		const LayoutConfig::ScopeLayout& scopeLayout() const;
		virtual const QString toString() override {return "Scope(" + CodeElementContainer::toString() + ")";}

	private:
		const LayoutConfig::ScopeLayout scopeLayout_;
};

inline const LayoutConfig::ScopeLayout& Scope::scopeLayout() const { return scopeLayout_;}



class Code : public CodeElementContainer {
	public:
		Code(Model::Node* owner) : CodeElementContainer(owner){}
		virtual const QString toString() override {
			return "Code(" + CodeElementContainer::toString() + ")";
		}

};

class NewLine : public CodeElement
{
public :
	NewLine(Model::Node* owner) : CodeElement(owner){};
};

class Package : public CodeElement
{
public:
	Package(Model::Node* owner) : CodeElement(owner){};
};

class Ignore : public CodeElement
{
public:
	Ignore(Model::Node* owner) : CodeElement(owner){};
};

class Error : public CodeElement
{
public:
	Error(Model::Node* owner,QString message) : CodeElement(owner), message_(message){};
	virtual QString message() const {return message_;}
	virtual const QString toString() override {return "Error(" + ownerToString() + ", " + message_ +  ")";}

private:
	QString message_;
};

class Unimplemented : public Error
{
public:
	Unimplemented(Model::Node* owner,QString language) : Error(owner,language){};
	virtual const QString toString() override {return "Unimplemented(" + ownerToString() + ", " + message() +  ")";}
	virtual QString message() const override
	{
		return "There is no implementation for " + ownerToString() + " in " + Error::message();
	}
};

class NotAllowed : public Error
{
public:
	NotAllowed(Model::Node* owner,QString language) : Error(owner,language){};
};



//inline QList<CodeElement*> Code::children() { return children_; }

} /* namespace JavaExport */
