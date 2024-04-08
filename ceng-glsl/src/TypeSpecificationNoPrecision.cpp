#include "TypeSpecifierNoPrecision.h"

#include "AST_Visitor.h"

using namespace Ceng;

void TypeSpecifierNoPrec::Release()
{
	delete this;
}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec),isArray(false)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec, bool undefinedArray)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec), isArray(true), elementExpression(nullptr)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& typeSpec, std::shared_ptr<Expression>& elementExpression)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), typeSpec(typeSpec), isArray(true), elementExpression(elementExpression)
{

}

Ceng::StringUtf8 TypeSpecifierNoPrec::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = typeSpec->ToString(indentLevel);

	if (isArray)
	{
		out += '[';

		if (elementExpression != nullptr)
		{
			out += elementExpression->ToString(indentLevel);
		}

		out += ']';
	}


	return out;
}

void TypeSpecifierNoPrec::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_TypeSpecifierNoPrec(*this);
}