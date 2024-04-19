#ifndef CENG_GLSL_SYMBOL_DATABASE_H
#define CENG_GLSL_SYMBOL_DATABASE_H

#include "INonTerminal.h"
#include "Symbol.h"

#include "SymbolLink.h"
#include "SymbolNode.h"

namespace Ceng
{
	class FunctionPrototype;
	class Condition;

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