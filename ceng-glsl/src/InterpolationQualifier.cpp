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
	: INonTerminal(NonTerminalType::interpolation_qualifier),interpolation(InterpolationQualifierType::unused)
{

}

InterpolationQualifier::InterpolationQualifier(const Token& token)
	: INonTerminal(NonTerminalType::interpolation_qualifier)
{
	switch (token.type)
	{
	case TokenType::keyword_smooth:
		interpolation = InterpolationQualifierType::smooth;
		break;
	case TokenType::keyword_noperspective:
		interpolation = InterpolationQualifierType::noperspective;
		break;
	case TokenType::keyword_flat:
		interpolation = InterpolationQualifierType::flat;
		break;
	default:
		interpolation = InterpolationQualifierType::invalid_value;
		break;
	}
}

InterpolationQualifier::InterpolationQualifier(InterpolationQualifierType::value interpolation)
	: INonTerminal(NonTerminalType::interpolation_qualifier), interpolation(interpolation)
{

}

Ceng::StringUtf8 InterpolationQualifier::ToString(unsigned int indentLevel) const
{
	switch (interpolation)
	{
	case InterpolationQualifierType::flat:
		return "flat";
	case InterpolationQualifierType::noperspective:
		return "noperspective";
	case InterpolationQualifierType::smooth:
		return "smooth";
	case InterpolationQualifierType::unused:
		return "";
	default:
		return "InterpolationQualifierType::unhandled";
	}

}

void InterpolationQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_InterpolationQualifier(*this);
}