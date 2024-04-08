#ifndef CENG_GLSL_LAYOUT_QUALIFIER_ID_LIST_H
#define CENG_GLSL_LAYOUT_QUALIFIER_ID_LIST_H

#include <vector>
#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class LayoutQualifierId;

	class LayoutQualifierIdList : public INonTerminal
	{
	public:
		std::vector<std::shared_ptr<LayoutQualifierId>> list;
	public:
		void Release() override;

		~LayoutQualifierIdList() override;

		LayoutQualifierIdList(std::shared_ptr<LayoutQualifierId>& qualifier);

		void Append(std::shared_ptr<LayoutQualifierId>& qualifier);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif