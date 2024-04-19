#ifndef CENG_GLSL_SYMBOL_LINK_H
#define CENG_GLSL_SYMBOL_LINK_H

#include <vector>

#include "Symbol.h"

namespace Ceng
{
	struct SymbolLink
	{
	private:
		std::vector<Symbol>* data;
		size_t index;

	public:

		SymbolLink()
			: data(nullptr), index(0)
		{

		}

		SymbolLink(std::vector<Symbol>* data, size_t index)
			: data(data), index(index)
		{

		}

		Symbol* Get() const
		{
			return &(*data)[index];
		}

		bool Valid() const
		{
			return data != nullptr;
		}
	};

}

#endif