#include "TypeSpecifierNoPrecision.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void TypeSpecifierNoPrec::Release()
{
	delete this;
}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& baseType)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), baseType(baseType),isArray(false)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& baseType, bool undefinedArray)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), baseType(baseType), isArray(true), elementExpression(nullptr)
{

}

TypeSpecifierNoPrec::TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoArray>& baseType, std::shared_ptr<Expression>& elementExpression)
	: INonTerminal(NonTerminalType::type_specifier_no_prec), baseType(baseType), isArray(true), elementExpression(elementExpression)
{

}

Ceng::StringUtf8 TypeSpecifierNoPrec::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = baseType->ToString(indentLevel);

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

void TypeSpecifierNoPrec::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_TypeSpecifierNoPrec(*this);
}