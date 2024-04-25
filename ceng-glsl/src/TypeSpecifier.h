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

		TypeSpecifierNoPrec arrayType;

	public:

		void Release() override;

		TypeSpecifier(const TypeSpecifierNoPrec& arrayType);
		TypeSpecifier(const PrecisionQualifier& precision, const TypeSpecifierNoPrec& arrayType);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

		static std::shared_ptr<TypeSpecifier> GetBasicType(GLSL::BasicType::value basicType);
	};
}

#endif