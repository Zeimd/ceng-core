#include "Initializer.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

Initializer::Initializer(std::shared_ptr<AssignmentExpression>& assignEx)
	: INonTerminal(NonTerminalType::initializer), assignEx(assignEx)
{

}

void Initializer::Release()
{
	delete this;
}

Ceng::StringUtf8 Initializer::ToString(unsigned int indentLevel) const
{
	return assignEx->ToString(indentLevel);
}

void Initializer::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_Initializer(*this);
}