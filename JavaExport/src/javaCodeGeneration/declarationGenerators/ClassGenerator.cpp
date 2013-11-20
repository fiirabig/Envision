/*
 * ClassGenerator.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#include "ClassGenerator.h"

namespace JavaExport {

ClassGenerator::ClassGenerator(Config config): CodeElementGenerator(config)
{
	// TODO Auto-generated constructor stub
}

ClassGenerator::~ClassGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* ClassGenerator::generate(OOModel::Class* c) const
{
	/*
		 from Declaration
		ATTRIBUTE_OOP_ANNOTATIONS //TODO: ask mitko
		ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations) //TODO: ask mitko

		ATTRIBUTE(Model::TypedList<Expression>, baseClasses, setBaseClasses)//TODO: ask mitko about interfaces
		PRIVATE_ATTRIBUTE_VALUE(Model::Integer, cKind, setCKind, int) //TODO: ask mikto
	*/

		auto code = new Code(c);

		auto classHeader = new Code(c);
		*code << classHeader;
		*classHeader << c->modifiers() << " class " << c->name();

		*classHeader << new Sequence(c->typeArguments(),"<"," ,",">");

		bool first = true;
		bool second = true;
		*classHeader << new Ignore(c->baseClasses());
		for(auto base :*c->baseClasses())
		{
			if(first)
			{
				*code << " extends " << base;
				first = false;
			}
			else if(second)
			{
				*code << " implements " << base;
				second = false;
			}
			else
				*code << " ," << base;
		}

		auto body = curlyBraces(c);
		*code << body;
		*body << c->classes()  << c->enumerators() << c->fields() << c->methods();

		//TODO: enum... testcases check for completeness...

		//TODO: check with mitko
		//Illegal in Java
		if(c->friends()->size())
			*code << new NotAllowed(c->friends(),"in Java there is no concept of friends");
		else
			*code << new Ignore(c->friends());

		return code;
}

} /* namespace JavaExport */
