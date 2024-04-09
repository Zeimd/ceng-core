#include "SingleDeclaration.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data()
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name,initializer)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, bool undefinedArray)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name, undefinedArray)
{

}


SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, bool undefinedArray,
	std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name,undefinedArray, initializer)
{

}


SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name, arraySizeExpression)
{

}

SingleDeclaration::SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression,
	std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(false), data(name, arraySizeExpression, initializer)
{

}

SingleDeclaration::SingleDeclaration(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), invariant(true), data(name)
{

}

void SingleDeclaration::Release()
{
	delete this;
}

Ceng::StringUtf8 SingleDeclaration::ToString(unsigned int indentLevel) const
{
	return "";	
}

void SingleDeclaration::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_SingleDeclaration(*this);
}