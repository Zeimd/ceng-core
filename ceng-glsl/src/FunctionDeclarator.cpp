#include "FunctionDeclarator.h"

#include "FunctionHeader.h"
#include "FunctionHeaderWithParams.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

FunctionDeclarator::~FunctionDeclarator()
{

}

void FunctionDeclarator::Release()
{
	delete this;
}

FunctionDeclarator::FunctionDeclarator(std::shared_ptr<FunctionHeader>& header)
	: INonTerminal(NonTerminalType::function_declarator), params(false), header(header)
{

}

FunctionDeclarator::FunctionDeclarator(std::shared_ptr<FunctionHeaderWithParams>& withParams)
	: INonTerminal(NonTerminalType::function_declarator), params(true), withParams(withParams)
{

}

Ceng::StringUtf8 FunctionDeclarator::ToString(unsigned int indentLevel) const
{
	if (params)
	{
		return withParams->ToString(indentLevel);
	}

	return header->ToString(indentLevel);
}

void FunctionDeclarator::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionDeclarator(*this);
}