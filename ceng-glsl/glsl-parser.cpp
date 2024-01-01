#include "inc/ceng/glsl-parser.h"

using namespace Ceng;

CRESULT GLSL_Parser::Parse(const std::vector<Token>& in_tokens)
{
	log = "";

	tokens = in_tokens;

	tokenIter = tokens.begin();

	Log("Parsing start");

	S_Translation_Unit();

	Log("Parsing end");

	return CE_OK;
}

const Token& GLSL_Parser::PeekToken()
{
	return *tokenIter;
}

const Token GLSL_Parser::NextToken()
{
	return (*tokenIter++);
}

void GLSL_Parser::DiscardNext()
{
	++tokenIter;
}

const char* GLSL_Parser::GetPrefixText(LogPrefix prefix)
{
	switch (prefix)
	{
	case log_nominal:
		return "";
	case log_error:
		return "ERROR: ";
	}

	return "";
}


void GLSL_Parser::Log(const char* text, LogPrefix prefix)
{
#ifndef _DEBUG
	if (prefix == log_debug)
	{
		return;
	}
#endif

	log += GetPrefixText(prefix);
	log += text;
	log += '\n';
}

void GLSL_Parser::Log(const Ceng::StringUtf8& text, LogPrefix prefix)
{
#ifndef _DEBUG
	if (prefix == log_debug)
	{
		return;
	}
#endif
	log += GetPrefixText(prefix);
	log += text;
	log += '\n';
}


void GLSL_Parser::LogError(const char* error)
{
	Log(error, log_error);
}

void GLSL_Parser::LogError(const Ceng::StringUtf8& error)
{
	Log(error, log_error);
}

void GLSL_Parser::LogDebug(const char* text)
{
	Log(text, log_debug);
}
void GLSL_Parser::LogDebug(const Ceng::StringUtf8& text)
{
	Log(text, log_debug);
}

void GLSL_Parser::S_Translation_Unit()
{
	Log("testing");
	LogDebug("S_Translation_Unit");

	Token next = NextToken();

	if (next.type == TokenType::meta_end_of_file)
	{
		LogDebug("end of file reached");
		return;
	}

	if (next.category == TokenCategory::data_type)
	{
		switch (next.type)
		{
		case TokenType::type_name:
			S_TU_TypeSpecNoArr(TypeSpecifierNoArray(next.name));
			break;
		default:
			S_TU_TypeSpecNoArr(TypeSpecifierNoArray(next.type));
			break;
		}
	}
	else
	{
		switch (next.type)
		{
		case TokenType::keyword_const:
			S_TU_StorageQ(StorageQualifier::sq_const);
			break;
		case TokenType::keyword_attribute:
			S_TU_StorageQ(StorageQualifier::sq_attribute);
			break;
		case TokenType::keyword_varying:
			S_TU_StorageQ(StorageQualifier::sq_varying);
			break;
		case TokenType::keyword_uniform:
			S_TU_StorageQ(StorageQualifier::sq_uniform);
			break;
		case TokenType::keyword_in:
			S_TU_StorageQ(StorageQualifier::sq_in);
			break;
		case TokenType::keyword_out:
			S_TU_StorageQ(StorageQualifier::sq_out);
			break;
		case TokenType::keyword_centroid:
			switch (PeekToken().type)
			{
			case TokenType::keyword_in:
				S_TU_StorageQ(StorageQualifier::sq_centroid_in);
				break;
			case TokenType::keyword_out:
				S_TU_StorageQ(StorageQualifier::sq_centroid_out);
				break;
			case TokenType::keyword_varying:
				S_TU_StorageQ(StorageQualifier::sq_centroid_varying);
				break;
			default:
				Ceng::StringUtf8 text;
				text = next.ToString();
				text += " not allowed after centroid";
				LogError(text);
				break;
			}
			break;
		default:
			Ceng::StringUtf8 text;
			text = "no parsing rule for: ";
			text += next.ToString();			
			LogError(text);
			break;
		}
	}
}

void GLSL_Parser::S_TU_StorageQ(StorageQualifier::value sq)
{
	LogDebug("S_TU_StorageQ");

	if (PeekToken().category != TokenCategory::qualifier)
	{
		S_TU_TypeQ(TypeQualifier(sq));
	}

	//Token next = NextToken();

	/*
	if (next.category == TokenCategory::data_type)
	{
		switch (next.type)
		{
		case TokenType::type_name:
			S_TU_StorageQ_TypeSpecNoArr(sq, TypeSpecifierNoArray(next.name));
			break;
		default:
			S_TU_StorageQ_TypeSpecNoArr(sq, TypeSpecifierNoArray(next.type));
			break;
		}
	}
	else
	{
		Ceng::StringUtf8 text;
		text += "no parsing rule for: ";
		text += next.ToString();
		LogError(text);
	}
	*/
}

void GLSL_Parser::S_TU_TypeQ(const TypeQualifier& typeQualifier)
{
	LogDebug("S_TU_TypeQ");
}

void GLSL_Parser::S_TU_StorageQ_TypeSpecNoArr(StorageQualifier::value sq, const TypeSpecifierNoArray& typeSpec)
{
	LogDebug("S_TU_StorageQ_TypeSpecNoArr");
}

void GLSL_Parser::S_TU_TypeSpecNoArr(const TypeSpecifierNoArray& typeSpec)
{
	LogDebug("S_TU_TypeSpecNoArr");

	Token next = NextToken();

	if (next.type == TokenType::left_bracket)
	{
		S_TU_TypeSpecNoArr_LB(typeSpec);
	}
	else if (next.type != TokenType::left_bracket)
	{
		S_TU_TypeSpecNoPrec(typeSpec);
	}
	else
	{
		Ceng::StringUtf8 text;
		text += next.ToString();
		text += " not allowed after typename";

		LogError(text);
	}
}

void GLSL_Parser::S_TU_TypeSpecNoArr_LB(const TypeSpecifierNoArray& typeSpec)
{

}

void GLSL_Parser::S_TU_TypeSpecNoPrec(const TypeSpecifierNoArray& typeSpec)
{

}


