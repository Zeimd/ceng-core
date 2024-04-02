#include "FunctionHeader.h"
#include "FullySpecifiedType.h"

using namespace Ceng;

FunctionHeader::~FunctionHeader()
{

}

void FunctionHeader::Release()
{
	delete this;
}

FunctionHeader::FunctionHeader(std::shared_ptr<FullySpecifiedType>& type, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::function_header), type(type), name(name)
{

}

Ceng::StringUtf8 FunctionHeader::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += type->ToString(indentLevel);
	out += ' ';
	out += name;
	out += '(';

	return out;
}