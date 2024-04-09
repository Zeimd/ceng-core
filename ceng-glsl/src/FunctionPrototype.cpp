#include "FunctionPrototype.h"

#include "FunctionDeclarator.h"

#include "NonTerminalVisitor.h"
#include "FunctionHeaderWithParams.h"
#include "ParameterDeclaration.h"
#include "ParameterDeclarator.h"

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

Ceng::UINT32 FunctionPrototype::GetParamCount() const
{
	if (!decl->params)
	{
		return 0;
	}

	return decl->withParams->params.size();
}

const Ceng::StringUtf8* FunctionPrototype::GetParameterName(Ceng::UINT32 index) const
{
	if (index > GetParamCount())
	{
		return nullptr;
	}

	return &decl->withParams->params[index]->decl->name;
}

std::shared_ptr<ParameterDeclaration> FunctionPrototype::GetParameter(Ceng::UINT32 index) 
{
	if (index > GetParamCount())
	{
		return nullptr;
	}

	return decl->withParams->params[index];
}