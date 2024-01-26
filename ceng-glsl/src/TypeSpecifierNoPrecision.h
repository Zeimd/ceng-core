#ifndef CENG_GLSL_TYPE_SPEC_NO_PREC_H
#define CENG_GLSL_TYPE_SPEC_NO_PREC_H

#include "INonTerminal.h"
#include "TypeSpecifierNoArray.h"
#include "ConstantExpression.h"
#include "Expression.h"

namespace Ceng
{
	class TypeSpecifierNoPrec : public INonTerminal
	{
	public:
		std::shared_ptr<TypeSpecifierNoArray> typeSpec;

		bool isArray;
		std::shared_ptr<Expression> elementExpression;

	public:

		void Release() override;

		TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec);

		TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec, bool undefinedArray);

		TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec, std::shared_ptr<Expression>& elementExpression);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif