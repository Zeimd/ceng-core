#include "FunctionDeclarator.h"

#include "FunctionHeader.h"
#include "FunctionHeaderWithParams.h"

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

Ceng::StringUtf8 FunctionDeclarator::ToString() const
{
	if (params)
	{
		return withParams->ToString();
	}

	return header->ToString();
}

