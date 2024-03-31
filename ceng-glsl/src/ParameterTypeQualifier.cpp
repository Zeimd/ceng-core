#include <ceng/GLSL/Token.h>

#include "ParameterTypeQualifier.h"

using namespace Ceng;

ParameterTypeQualifier::~ParameterTypeQualifier()
{

}

void ParameterTypeQualifier::Release()
{
	delete this;
}

ParameterTypeQualifier::ParameterTypeQualifier(const Token& token)
	: INonTerminal(NonTerminalType::parameter_type_qualifier)
{
	qualifier = TokenToQualifier(token);
}

ParameterTypeQualifier::ParameterTypeQualifier(ParamTypeQualifiers::value qualifier)
	: INonTerminal(NonTerminalType::parameter_qualifier), qualifier(qualifier)
{

}

Ceng::StringUtf8 ParameterTypeQualifier::ToString() const
{
	switch (type)
	{
	case ParamTypeQualifiers::const_qual:
		return "const";

	default:
		return "<UNHANDLED PARAMETER TYPE QUALIFIER>";
	}
}

ParamTypeQualifiers::value ParameterTypeQualifier::TokenToQualifier(const Token& token)
{
	switch (token.type)
	{
	case TokenType::keyword_const:
		return ParamTypeQualifiers::const_qual;
	}
}