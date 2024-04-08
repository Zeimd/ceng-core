#include "FunctionIdentifier.h"

#include "AST_Visitor.h"

using namespace Ceng;

void FunctionIdentifier::Release()
{
	delete this;
}

FunctionIdentifier::FunctionIdentifier(std::shared_ptr<TypeSpecifier>& typeSpec)
	: INonTerminal(NonTerminalType::function_identifier), typeSpec(typeSpec), funcType(FunctionType::constructor)
{

}

FunctionIdentifier::FunctionIdentifier(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::function_identifier), name(name), typeSpec(nullptr), funcType(FunctionType::normal)
{

}

Ceng::StringUtf8 FunctionIdentifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (funcType)
	{
	case FunctionType::constructor:
		return typeSpec->ToString(indentLevel);
	case FunctionType::normal:
		return name;
	default:
		return "<UNHANDLED FUNCTION INDENTIFIER TYPE>";
	}
}

void FunctionIdentifier::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_FunctionIdentifier(*this);
}