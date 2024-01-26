#ifndef CENG_GLSL_LAYOUT_QUALIFIER_H
#define CENG_GLSL_LAYOUT_QUALIFIER_H

#include "INonTerminal.h"
#include "LayoutQualifierIdList.h"

namespace Ceng
{
	class LayoutQualifier : public INonTerminal
	{
	public:
		LayoutQualifierIdList list;

	public:

		LayoutQualifier();

		void Release() override;

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif