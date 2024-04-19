#ifndef CENG_GLSL_SYMBOL_NODE_H
#define CENG_GLSL_SYMBOL_NODE_H

#include <ceng/datatypes/ce-string.h>

#include "INonTerminal.h"

#include "SymbolLink.h"

namespace Ceng
{
	struct SymbolNode
	{
		SymbolNode* parent;

		// Index of this symbol in parent's scope
		Ceng::UINT32 childIndex;

		std::vector<SymbolNode> scope;

		SymbolLink link;

		SymbolNode()
			: parent(nullptr), childIndex(0)
		{

		}

		SymbolNode(const SymbolLink& link, SymbolNode* parent, Ceng::UINT32 childIndex)
			: link(link), parent(parent), childIndex(childIndex)
		{

		}

		Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const
		{
			Symbol* symbol = link.Get();

			Ceng::StringUtf8 out;

			out += INonTerminal::GetIndent(indentLevel);

			if (symbol->undefined)
			{
				out += "undefined ";
			}

			out += SymbolType::ToString(symbol->symbolType);

			const Ceng::StringUtf8* name = symbol->Name();

			if (name != nullptr)
			{
				out += ' ';
				out += *name;
			}

			out += '\n';

			for (auto& x : scope)
			{
				out += x.ToString(indentLevel + 1);
			}

			return out;
		}
	};
}

#endif