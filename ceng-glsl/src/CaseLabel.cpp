#include "CaseLabel.h"
#include "Expression.h"

#include "AST_Visitor.h"

using namespace Ceng;

CaseLabel::~CaseLabel()
{

}

void CaseLabel::Release()
{
	delete this;
}

CaseLabel::CaseLabel()
	: INonTerminal(NonTerminalType::case_label), defaultCase(true), expression(nullptr)
{

}

CaseLabel::CaseLabel(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::case_label), defaultCase(false), expression(expression)
{

}


Ceng::StringUtf8 CaseLabel::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	unsigned int indent = indentLevel;
	if (indent > 0)
	{
		--indent;
	}

	out += GetIndent(indent);

	if (defaultCase)
	{		
		out += "default:";
		return out;
	}

	out += "case ";
	out += expression->ToString(indent);
	out += ':';

	return out;
}

void CaseLabel::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_CaseLabel(*this);
}