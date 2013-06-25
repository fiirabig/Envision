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


#include "ModifierPrinter.h"

namespace JavaExport {

ModifierPrinter::ModifierPrinter(SourcePrinter& printer):
		printer_(printer)
{
	// TODO Auto-generated constructor stub

}

ModifierPrinter::~ModifierPrinter()
{
	// TODO Auto-generated destructor stub
}

void ModifierPrinter::print(OOModel::Modifier* modifier)
{
	printer_.startPrinting(modifier);
	printModifier(modifier);
	printer_.endPrinting(modifier);

}

void ModifierPrinter::printModifier(OOModel::Modifier* modifier)
{
//	enum ModifierFlag {
//				None  = 0x00000000,
//
//				Public = 0x00000001,
//				Private = 0x00000002,
//				Protected = 0x00000004,
//
//				Static = 0x00000008
//			};

	qDebug() << "printing modifier " << modifier;
	//XXX: remove hit;
	int hit = 0;
	if(modifier->isSet(OOModel::Modifier::None)) {
			printer_.print("");
			hit++;
	}if(modifier->isSet(OOModel::Modifier::Public)) {
		printer_.print("public ");
		hit++;
	}if(modifier->isSet(OOModel::Modifier::Private)) {
		printer_.print("private ");
		hit++;
	}if(modifier->isSet(OOModel::Modifier::Protected)) {
		printer_.print("protected ");
		hit++;
	}if(modifier->isSet(OOModel::Modifier::Static)) {
		printer_.print("static ");
		hit++;
	}
	Q_ASSERT(hit>0);
}
} /* namespace JavaExport */
