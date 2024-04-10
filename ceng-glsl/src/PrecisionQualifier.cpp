#include <ceng/GLSL/Token.h>

#include "PrecisionQualifier.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

PrecisionQualifier::~PrecisionQualifier()
{

}

void PrecisionQualifier::Release()
{
	delete this;
}

PrecisionQualifier::PrecisionQualifier()
	: INonTerminal(NonTerminalType::precision_qualifier), precision(GLSL::PrecisionQualifierType::unassigned)
{

}

PrecisionQualifier::PrecisionQualifier(const Token& token)
	: INonTerminal(NonTerminalType::precision_qualifier)
{
	switch (token.type)
	{
	case TokenType::keyword_low_precision:
		precision = GLSL::PrecisionQualifierType::low;
		break;
	case TokenType::keyword_medium_precision:
		precision = GLSL::PrecisionQualifierType::medium;
		break;
	case TokenType::keyword_high_precision:
		precision = GLSL::PrecisionQualifierType::high;
		break;
	default:
		precision = GLSL::PrecisionQualifierType::invalid_value;
	}
}

PrecisionQualifier::PrecisionQualifier(GLSL::PrecisionQualifierType::value precision)
	: INonTerminal(NonTerminalType::precision_qualifier), precision(precision)
{

}

#define CASE_TO_TEXT(x) case GLSL::PrecisionQualifierType::x: out += #x; break;

Ceng::StringUtf8 PrecisionQualifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (precision)
	{
		CASE_TO_TEXT(high);
		CASE_TO_TEXT(medium);
		CASE_TO_TEXT(low);
	case GLSL::PrecisionQualifierType::invalid_value:
		return "<INVALID PRECISION TYPE>";
	default:
		return "<UNHANDLED PRECISION TYPE>";
	}

	return out;
}

#undef CASE_TO_TEXT

void PrecisionQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_PrecisionQualifier(*this);
}