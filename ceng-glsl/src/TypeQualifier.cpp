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

TypeQualifier::TypeQualifier(std::shared_ptr<LayoutQualifier>& layout)
	: INonTerminal(NonTerminalType::type_qualifier), layout(layout)
{

}

TypeQualifier::TypeQualifier(std::shared_ptr<LayoutQualifier>& layout, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), layout(layout), storage(sq)
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
	Ceng::StringUtf8 out;

	if (layout != nullptr)
	{
		out += layout->ToString();
	}

	if (invariant)
	{
		out += "invariant ";
	}

	if (interpolation.interpolation != InterpolationQualifierType::unused)
	{
		out += interpolation.ToString();
		out += ' ';
	}

	if (storage.qualifier != StorageQualifierType::unused)
	{
		out += storage.ToString();
		out += ' ';
	}

	return out;
}