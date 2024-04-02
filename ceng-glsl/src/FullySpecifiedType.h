#ifndef CENG_GLSL_FULLY_SPECIFIED_TYPE_H
#define CENG_GLSL_FULLY_SPECIFIED_TYPE_H

#include "INonTerminal.h"
#include "TypeQualifier.h"
#include "TypeSpecifier.h"

namespace Ceng
{
	class FullySpecifiedType : public INonTerminal
	{
	public:

		TypeQualifier qualifier;
		TypeSpecifier typeSpec;
	
	protected:

	public:

		void Release() override;

		FullySpecifiedType(const TypeSpecifier& typeSpec);
		FullySpecifiedType(const TypeQualifier& qualifier, const TypeSpecifier& typeSpec);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif