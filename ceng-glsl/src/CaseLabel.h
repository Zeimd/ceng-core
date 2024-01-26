#ifndef CENG_GLSL_CASE_LABEL_H
#define CENG_GLSL_CASE_LABEL_H

#include "INonTerminal.h"

namespace Ceng
{
	class CaseLabel : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif