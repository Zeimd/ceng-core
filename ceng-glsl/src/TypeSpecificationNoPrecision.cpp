#include "TypeSpecifierNoPrecision.h"

using namespace Ceng;

TypeSpecifierNoPrec::TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec)
	: typeSpec(typeSpec),isArray(false)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec, const ConstantExpression& elementExpression)
	: typeSpec(typeSpec), isArray(true), elementExpression(elementExpression)
{

}