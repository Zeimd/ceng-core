#include "LayoutQualifierId.h"

#include "AST_Visitor.h"

using namespace Ceng;

LayoutQualifierId::~LayoutQualifierId()
{

}

void LayoutQualifierId::Release()
{
	delete this;
}

LayoutQualifierId::LayoutQualifierId(const Ceng::StringUtf8& identifier)
	: INonTerminal(NonTerminalType::layout_qualifier_id), identifier(identifier), hasValue(false)
{

}

LayoutQualifierId::LayoutQualifierId(const Ceng::StringUtf8& identifier, Ceng::INT32 value)
	: INonTerminal(NonTerminalType::layout_qualifier_id), identifier(identifier), hasValue(true), value(value)
{

}

Ceng::StringUtf8 LayoutQualifierId::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += identifier;

	if (hasValue)
	{
		out += '=';
		out += value;
	}

	return out;
}

void LayoutQualifierId::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_LayoutQualifierId(*this);
}
