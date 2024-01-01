#include "StorageQualifier.h"

using namespace Ceng;

void StorageQualifier::Release()
{
	delete this;
}

StorageQualifier::StorageQualifier() 
	: INonTerminal(NonTerminalType::storage_qualifier), qualifier(StorageQualifierType::unused)
{

}

StorageQualifier::StorageQualifier(TokenType::value type)
	: INonTerminal(NonTerminalType::storage_qualifier)
{	

}

StorageQualifier::StorageQualifier(StorageQualifierType::value qualifier)
	: INonTerminal(NonTerminalType::storage_qualifier), qualifier(qualifier)
{

}

StorageQualifierType::value StorageQualifier::FromTokenType(TokenType::value type)
{
	switch (type)
	{
	case TokenType::keyword_const:
		return StorageQualifierType::sq_const;
	case TokenType::keyword_attribute:
		return StorageQualifierType::sq_attribute;
	case TokenType::keyword_varying:
		return StorageQualifierType::sq_varying;
	case TokenType::keyword_in:
		return StorageQualifierType::sq_in;
	case TokenType::keyword_out:
		return StorageQualifierType::sq_out;
	case TokenType::keyword_uniform:
		return StorageQualifierType::sq_uniform;
	default:
		return StorageQualifierType::unused;
	}
}