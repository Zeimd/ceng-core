#ifndef CENG_GLSL_STRUCT_SPECIFIER
#define CENG_GLSL_STRUCT_SPECIFIER

#include "INonTerminal.h"

namespace Ceng
{
	class StructSpecifier : public INonTerminal
	{
	public:

		StructSpecifier();

		void Release() override;

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif