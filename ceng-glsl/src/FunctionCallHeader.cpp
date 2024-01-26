#include "FunctionCallHeader.h"

using namespace Ceng;

void FunctionCallHeader::Release()
{
	delete this;
}

FunctionCallHeader::FunctionCallHeader(std::shared_ptr<FunctionIdentifier>& identifier)
	: INonTerminal(NonTerminalType::function_call_header), identifier(identifier)
{

}

Ceng::StringUtf8 FunctionCallHeader::ToString() const
{
	return "";
}