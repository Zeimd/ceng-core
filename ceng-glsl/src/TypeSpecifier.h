#ifndef CENG_GLSL_TYPE_SPECIFIER_H
#define CENG_GLSL_TYPE_SPECIFIER_H

#include "INonTerminal.h"
#include "TypeSpecifierNoPrecision.h"
#include "PrecisionQualifier.h"

namespace Ceng
{
	class TypeSpecifier : public INonTerminal
	{
	public:

		PrecisionQualifier precision;

		TypeSpecifierNoPrec typeSpec;

	public:

		void Release() override;

		TypeSpecifier(const TypeSpecifierNoPrec& typeSpec);
		TypeSpecifier(const PrecisionQualifier& precision, const TypeSpecifierNoPrec& typeSpec);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif