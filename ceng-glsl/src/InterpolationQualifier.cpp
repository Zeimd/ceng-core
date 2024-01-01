#include "InterpolationQualifier.h"

using namespace Ceng;

void InterpolationQualifier::Release()
{
	delete this;
}

InterpolationQualifier::InterpolationQualifier()
	: INonTerminal(NonTerminalType::interpolation_qualifier),interpolation(InterpolationQualifierType::unused)
{

}

InterpolationQualifier::InterpolationQualifier(InterpolationQualifierType::value interpolation)
	: INonTerminal(NonTerminalType::interpolation_qualifier), interpolation(interpolation)
{

}