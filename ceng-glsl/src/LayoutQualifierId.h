#ifndef CENG_GLSL_LAYOUT_QUALIFIER_ID_H
#define CENG_GLSL_LAYOUT_QUALIFIER_ID_H

#include "INonTerminal.h"
#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	class LayoutQualifierId : public INonTerminal
	{
	public:
		Ceng::StringUtf8 identifier;
		Ceng::INT32 value;

		bool hasValue;

	public:

		~LayoutQualifierId() override;

		void Release() override;

		LayoutQualifierId(const Ceng::StringUtf8& identifier);

		LayoutQualifierId(const Ceng::StringUtf8& identifier, Ceng::INT32 value);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif