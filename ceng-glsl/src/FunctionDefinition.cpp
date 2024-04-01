#include "FunctionDefinition.h"
#include "FunctionPrototype.h"
#include "CompoundStatementNoNewScope.h"

using namespace Ceng;

FunctionDefinition::~FunctionDefinition()
{

}

void FunctionDefinition::Release()
{
	delete this;
}

FunctionDefinition::FunctionDefinition(std::shared_ptr<FunctionPrototype>& prototype,
	std::shared_ptr<CompoundStatementNoNewScope>& body)
	: INonTerminal(NonTerminalType::function_definition), prototype(prototype), body(body)
{

}

Ceng::StringUtf8 FunctionDefinition::ToString() const
{
	Ceng::StringUtf8 out;

	out = prototype->ToString();
	out += body->ToString();
	out += '\n';

	return out;
}