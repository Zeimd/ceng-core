#ifndef CENG_GLSL_SYMBOL_H
#define CENG_GLSL_SYMBOL_H

#include <memory>
#include <vector>

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

		const char* ToString(SymbolType::value type);
	}

	

	class Declaration;
	class FunctionPrototype;
	class StructSpecifier;
	class ParameterDeclaration;
	class Condition;
	class FunctionCallOrMethod;

	class Symbol
	{
	public:
		FilePosition declarePosition;
		FilePosition lastUse;
		FilePosition endOfScope;

		SymbolType::value symbolType;

		bool isConst;
		bool isInteger;

		bool undefined;

		// Variable declaration can be found under condition instead of the usual declaration.
		bool variableIsCondition;

		// If declaration statement provides multiple variables,
		// which one is it
		Ceng::UINT32 declIndex;
	
		std::shared_ptr<Declaration> decl;
		std::shared_ptr<StructSpecifier> structSpec;
		std::shared_ptr<FunctionPrototype> prototype;
		std::shared_ptr<ParameterDeclaration> param;
		std::shared_ptr<Condition> condition;

		Ceng::StringUtf8 undefinedName;

	public:

		// Scope
		Symbol();

		Symbol(SymbolType::value type, const Ceng::StringUtf8& undefinedName);

		Symbol(std::shared_ptr<Declaration>& decl, Ceng::UINT32 index);

		Symbol(std::shared_ptr<StructSpecifier>& structSpec);

		Symbol(std::shared_ptr<FunctionPrototype>& prototype);

		Symbol(std::shared_ptr<ParameterDeclaration> param);

		Symbol(std::shared_ptr<Condition>& condition);

		const Ceng::StringUtf8* Name() const;

		bool IsTypeName() const;

		Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;
	};
	
}

#endif