#include <ceng/GLSL/Token.h>

#include "InterpolationQualifier.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

InterpolationQualifier::~InterpolationQualifier()
{

}

void InterpolationQualifier::Release()
{
	delete this;
}

InterpolationQualifier::InterpolationQualifier()
	: INonTerminal(NonTerminalType::interpolation_qualifier),interpolation(GLSL::InterpolationQualifierType::unused)
{

}

InterpolationQualifier::InterpolationQualifier(const Token& token)
	: INonTerminal(NonTerminalType::interpolation_qualifier)
{
	switch (token.type)
	{
	case TokenType::keyword_smooth:
		interpolation = GLSL::InterpolationQualifierType::smooth;
		break;
	case TokenType::keyword_noperspective:
		interpolation = GLSL::InterpolationQualifierType::noperspective;
		break;
	case TokenType::keyword_flat:
		interpolation = GLSL::InterpolationQualifierType::flat;
		break;
	default:
		interpolation = GLSL::InterpolationQualifierType::invalid_value;
		break;
	}
}

InterpolationQualifier::InterpolationQualifier(GLSL::InterpolationQualifierType::value interpolation)
	: INonTerminal(NonTerminalType::interpolation_qualifier), interpolation(interpolation)
{

}

Ceng::StringUtf8 InterpolationQualifier::ToString(unsigned int indentLevel) const
{
	switch (interpolation)
	{
	case GLSL::InterpolationQualifierType::flat:
		return "flat";
	case GLSL::InterpolationQualifierType::noperspective:
		return "noperspective";
	case GLSL::InterpolationQualifierType::smooth:
		return "smooth";
	case GLSL::InterpolationQualifierType::unused:
		return "";
	default:
		return "InterpolationQualifierType::unhandled";
	}

}

void InterpolationQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_InterpolationQualifier(*this);
}