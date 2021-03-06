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

#include "expression_editor/OperatorDescriptor.h"

namespace Interaction {

OperatorDescriptor::OperatorDescriptor() {
}

OperatorDescriptor::~OperatorDescriptor() {
}

OperatorDescriptor::OperatorDescriptor(const QString& name, const QString& signature, int num_operands, int precedence, Associativity associativity)
	: name_(name), num_operands_(num_operands), precedence_(precedence), associativity_(associativity), transient_(false)
{
	signature_ = signature.split(" ", QString::SkipEmptyParts);
	signature_.replaceInStrings("SPACE", " ");

	// Compute prefix
	for(int i = 0; i < signature_.size() && signature_.at(i) != "expr" && signature_.at(i) != "id"; ++i)
		prefix_.append( signature_.at(i) );

	// Compute posfix
	for(int i = signature_.size()-1; i>=0 && signature_.at(i) != "expr" && signature_.at(i) != "id" ; --i)
		postfix_.prepend( signature_.at(i) );

	// Compute infixes
	infixes_ = delimiters();
	infixes_.removeAll("");
	if ( !prefix_.isEmpty() ) infixes_.removeFirst();
	if ( !postfix_.isEmpty() ) infixes_.removeLast();
}

QStringList OperatorDescriptor::delimiters()
{
	QStringList l;
	l.append("");

	for (int i = 0; i< signature_.size(); ++i)
	{
		if (signature_.at(i) == "expr" || signature_.at(i) == "id") l.append("");
		else l.last().append( signature_.at(i) );
	}

	return l;
}


}
