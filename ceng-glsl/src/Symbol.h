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

	const char* ToString(SymbolType::value type);

	class Declaration;
	class FunctionPrototype;
	class StructSpecifier;
	class ParameterDeclaration;

	class Symbol
	{
	public:

		Symbol* parent;

		// Index of this symbol in parent's scope
		Ceng::UINT32 childIndex;

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
		std::shared_ptr<FunctionPrototype> prototype;
		std::shared_ptr<ParameterDeclaration> param;

		std::vector<Symbol> scope;

	public:

		Symbol(Symbol* parent, Ceng::UINT32 childIndex);

		Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<Declaration>& decl, Ceng::UINT32 index);

		Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<StructSpecifier>& structSpec);

		Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<FunctionPrototype>& prototype);

		Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<ParameterDeclaration> param);

		const Ceng::StringUtf8* Name() const;

		bool IsTypeName() const;
	};
	
}

#endif