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

Ceng::StringUtf8 PrecisionQualifier::ToString() const
{
	return "";
}