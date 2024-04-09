#include "StructDeclarator.h"
#include "Expression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;



StructDeclarator::StructDeclarator(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(false), arraySize(nullptr)
{

}

StructDeclarator::StructDeclarator(const Ceng::StringUtf8& name, bool implicitArray)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(true), arraySize(nullptr)
{

}

StructDeclarator::StructDeclarator(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(true), arraySize(arraySize)
{

}

StructDeclarator::~StructDeclarator()
{

}

void StructDeclarator::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclarator::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += name;

	if (isArray)
	{
		out += '[';

		if (arraySize != nullptr)
		{
			out += arraySize->ToString(indentLevel);
		}

		out += ']';
	}

	return out;
}

void StructDeclarator::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_StructDeclarator(*this);
}