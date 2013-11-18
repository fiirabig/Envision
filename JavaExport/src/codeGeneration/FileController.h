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
#include <QDir>


namespace JavaExport {
class SourceFile;

class FileController {
	public:
	struct Cursor {
		int line {};
		int symbol {};
		void advanceLine(){ line++; symbol = 0; }
		void advanceSymbol(int amount) { symbol += amount; }
	};

		FileController(LayoutConfig config,SourceFile* file);
		virtual ~FileController();
		void print(const QString&);
		void printNewLine();
		void openScope(const LayoutConfig::ScopeLayout&);
		void closeScope(const LayoutConfig::ScopeLayout&);
		Cursor cursor() const;

	private:
		void printIndent();
		QFile qFile_;
		QTextStream stream_{};
		int indent_{};
		Cursor cursor_;
		QList<LayoutConfig::ScopeLayout> openScopes_;
		LayoutConfig config_;
};

inline FileController::Cursor FileController::cursor() const {return cursor_; }

} /* namespace JavaExport */
