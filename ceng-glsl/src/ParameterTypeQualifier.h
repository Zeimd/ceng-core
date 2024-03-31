#ifndef CENG_GLSL_PARAMETER_TYPE_QUALIFIER_H
#define CENG_GLSL_PARAMETER_TYPE_QUALIFIER_H

#include "INonTerminal.h"

namespace Ceng
{
	namespace ParamTypeQualifiers
	{
		enum value
		{
			const_qual,
		};
	}

	class Token;

	class ParameterTypeQualifier : public INonTerminal
	{
	public:

		ParamTypeQualifiers::value qualifier;

	public:

		~ParameterTypeQualifier() override;

		void Release() override;

		ParameterTypeQualifier(const Token& token);

		ParameterTypeQualifier(ParamTypeQualifiers::value qualifier);

		Ceng::StringUtf8 ToString() const override;

		static ParamTypeQualifiers::value TokenToQualifier(const Token& token);
	};
}

#endif