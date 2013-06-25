/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2012 ETH Zurich
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


#include "SourcePrinter.h"

namespace JavaExport {

SourcePrinter::SourcePrinter(QString filename, SourceToASTMap& map ,int indentWidth):
				filename_(filename),
				file_(filename_),
				print_(&file_),
				map_(map),
				cursor_(0,0),
				indentWidth_(indentWidth),
				indent_(0)
{
	if (!file_.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "problem with file " + file_.fileName();

		Q_ASSERT(false);
		//TODO: exception
	}
	//Todo : add filename to map
}


SourcePrinter::~SourcePrinter()
{
	// TODO Auto-generated destructor stub
}

void SourcePrinter::print(QString text) {
	print_ << text;
	cursor_.second += text.length();
}

void SourcePrinter::printNewLineAndIndent(IndentChangeInfo info) {
	print_ << endl;
	cursor_.first ++;
	cursor_.second = 0;
	switch(info) {
		case NoChange : break;
		case IncrementIndent : incrIndent(); break;
		case DecrementIndent : decrIndent(); break;
		default : Q_ASSERT(false);
	}
	printIndent();
}

void SourcePrinter::printIndent() {
	for(int i = 0; i < indent_; i++) {
		for(int j = 0; j < indentWidth_; j++) {
			print_ << " ";
		}
		cursor_.second += indentWidth_;
	}
}

void SourcePrinter::incrIndent() {
	indent_ ++;
}

void SourcePrinter::decrIndent() {
	indent_ --;
	Q_ASSERT(indent_ >= 0);
}

//TODO: remove
void SourcePrinter::flush()
{
	print_.flush();
}
void SourcePrinter::startPrinting(Model::Node* node) {
	map_.startNode(cursor_, node);
}
void SourcePrinter::endPrinting(Model::Node* node) {
	map_.endNode(cursor_, node);
}

} /* namespace JavaExport */
