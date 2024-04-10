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
	switch (qualifier)
	{
	case GLSL::StorageQualifierType::sq_const:
		return "const";
	case GLSL::StorageQualifierType::sq_attribute:
		return "attribute";
	case GLSL::StorageQualifierType::sq_centroid_in:
		return "centroid in";
	case GLSL::StorageQualifierType::sq_centroid_out:
		return "centroid out";
	case GLSL::StorageQualifierType::sq_centroid_varying:
		return "centroid varying";
	case GLSL::StorageQualifierType::sq_in:
		return "in";
	case GLSL::StorageQualifierType::sq_out:
		return "out";
	case GLSL::StorageQualifierType::sq_uniform:
		return "uniform";
	case GLSL::StorageQualifierType::sq_varying:
		return "varying";
	case GLSL::StorageQualifierType::unused:
		return "";
	default:
		return"StorageQualifier::unhandled";
	}
}

void StorageQualifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_StorageQualifier(*this);
}