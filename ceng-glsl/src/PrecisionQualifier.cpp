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

#define CASE_TO_TEXT(x) case PrecisionQualifierType::x: return #x;

Ceng::StringUtf8 PrecisionQualifier::ToString() const
{
	switch (precision)
	{
		CASE_TO_TEXT(high);
		CASE_TO_TEXT(medium);
		CASE_TO_TEXT(low);
	default:
		return "";
	}
}