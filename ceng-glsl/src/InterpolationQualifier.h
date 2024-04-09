#ifndef CENG_GLSL_INTERPOLATION_QUALIFIER_H
#define CENG_GLSL_INTERPOLATION_QUALIFIER_H

#include "INonTerminal.h"
#include "InterpolationQualifierType.h"

namespace Ceng
{
	class Token;

	class InterpolationQualifier : public INonTerminal
	{
	public:

		InterpolationQualifierType::value interpolation;

	public:

		~InterpolationQualifier() override;

		void Release() override;

		InterpolationQualifier();

		InterpolationQualifier(const Token& token);
	
		InterpolationQualifier(InterpolationQualifierType::value interpolation);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif