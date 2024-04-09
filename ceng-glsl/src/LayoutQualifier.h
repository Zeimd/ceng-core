#ifndef CENG_GLSL_LAYOUT_QUALIFIER_H
#define CENG_GLSL_LAYOUT_QUALIFIER_H

#include "INonTerminal.h"

namespace Ceng
{
	class LayoutQualifierIdList;

	class LayoutQualifier : public INonTerminal
	{
	public:
		std::shared_ptr<LayoutQualifierIdList> list;

	public:

		~LayoutQualifier() override;

		void Release() override;

		LayoutQualifier(std::shared_ptr<LayoutQualifierIdList>& list);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif