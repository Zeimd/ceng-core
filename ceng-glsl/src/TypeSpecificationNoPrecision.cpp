#include "TypeSpecifierNoPrecision.h"

using namespace Ceng;

void TypeSpecifierNoPrec::Release()
{
	delete this;
}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec),isArray(false)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec, const ConstantExpression& elementExpression)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec), isArray(true), elementExpression(elementExpression)
{

}