#include "ParameterDeclarator.h"

#include "TypeSpecifier.h"
#include "Expression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

ParameterDeclarator::~ParameterDeclarator()
{

}

void ParameterDeclarator::Release()
{
	delete this;
}

ParameterDeclarator::ParameterDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::parameter_declarator), typeSpec(typeSpec), name(name), arraySize(nullptr)
{

}

ParameterDeclarator::ParameterDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize)
	: INonTerminal(NonTerminalType::parameter_declarator), typeSpec(typeSpec), name(name), arraySize(arraySize)
{

}

Ceng::StringUtf8 ParameterDeclarator::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = typeSpec->ToString(indentLevel);
	out += ' ';
	out += name;

	if (arraySize != nullptr)
	{
		out += '[';
		out += arraySize->ToString(indentLevel);
		out += ']';
	}

	return out;
}

void ParameterDeclarator::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_ParameterDeclarator(*this);
}