#include "ParameterDeclarator.h"

#include "TypeSpecifier.h"
#include "Expression.h"

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

Ceng::StringUtf8 ParameterDeclarator::ToString() const
{
	Ceng::StringUtf8 out;

	out = typeSpec->ToString();
	out += ' ';
	out += name;

	if (arraySize != nullptr)
	{
		out += '[';
		out += arraySize->ToString();
		out += ']';
	}

	return out;
}