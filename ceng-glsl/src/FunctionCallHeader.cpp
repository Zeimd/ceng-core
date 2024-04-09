#include "FunctionCallHeader.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void FunctionCallHeader::Release()
{
	delete this;
}

FunctionCallHeader::FunctionCallHeader(std::shared_ptr<FunctionIdentifier>& identifier)
	: INonTerminal(NonTerminalType::function_call_header), identifier(identifier)
{

}

Ceng::StringUtf8 FunctionCallHeader::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = identifier->ToString(indentLevel);
	out += '(';

	return out;
}

void FunctionCallHeader::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionCallHeader(*this);
}