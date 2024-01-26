#include "SingleDeclaration.h"

using namespace Ceng;

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(false),invariant(false),
	arraySizeExpression(nullptr), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(nullptr), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(nullptr), initializer(initializer)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(arraySizeExpression), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression,
	std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(arraySizeExpression), initializer(initializer)
{

}

SingleDeclaration::SingleDeclaration(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(true),
	arraySizeExpression(nullptr), initializer(nullptr)
{

}

void SingleDeclaration::Release()
{
	delete this;
}

Ceng::StringUtf8 SingleDeclaration::ToString() const
{
	Ceng::StringUtf8 out;

	if (invariant)
	{
		out += "invariant ";
		out += name;
		return out;
	}

	out += fullType->ToString();
	out += ' ';

	if (hasName)
	{
		out += name;
	}

	if (arraySizeExpression != nullptr)
	{
		out += '[';
		out += arraySizeExpression->ToString();
		out += ']';
	}

	if (initializer != nullptr)
	{
		out += " = ";
		out += initializer->ToString();
	}

	return out;	
}