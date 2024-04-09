#include "LayoutQualifier.h"
#include "LayoutQualifierIdList.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

LayoutQualifier::~LayoutQualifier()
{

}

void LayoutQualifier::Release()
{
	delete this;
}

LayoutQualifier::LayoutQualifier(std::shared_ptr<LayoutQualifierIdList>& list)
	: INonTerminal(NonTerminalType::layout_qualifier), list(list)
{

}

Ceng::StringUtf8 LayoutQualifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "layout(";
	out += list->ToString(indentLevel);
	out += ") ";

	return out;
}

void LayoutQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_LayoutQualifier(*this);
}