#ifndef CENG_GLSL_INTERPOLATION_QUALIFIER_H
#define CENG_GLSL_INTERPOLATION_QUALIFIER_H

#include "INonTerminal.h"
#include "InterpolationQualifierType.h"

namespace Ceng
{
	class InterpolationQualifier : public INonTerminal
	{
	public:

		InterpolationQualifierType::value interpolation;

	public:

		void Release() override;

		InterpolationQualifier();
	
		InterpolationQualifier(InterpolationQualifierType::value interpolation);
	};
}

#endif