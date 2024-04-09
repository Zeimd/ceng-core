#ifndef CENG_GLSL_SYMBOL_DATABASE_H
#define CENG_GLSL_SYMBOL_DATABASE_H

#include "Symbol.h"

namespace Ceng
{
	class SymbolDatabase
	{
	private:

		Symbol root;

		Symbol* top;

	public:

		SymbolDatabase();

		Symbol& StartScope();
		Symbol& EndScope();
	};
}

#endif