#include "FunctionPrototype.h"

#include "FunctionDeclarator.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

FunctionPrototype::~FunctionPrototype()
{

}

void FunctionPrototype::Release()
{
	delete this;
}

FunctionPrototype::FunctionPrototype(std::shared_ptr<FunctionDeclarator>& decl)
	: INonTerminal(NonTerminalType::function_prototype), decl(decl)
{

}

Ceng::StringUtf8 FunctionPrototype::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = decl->ToString(indentLevel);
	out += ')';

	return out;
}

void FunctionPrototype::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionPrototype(*this);
}