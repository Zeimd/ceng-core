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
	: INonTerminal(NonTerminalType::parameter_qualifier), qualifier(ParameterQualifierType::empty)
{

}

ParameterQualifier::ParameterQualifier(const Token& token)
	: INonTerminal(NonTerminalType::parameter_qualifier)
{
	qualifier = TokenToType(token);
}

ParameterQualifier::ParameterQualifier(ParameterQualifierType::value qualifier)
	: INonTerminal(NonTerminalType::parameter_qualifier), qualifier(qualifier)
{

}

Ceng::StringUtf8 ParameterQualifier::ToString(unsigned int indentLevel) const
{
	switch (qualifier)
	{
	case ParameterQualifierType::empty:
		return "";
	case ParameterQualifierType::in:
		return "in";
	case ParameterQualifierType::out:
		return "out";
	case ParameterQualifierType::inout:
		return "inout";
	case ParameterQualifierType::invalid_value:
		return "<invalid>";
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

	return ParameterQualifierType::invalid_value;
}