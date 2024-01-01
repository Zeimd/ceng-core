#include "GLSL_Parser.h"

using namespace Ceng;

GLSL_Parser::GLSL_Parser()
{
}

void GLSL_Parser::Release()
{
	delete this;
}

const Ceng::StringUtf8 GLSL_Parser::GetLog() const
{
	return log;
}

CRESULT GLSL_Parser::Parse(const std::vector<Token>& in_tokens, GLSL::AbstractSyntaxTree& output)
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
	Ceng::StringUtf8 text;
	text = "PeekToken = ";
	text += tokenIter->ToString();
	LogDebug(text);

	return *tokenIter;
}

const Token GLSL_Parser::NextToken()
{
	Ceng::StringUtf8 text;
	text = "NextToken = ";
	text += tokenIter->ToString();
	LogDebug(text);

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

ParserReturnValue GLSL_Parser::S_Translation_Unit()
{
	LogDebug("S_Translation_Unit");

	do
	{
		ParserReturnValue retVal;

		Token next = NextToken();

		if (next.type == TokenType::meta_end_of_file)
		{
			LogDebug("end of file reached");
			return ParserReturnValue();
		}

		if (next.category == TokenCategory::data_type)
		{
			Ceng::StringUtf8 text;
			text = "no parsing rule for: ";
			text += next.ToString();
			LogError(text);
		}
		else
		{
			switch (next.type)
			{
			case TokenType::keyword_const:
			case TokenType::keyword_attribute:
			case TokenType::keyword_varying:
			case TokenType::keyword_uniform:
			case TokenType::keyword_in:
			case TokenType::keyword_out:
				retVal = ParserReturnValue(new StorageQualifier(next.type));
				break;
			default:
				Ceng::StringUtf8 text;
				text = "no parsing rule for: ";
				text += next.ToString();
				LogError(text);
				break;
			}
		}

		shiftCount--;

		if (shiftCount > 0)
		{
			return retVal;
		}

		if (retVal.nonTerminal != nullptr)
		{
			switch (retVal.nonTerminal->type)
			{
			case NonTerminalType::storage_qualifier:
				retVal = S_StorageQ((StorageQualifier*)retVal.nonTerminal);

			default:
				Ceng::StringUtf8 text;
				text = "no parsing rule for: ";
				text += next.ToString();
				LogError(text);
				break;
			}
		}

	} while (1);
}

ParserReturnValue GLSL_Parser::S_StorageQ(StorageQualifier* sq)
{
	LogDebug("S_TU_StorageQ");

	shiftCount++;

	ParserReturnValue retVal;

	Token next = NextToken();



	if (retVal.nonTerminal != nullptr)
	{
		switch (retVal.nonTerminal->type)
		{
		default:
			break;
		}
	}
	
}

/*
void GLSL_Parser::S_TU_TypeQ(const TypeQualifier& typeQualifier)
{
	LogDebug("S_TU_TypeQ");

	if (PeekToken().category == TokenCategory::data_type)
	{
		switch (PeekToken().type)
		{
		case TokenType::type_name:
			S_TU_TypeQ_TypeSpecNoArr(typeQualifier, TypeSpecifierNoArray(PeekToken().name));
			break;
		default:
			S_TU_TypeQ_TypeSpecNoArr(typeQualifier, TypeSpecifierNoArray(PeekToken().type));
			break;
		}
	}
	else
	{
		switch (PeekToken().type)
		{
		case TokenType::keyword_high_precision:
		case TokenType::keyword_medium_precision:
		case TokenType::keyword_low_precision:
			break;
		default:
			Ceng::StringUtf8 text;
			text += "no parsing rule for: ";
			text += PeekToken().ToString();
			LogError(text);
			break;
		}
	}
}

void GLSL_Parser::S_TU_TypeQ_TypeSpecNoArr(const TypeQualifier& typeQualifier, const TypeSpecifierNoArray& typeSpec)
{
	LogDebug("S_TU_TypeQ_TypeSpecNoArr");

	Token next = NextToken();

	if (next.type == TokenType::left_bracket)
	{
		Ceng::StringUtf8 text;
		text += "no parsing rule for: ";
		text += next.ToString();
		LogError(text);
	}
	else if (next.type != TokenType::left_bracket)
	{
		S_TU_TypeQ_TypeSpecNoPrec(typeQualifier, TypeSpecifierNoPrec(typeSpec));
	}
	else
	{
		Ceng::StringUtf8 text;
		text += next.ToString();
		text += " not allowed after typename";

		LogError(text);
	}
}

void GLSL_Parser::S_TU_TypeQ_TypeSpecNoPrec(const TypeQualifier& typeQualifier, const TypeSpecifierNoPrec& typeSpec)
{
	LogDebug("S_TU_TypeQ_TypeSpecNoPrec");

	S_TU_TypeQ_TypeSpecifier(typeQualifier, TypeSpecifier(typeSpec));
}

void GLSL_Parser::S_TU_TypeQ_TypeSpecifier(const TypeQualifier& typeQualifier, const TypeSpecifier& typeSpec)
{
	LogDebug("S_TU_TypeQ_TypeSpecifier");

	S_TU_FullSpecType(FullySpecifiedType(typeQualifier, typeSpec));
}

void GLSL_Parser::S_TU_FullSpecType(const FullySpecifiedType& typeSpec)
{
	LogDebug("S_TU_FullSpecType");

	Token next = NextToken();

	if (next.type == TokenType::identifier)
	{
		S_TU_FullSpecType_identifier(typeSpec, next.name);
	}
	else
	{
		Ceng::StringUtf8 text;
		text += "no parsing rule for: ";
		text += next.ToString();
		LogError(text);
	}
}

void GLSL_Parser::S_TU_FullSpecType_identifier(const FullySpecifiedType& typeSpec, const Ceng::StringUtf8& name)
{
	LogDebug("S_TU_FullSpecType_identifier");

	if (PeekToken().type != TokenType::left_bracket)
	{
		S_TU_SingleDeclaration(SingleDeclaration(typeSpec,name));
	}
	else
	{
		Ceng::StringUtf8 text;
		text += "no parsing rule for: ";
		text += PeekToken().ToString();
		LogError(text);
	}
}

void GLSL_Parser::S_TU_SingleDeclaration(const SingleDeclaration& singleDecl)
{
	LogDebug("S_TU_SingleDeclaration");

	if (PeekToken().type != TokenType::comma)
	{
		S_TU_InitDeclList(InitDeclaratorList(singleDecl));
	}
	else
	{
		Ceng::StringUtf8 text;
		text += "no parsing rule for: ";
		text += PeekToken().ToString();
		LogError(text);
	}
}

void GLSL_Parser::S_TU_InitDeclList(const InitDeclaratorList& initDeclList)
{
	LogDebug("S_TU_InitDeclList");

	Token next = NextToken();

	if (next.type == TokenType::semicolon)
	{
		auto output = Declaration(initDeclList);
		return;
	}
}
*/