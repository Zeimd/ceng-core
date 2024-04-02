#ifndef CENG_GLSL_LAYOUT_QUALIFIER_ID_LIST_H
#define CENG_GLSL_LAYOUT_QUALIFIER_ID_LIST_H

#include "INonTerminal.h"
#include <vector>

#include "LayoutQualifierId.h"

namespace Ceng
{
	class LayoutQualifierIdList : public INonTerminal
	{
	public:
		std::vector<LayoutQualifierId> qualifiers;
	public:
		void Release() override;

		LayoutQualifierIdList();

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif