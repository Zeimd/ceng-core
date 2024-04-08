#include "JumpStatement.h"
#include "Expression.h"

#include "AST_Visitor.h"

using namespace Ceng;

JumpStatement::~JumpStatement()
{

}

void JumpStatement::Release()
{
	delete this;
}

JumpStatement::JumpStatement(JumpType::value jumpType)
	: INonTerminal(NonTerminalType::jump_statement), jumpType(jumpType), returnExpression(nullptr)
{

}

JumpStatement::JumpStatement(std::shared_ptr<Expression>& returnExpression)
	: INonTerminal(NonTerminalType::jump_statement), jumpType(JumpType::returnStatement), returnExpression(returnExpression)
{

}

Ceng::StringUtf8 JumpStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += GetIndent(indentLevel);

	switch (jumpType)
	{
	case JumpType::breakStatement:
		out += "break;";
		break;
	case JumpType::continueStatement:
		out += "continue;";
		break;
	case JumpType::discard:
		out += "discard;";
		break;
	case JumpType::returnStatement:

		if (returnExpression == nullptr)
		{
			out += "return;";
		}
		else
		{
			out += "return ";
			out += returnExpression->ToString(indentLevel);
			out += ";";
		}
		

		break;
		
	default:
		out += "<UNHANDLED JUMP TYPE>";
	}

	return out;
}

void JumpStatement::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_JumpStatement(*this);
}