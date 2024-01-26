#include "TypeQualifier.h"

using namespace Ceng;

void TypeQualifier::Release()
{
	delete this;
}

TypeQualifier::TypeQualifier()
	: INonTerminal(NonTerminalType::type_qualifier), storage(StorageQualifier()),interpolation(),
	invariant(false)
{

}

TypeQualifier::TypeQualifier(const LayoutQualifier& layout)
	: INonTerminal(NonTerminalType::type_qualifier)
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation)
	: INonTerminal(NonTerminalType::type_qualifier)
{

}

TypeQualifier::TypeQualifier(const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), storage(sq)
{

}

TypeQualifier::TypeQualifier(bool invariant)
	: INonTerminal(NonTerminalType::type_qualifier), 
	storage(StorageQualifier()), interpolation(), invariant(invariant)
{

}

TypeQualifier::TypeQualifier(bool invariant, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier)
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier)
{

}

TypeQualifier::TypeQualifier(bool invariant, const InterpolationQualifier& interpolation, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier)
{

}

Ceng::StringUtf8 TypeQualifier::ToString() const
{
	return "";
}