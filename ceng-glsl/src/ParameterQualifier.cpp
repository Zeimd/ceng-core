#include <ceng/GLSL/Token.h>

#include "ParameterQualifier.h"

using namespace Ceng;

ParameterQualifier::~ParameterQualifier()
{

}

void ParameterQualifier::Release()
{
	delete this;
}

ParameterQualifier::ParameterQualifier()
	: INonTerminal(NonTerminalType::parameter_qualifier), type(ParameterQualifierType::empty)
{

}

ParameterQualifier::ParameterQualifier(const Token& token)
	: INonTerminal(NonTerminalType::parameter_qualifier)
{
	type = TokenToType(token);
}

ParameterQualifier::ParameterQualifier(ParameterQualifierType::value type)
	: INonTerminal(NonTerminalType::parameter_qualifier), type(type)
{

}

Ceng::StringUtf8 ParameterQualifier::ToString() const
{
	switch (type)
	{
	case ParameterQualifierType::empty:
		return "";
	case ParameterQualifierType::in:
		return "in";
	case ParameterQualifierType::out:
		return "out";
	case ParameterQualifierType::inout:
		return "inout";
	default:
		return "<UNHANDLED PARAMETER QUALIFIER>";
	}
}

ParameterQualifierType::value ParameterQualifier::TokenToType(const Token& token)
{
	switch (token.type)
	{
	case TokenType::keyword_in:
		return ParameterQualifierType::in;
	case TokenType::keyword_out:
		return ParameterQualifierType::out;
	case TokenType::keyword_inout:
		return ParameterQualifierType::inout;
	}
}