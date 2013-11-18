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

#include "FileController.h"
#include "CodeElement.h"

namespace JavaExport {


FileController::FileController(LayoutConfig config,SourceFile* file):
		//qFile_("source_code/bla")
		qFile_(file->parentDirectory()->qDir().absolutePath() + "/" + file->name() + "." + file->fileExtension()),
		config_(config)
{
	qDebug() << file;
	if(!qFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		Q_ASSERT(false && "can't open file");
	stream_.setDevice(&qFile_);
	stream_.setCodec("UTF-8");
}

FileController::~FileController()
{
	Q_ASSERT(openScopes_.isEmpty());
	qFile_.close();

}

void FileController::print(const QString& text)
{
	qDebug() << "printing to file" << text << flush;
	stream_ << text;
	cursor_.advanceSymbol(text.size());
	//TODO: map
	qDebug() << "finished printing to file" << flush;
}

void FileController::openScope(const LayoutConfig::ScopeLayout& scope)
{
	//openScopes_.append(scope);
	if(scope.newLineBeforOpen) printNewLine();
	//qDebug() << scope.openString;
	print(scope.openString);
	if(scope.indented) indent_++;
	if(scope.newLineAfterOpen) printNewLine();
}

void FileController::closeScope(const LayoutConfig::ScopeLayout& scope)
{
	//Q_ASSERT(!openScopes_.isEmpty());
	//LayoutConfig::ScopeLayout scope = openScopes_.takeLast();
	if(scope.indented) indent_--;
	if(scope.newLineBeforeClose) printNewLine();
	print(scope.closeString);
	if(scope.newLineAfterClose) printNewLine();
}


void FileController::printIndent()
{
	Q_ASSERT(indent_ >= 0);

	for(int i = 0; i < indent_; i++) {
		print(config_.indentString());
	}
}

void FileController::printNewLine()
{
	stream_ << endl;
	cursor_.advanceLine();
	printIndent();
}


} /* namespace JavaExport */
