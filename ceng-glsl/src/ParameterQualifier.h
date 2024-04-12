#ifndef CENG_GLSL_PARAMETER_QUALIFIER_H
#define CENG_GLSL_PARAMETER_QUALIFIER_H

#include <ceng/GLSL/ParameterQualifierType.h>

#include "INonTerminal.h"

namespace Ceng
{
	class Token;

	class ParameterQualifier : public INonTerminal
	{
	public:

		GLSL::ParameterQualifierType::value qualifier;

	public:

		~ParameterQualifier() override;

		void Release() override;

		ParameterQualifier();

		ParameterQualifier(const Token& token);

		ParameterQualifier(GLSL::ParameterQualifierType::value type);
	
		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		static GLSL::ParameterQualifierType::value TokenToType(const Token& token);

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif