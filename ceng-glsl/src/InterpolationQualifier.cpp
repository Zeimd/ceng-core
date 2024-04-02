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