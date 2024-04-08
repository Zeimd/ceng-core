#include "Condition.h"

#include "Expression.h"
#include "FullySpecifiedType.h"
#include "Initializer.h"

#include "AST_Visitor.h"

using namespace Ceng;

Condition::~Condition()
{

}

void Condition::Release()
{
	delete this;
}

Condition::Condition(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::condition), conditionType(ConditionType::expression), expression(expression)
{

}

Condition::Condition(std::shared_ptr<FullySpecifiedType>& fullSpec, const Ceng::StringUtf8& identifier, std::shared_ptr<Initializer>& initializer)
	: INonTerminal(NonTerminalType::condition), conditionType(ConditionType::declare),
	fullSpec(fullSpec), identifier(identifier), initializer(initializer)
{

}

Ceng::StringUtf8 Condition::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (conditionType)
	{
	case ConditionType::expression:
		return expression->ToString(indentLevel);
	case ConditionType::declare:
		out = fullSpec->ToString(indentLevel);
		out += ' ';
		out += identifier;
		out += " = ";
		out += initializer->ToString(indentLevel);
		return out;
	}

	return "<UNHANDLED CONDITION TYPE>";
}

void Condition::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_Condition(*this);
}