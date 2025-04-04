#include <ceng/GLSL/Token.h>

#include "ParameterQualifier.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

ParameterQualifier::~ParameterQualifier()
{

}

void ParameterQualifier::Release()
{
	delete this;
}

ParameterQualifier::ParameterQualifier()
	: INonTerminal(NonTerminalType::parameter_qualifier), qualifier(GLSL::ParameterQualifierType::empty)
{

}

ParameterQualifier::ParameterQualifier(const Token& token)
	: INonTerminal(NonTerminalType::parameter_qualifier)
{
	qualifier = TokenToType(token);
}

ParameterQualifier::ParameterQualifier(GLSL::ParameterQualifierType::value qualifier)
	: INonTerminal(NonTerminalType::parameter_qualifier), qualifier(qualifier)
{

}

Ceng::StringUtf8 ParameterQualifier::ToString(unsigned int indentLevel) const
{
	return GLSL::ParameterQualifierType::ToString(qualifier);
}

GLSL::ParameterQualifierType::value ParameterQualifier::TokenToType(const Token& token)
{
	switch (token.type)
	{
	case TokenType::keyword_in:
		return GLSL::ParameterQualifierType::in;
	case TokenType::keyword_out:
		return GLSL::ParameterQualifierType::out;
	case TokenType::keyword_inout:
		return GLSL::ParameterQualifierType::inout;
	}

	return GLSL::ParameterQualifierType::invalid_value;
}

void ParameterQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_ParameterQualifier(*this);
}