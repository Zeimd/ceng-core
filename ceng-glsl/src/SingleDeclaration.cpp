#include "SingleDeclaration.h"

using namespace Ceng;

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(false),invariant(false),
	arraySizeExpression(nullptr), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(nullptr), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(nullptr), initializer(initializer)
{

}

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<ConstantExpression>& arraySizeExpression)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), hasName(true), invariant(false),
	arraySizeExpression(arraySizeExpression), initializer(nullptr)
{

}

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<ConstantExpression>& arraySizeExpression,
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