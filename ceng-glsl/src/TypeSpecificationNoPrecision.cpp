#include "TypeSpecifierNoPrecision.h"

using namespace Ceng;

void TypeSpecifierNoPrec::Release()
{
	delete this;
}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec),isArray(false)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec, std::shared_ptr<Expression>& elementExpression)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec), isArray(true), elementExpression(elementExpression)
{

}