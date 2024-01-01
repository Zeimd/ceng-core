#ifndef CENG_GLSL_PRECISION_QUALIFIER_H
#define CENG_GLSL_PRECISION_QUALIFIER_H

#include "INonTerminal.h"
#include "PrecisionQualifierType.h"

namespace Ceng
{
	class PrecisionQualifier : public INonTerminal
	{
	public:

		PrecisionQualifierType::value precision;

	public:

		void Release() override;

		PrecisionQualifier();
		PrecisionQualifier(PrecisionQualifierType::value precision);

	};
}

#endif