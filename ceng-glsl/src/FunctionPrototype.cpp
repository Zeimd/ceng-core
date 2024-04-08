#include "FunctionPrototype.h"

#include "FunctionDeclarator.h"

#include "AST_Visitor.h"

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

void FunctionPrototype::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_FunctionPrototype(*this);
}