#ifndef CENG_GLSL_SYMBOL_DATABASE_H
#define CENG_GLSL_SYMBOL_DATABASE_H

#include "Symbol.h"

namespace Ceng
{
	class FunctionPrototype;

	class SymbolDatabase
	{
	private:

		Symbol root;

		Symbol* top;

	public:

		SymbolDatabase();

		Symbol& StartScope();
		Symbol& EndScope();

		Symbol& StartFunction(std::shared_ptr<FunctionPrototype>& prototype);

		Symbol& Top();

		Ceng::INT32 Add(std::shared_ptr<Declaration>& decl);

		Ceng::INT32 Add(std::shared_ptr<StructSpecifier>& structSpec);

		Symbol* Find(const Ceng::StringUtf8& name) const;
	};
}

#endif