#include "StorageQualifier.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void StorageQualifier::Release()
{
	delete this;
}

StorageQualifier::StorageQualifier() 
	: INonTerminal(NonTerminalType::storage_qualifier), qualifier(GLSL::StorageQualifierType::unused)
{

}

StorageQualifier::StorageQualifier(TokenType::value type)
	: INonTerminal(NonTerminalType::storage_qualifier)
{	
	qualifier = FromTokenType(type);
}

StorageQualifier::StorageQualifier(GLSL::StorageQualifierType::value qualifier)
	: INonTerminal(NonTerminalType::storage_qualifier), qualifier(qualifier)
{

}

GLSL::StorageQualifierType::value StorageQualifier::FromTokenType(TokenType::value type)
{
	switch (type)
	{
	case TokenType::keyword_const:
		return GLSL::StorageQualifierType::sq_const;
	case TokenType::keyword_attribute:
		return GLSL::StorageQualifierType::sq_attribute;
	case TokenType::keyword_varying:
		return GLSL::StorageQualifierType::sq_varying;
	case TokenType::keyword_in:
		return GLSL::StorageQualifierType::sq_in;
	case TokenType::keyword_out:
		return GLSL::StorageQualifierType::sq_out;
	case TokenType::keyword_uniform:
		return GLSL::StorageQualifierType::sq_uniform;
	default:
		return GLSL::StorageQualifierType::unused;
	}
}

Ceng::StringUtf8 StorageQualifier::ToString(unsigned int indentLevel) const
{
	return GLSL::StorageQualifierType::ToString(qualifier);
}

void StorageQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_StorageQualifier(*this);
}