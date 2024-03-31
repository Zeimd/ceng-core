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
		};
	}

	class Token;

	class ParameterQualifier : public INonTerminal
	{
	public:

		ParameterQualifierType::value type;

	public:

		~ParameterQualifier() override;

		void Release() override;

		ParameterQualifier();

		ParameterQualifier(const Token& token);

		ParameterQualifier(ParameterQualifierType::value type);
	
		Ceng::StringUtf8 ToString() const override;

		static ParameterQualifierType::value TokenToType(const Token& token);
	};
}

#endif