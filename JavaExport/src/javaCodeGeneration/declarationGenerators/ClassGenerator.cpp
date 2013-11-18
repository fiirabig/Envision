/*
 * ClassGenerator.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#include "ClassGenerator.h"

namespace JavaExport {

ClassGenerator::ClassGenerator()
{
	// TODO Auto-generated constructor stub
}

ClassGenerator::~ClassGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* ClassGenerator::generate(OOModel::Class* c) const
{
	auto code = new Code(c);

	auto classHeader = new Code(c);
	*code << classHeader;
	*classHeader << c->modifiers() << " class " << c->name();
	//TODO: base classes & type arguments

	auto body = curlyBraces(c);
	*code << body;

	auto classes = new Code(c);
	*body << classes;
	for(auto innerClass: *c->classes())
		*body << innerClass;

	auto fields = new Code(c);
	*body << fields;
	for(auto field: *c->fields())
		*fields << field;

	auto methods = new Code(c);
	*body << methods;
	for(auto method : *c->methods())
		*methods << method;

	//TODO: enum... check for completeness...

	return code;
}

} /* namespace JavaExport */
