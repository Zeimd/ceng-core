#include "TypeQualifier.h"

#include "NonTerminalVisitor.h"

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
	: INonTerminal(NonTerminalType::type_qualifier), layout(layout), invariant(false),interpolation()
{

}

TypeQualifier::TypeQualifier(std::shared_ptr<LayoutQualifier>& layout, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), layout(layout), storage(sq), invariant(false),
	interpolation()
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation)
	: INonTerminal(NonTerminalType::type_qualifier), invariant(false), interpolation(interpolation)
{

}

TypeQualifier::TypeQualifier(const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), storage(sq), invariant(false),
	interpolation()
{

}

TypeQualifier::TypeQualifier(bool invariant)
	: INonTerminal(NonTerminalType::type_qualifier), 
	storage(StorageQualifier()), interpolation(), invariant(invariant)
{

}

TypeQualifier::TypeQualifier(bool invariant, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), invariant(invariant),interpolation(),storage(sq)
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), invariant(false),interpolation(interpolation),storage(sq)
{

}

TypeQualifier::TypeQualifier(bool invariant, const InterpolationQualifier& interpolation, const StorageQualifier& sq)
	: INonTerminal(NonTerminalType::type_qualifier), invariant(invariant), interpolation(interpolation), storage(sq)
{

}

Ceng::StringUtf8 TypeQualifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (layout != nullptr)
	{
		out += layout->ToString(indentLevel);
	}

	if (invariant)
	{
		out += "invariant ";
	}

	if (interpolation.interpolation != GLSL::InterpolationQualifierType::unused)
	{
		out += interpolation.ToString(indentLevel);
		out += ' ';
	}

	if (storage.qualifier != GLSL::StorageQualifierType::unused)
	{
		out += storage.ToString(indentLevel);
		out += ' ';
	}

	return out;
}

void TypeQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_TypeQualifier(*this);
}