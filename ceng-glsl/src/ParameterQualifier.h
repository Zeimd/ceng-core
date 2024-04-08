#ifndef CENG_GLSL_PARAMETER_QUALIFIER_H
#define CENG_GLSL_PARAMETER_QUALIFIER_H

#include "INonTerminal.h"

namespace Ceng
{
	namespace ParameterQualifierType
	{
		enum value
		{
			empty,
			in,
			out,
			inout,
			invalid_value,
		};
	}

	class Token;

	class ParameterQualifier : public INonTerminal
	{
	public:

		ParameterQualifierType::value qualifier;

	public:

		~ParameterQualifier() override;

		void Release() override;

		ParameterQualifier();

		ParameterQualifier(const Token& token);

		ParameterQualifier(ParameterQualifierType::value type);
	
		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		static ParameterQualifierType::value TokenToType(const Token& token);

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif