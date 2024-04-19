#ifndef CENG_GLSL_SYMBOL_DATABASE_H
#define CENG_GLSL_SYMBOL_DATABASE_H

#include "INonTerminal.h"
#include "Symbol.h"

namespace Ceng
{
	class FunctionPrototype;
	class Condition;

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

	class SymbolDatabase
	{
	private:

		std::vector<Symbol> data;

		SymbolNode root;

		SymbolNode* top;

	public:

		SymbolDatabase();

		void StartScope();
		void EndScope();

		void StartFunction(std::shared_ptr<FunctionPrototype>& prototype);

		//Symbol& Top();

		SymbolLink AddUndefined(SymbolType::value type, const Ceng::StringUtf8& name);

		Ceng::INT32 Add(std::shared_ptr<Declaration>& decl);

		Ceng::INT32 Add(std::shared_ptr<StructSpecifier>& structSpec);

		Ceng::INT32 Add(std::shared_ptr<Condition>& condition);

		SymbolLink Find(const Ceng::StringUtf8& name) const;

		bool IsCustomType(const Ceng::StringUtf8& name) const;

		Ceng::StringUtf8 ToString() const;

	private:

		void AddNode();
	};
}

#endif