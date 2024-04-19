#ifndef CENG_GLSL_TYPE_SPEC_NO_ARR_H
#define CENG_GLSL_TYPE_SPEC_NO_ARR_H

#include <ceng/datatypes/ce-string.h>

#include "INonTerminal.h"
#include "StructSpecifier.h"
#include <ceng/GLSL/TokenType.h>
#include <ceng/GLSL/BasicType.h>

#include "SymbolLink.h"

namespace Ceng
{
	enum class TypeSelector
	{
		basic_type,
		struct_specifier,
		type_name,
	};

	class TypeSpecifierNoArray : public INonTerminal
	{
	public:

		TypeSelector dataType;

		GLSL::BasicType::value basicType;

		std::shared_ptr<StructSpecifier> structSpec;

		SymbolLink link;

	public:
		
		void Release() override;

		TypeSpecifierNoArray(GLSL::BasicType::value basicType);
		TypeSpecifierNoArray(TokenType::value tokenType);

		TypeSpecifierNoArray(const SymbolLink& link);
		TypeSpecifierNoArray(std::shared_ptr<StructSpecifier>& structSpec);

		static GLSL::BasicType::value FromTokenType(TokenType::value tokenType);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

		bool IsIntegerType() const;
	};
}

#endif