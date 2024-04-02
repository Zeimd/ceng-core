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
	qualifier = FromTokenType(type);
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

Ceng::StringUtf8 StorageQualifier::ToString(unsigned int indentLevel) const
{
	switch (qualifier)
	{
	case StorageQualifierType::sq_const:
		return "const";
	case StorageQualifierType::sq_attribute:
		return "attribute";
	case StorageQualifierType::sq_centroid_in:
		return "centroid in";
	case StorageQualifierType::sq_centroid_out:
		return "centroid out";
	case StorageQualifierType::sq_centroid_varying:
		return "centroid varying";
	case StorageQualifierType::sq_in:
		return "in";
	case StorageQualifierType::sq_out:
		return "out";
	case StorageQualifierType::sq_uniform:
		return "uniform";
	case StorageQualifierType::sq_varying:
		return "varying";
	case StorageQualifierType::unused:
		return "";
	default:
		return"StorageQualifier::unhandled";
	}
}