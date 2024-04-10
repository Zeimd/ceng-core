#ifndef CENG_GLSL_TYPE_SPEC_NO_ARR_H
#define CENG_GLSL_TYPE_SPEC_NO_ARR_H

#include <ceng/datatypes/ce-string.h>

#include "INonTerminal.h"
#include "StructSpecifier.h"
#include <ceng/GLSL/TokenType.h>
#include <ceng/GLSL/DataType.h>

namespace Ceng
{
	class TypeSpecifierNoArray : public INonTerminal
	{
	public:

		GLSL::DataType::value datatype;

		std::shared_ptr<StructSpecifier> structSpec;

		Ceng::StringUtf8 name;
	public:
		
		void Release() override;

		TypeSpecifierNoArray(GLSL::DataType::value datatype);
		TypeSpecifierNoArray(TokenType::value tokenType);

		TypeSpecifierNoArray(const Ceng::StringUtf8& name);
		TypeSpecifierNoArray(std::shared_ptr<StructSpecifier>& structSpec);

		static GLSL::DataType::value FromTokenType(TokenType::value tokenType);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

		bool IsIntegerType() const;
	};
}

#endif