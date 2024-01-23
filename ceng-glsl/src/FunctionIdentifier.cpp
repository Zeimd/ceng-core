#include "FunctionIdentifier.h"

using namespace Ceng;

void FunctionIdentifier::Release()
{
	delete this;
}

FunctionIdentifier::FunctionIdentifier(std::shared_ptr<TypeSpecifier>& typeSpec)
	: INonTerminal(NonTerminalType::function_identifier), typeSpec(typeSpec), funcType(FunctionType::constructor)
{

}

FunctionIdentifier::FunctionIdentifier(Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::function_identifier), typeSpec(typeSpec), funcType(FunctionType::normal)
{

}