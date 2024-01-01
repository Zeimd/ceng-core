#ifndef CENG_GLSL_TYPE_SPEC_NO_PREC_H
#define CENG_GLSL_TYPE_SPEC_NO_PREC_H

#include "INonTerminal.h"
#include "TypeSpecifierNoArray.h"
#include "ConstantExpression.h"

namespace Ceng
{
	class TypeSpecifierNoPrec : public INonTerminal
	{
	public:
		TypeSpecifierNoArray typeSpec;

		bool isArray;
		ConstantExpression elementExpression;

	public:

		void Release() override;

		TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec);

		TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec, const ConstantExpression& elementExpression);
	};
}

#endif