#include "CaseLabel.h"
#include "Expression.h"

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

	if (defaultCase)
	{		
		out += "default:\n";
		return out;
	}

	out += "case ";
	out += expression->ToString(indentLevel);
	out += ":\n";

	return out;
}
