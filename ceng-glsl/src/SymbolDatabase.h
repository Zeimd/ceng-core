#ifndef CENG_GLSL_SYMBOL_DATABASE_H
#define CENG_GLSL_SYMBOL_DATABASE_H

#include "INonTerminal.h"
#include "Symbol.h"

#include "SymbolLink.h"
#include "SymbolNode.h"

#include <ceng/GLSL/BasicType.h>

namespace Ceng
{
	class FunctionPrototype;
	class FunctionCallOrMethod;
	class Condition;

	class SymbolDatabase
	{
	private:

		std::vector<Symbol> builtIns;

		std::vector<Symbol> data;

		SymbolNode root;

		SymbolNode* top;

	public:

		SymbolDatabase();

		void StartScope();
		void EndScope();

		void InitBuiltIns();

		// Add built-in function with one parameter
		void AddSimpleFunction(const Ceng::StringUtf8&name, std::vector<GLSL::BasicType::value> variants, Ceng::UINT32 numParams);

		void AddSimpleFunction_Ret_Common(const Ceng::StringUtf8& name, GLSL::BasicType::value returnType, 
			std::vector<GLSL::BasicType::value> variants, Ceng::UINT32 numParams);

		void StartFunction(std::shared_ptr<FunctionPrototype>& prototype);

		SymbolLink AddUndefined(SymbolType::value type, const Ceng::StringUtf8& name);

		Ceng::INT32 Add(std::shared_ptr<Declaration>& decl);

		Ceng::INT32 Add(std::shared_ptr<StructSpecifier>& structSpec);

		Ceng::INT32 Add(std::shared_ptr<Condition>& condition);

		SymbolLink Find(const Ceng::StringUtf8& name) const;

		// Finds all functions with the given name. AST generation stage can use this
		// information to match function calls.
		std::vector<SymbolLink> FindFunctions(const Ceng::StringUtf8& name);

		bool IsCustomType(const Ceng::StringUtf8& name) const;

		Ceng::StringUtf8 ToString() const;

	private:

		void AddNode();
	};
}

#endif