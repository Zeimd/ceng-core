#include "ParameterDeclaration.h"

#include "ParameterQualifier.h"
#include "ParameterTypeQualifier.h"
#include "TypeSpecifier.h"
#include "ParameterDeclarator.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

ParameterDeclaration::~ParameterDeclaration()
{

}

void ParameterDeclaration::Release()
{
	delete this;
}

ParameterDeclaration::ParameterDeclaration(std::shared_ptr<ParameterTypeQualifier>& typeQ, std::shared_ptr<ParameterQualifier>& paramQ,
	std::shared_ptr<ParameterDeclarator>& decl)
	: INonTerminal(NonTerminalType::parameter_declaration), typeQ(typeQ), paramQ(paramQ), typeOnly(false), decl(decl), typeSpec(nullptr)
{

}

ParameterDeclaration::ParameterDeclaration(std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<ParameterDeclarator>& decl)
	: INonTerminal(NonTerminalType::parameter_declaration), typeQ(nullptr), paramQ(paramQ), typeOnly(false), decl(decl), typeSpec(nullptr)
{

}

ParameterDeclaration::ParameterDeclaration(std::shared_ptr<ParameterTypeQualifier>& typeQ, std::shared_ptr<ParameterQualifier>& paramQ,
	std::shared_ptr<TypeSpecifier>& type)
	: INonTerminal(NonTerminalType::parameter_declaration), typeQ(typeQ), paramQ(paramQ), typeOnly(true), decl(nullptr), typeSpec(typeSpec)
{

}

ParameterDeclaration::ParameterDeclaration(std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<TypeSpecifier>& typeSpec)
	: INonTerminal(NonTerminalType::parameter_declaration), typeQ(nullptr), paramQ(paramQ), typeOnly(true), decl(nullptr), typeSpec(typeSpec)
{

}

Ceng::StringUtf8 ParameterDeclaration::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (typeQ != nullptr)
	{
		out += typeQ->ToString(indentLevel);
		out += ' ';
	}

	out += paramQ->ToString(indentLevel);
	out += ' ';

	if (typeOnly)
	{
		out += typeSpec->ToString(indentLevel);
	}
	else
	{
		out += decl->ToString(indentLevel);
	}

	return out;
}

void ParameterDeclaration::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_ParameterDeclaration(*this);
}