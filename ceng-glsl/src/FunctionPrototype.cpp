#include "FunctionPrototype.h"

#include "FunctionDeclarator.h"

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

Ceng::StringUtf8 FunctionPrototype::ToString() const
{
	Ceng::StringUtf8 out;

	out = decl->ToString();
	out += ')';

	return out;
}