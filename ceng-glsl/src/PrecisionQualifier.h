#ifndef CENG_GLSL_PRECISION_QUALIFIER_H
#define CENG_GLSL_PRECISION_QUALIFIER_H

#include "INonTerminal.h"
#include "PrecisionQualifierType.h"

namespace Ceng
{
	class Token;

	class PrecisionQualifier : public INonTerminal
	{
	public:

		PrecisionQualifierType::value precision;

	public:

		~PrecisionQualifier() override;

		void Release() override;

		PrecisionQualifier();
		PrecisionQualifier(const Token& token);
		PrecisionQualifier(PrecisionQualifierType::value precision);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif