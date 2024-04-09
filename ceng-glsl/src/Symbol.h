#ifndef CENG_GLSL_SYMBOL_H
#define CENG_GLSL_SYMBOL_H

#include <ceng/datatypes/ce-string.h>

#include <ceng/GLSL/FilePosition.h>

namespace Ceng
{
	namespace SymbolType
	{
		enum value
		{
			variable,
			function,
			function_prototype,
			function_parameter,
			struct_declaration,
			interface_block,
			interface_block_instance,
			scope,
		};
	}

	class Declaration;
	class FunctionPrototype;
	class StructSpecifier;

	class Symbol
	{
	public:
		FilePosition declarePosition;
		FilePosition lastUse;
		FilePosition endOfScope;

		SymbolType::value symbolType;

		bool isConst;
		bool isInteger;

		// If declaration statement provides multiple variables,
		// which one is it
		Ceng::UINT32 declIndex;
	
		std::shared_ptr<Declaration> decl;
		std::shared_ptr<StructSpecifier> structSpec;

		std::vector<Symbol> scope;

	public:

		// Used for scope
		Symbol();

		Symbol(std::shared_ptr<Declaration>& decl, Ceng::UINT32 index);

		Symbol(std::shared_ptr<StructSpecifier>& structSpec);

		bool IsTypeName() const;
	};
	
}

#endif