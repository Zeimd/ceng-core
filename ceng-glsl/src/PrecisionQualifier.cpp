#include "PrecisionQualifier.h"

using namespace Ceng;

void PrecisionQualifier::Release()
{
	delete this;
}

PrecisionQualifier::PrecisionQualifier()
	: INonTerminal(NonTerminalType::precision_qualifier), precision(PrecisionQualifierType::unassigned)
{

}

PrecisionQualifier::PrecisionQualifier(PrecisionQualifierType::value precision)
	: INonTerminal(NonTerminalType::precision_qualifier), precision(precision)
{

}

#define CASE_TO_TEXT(x) case PrecisionQualifierType::x: out += #x; out += ' '; break;

Ceng::StringUtf8 PrecisionQualifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (precision)
	{
		CASE_TO_TEXT(high);
		CASE_TO_TEXT(medium);
		CASE_TO_TEXT(low);
	default:
		return "";
	}

	return out;
}

#undef CASE_TO_TEXT