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
	LogDebug(__func__);

	do
	{
		bool earlyContinue = false;

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
				retVal = S_StorageQualifierToken(next.type);
				break;
			default:
				Ceng::StringUtf8 text;
				text = "no parsing rule for: ";
				text += next.ToString();
				LogError(text);

				earlyContinue = true;
				break;
			}
		}

		if (earlyContinue)
		{
			continue;
		}

		// Loop goto action until something's returned for which there isn't a goto rule

		bool exit;

		do
		{
			LogDebug("goto loop start");

			exit = false;

			retVal.backtrackCounter--;

			if (retVal.backtrackCounter > 0)
			{
				LogDebug("Received non-zero backtrack counter");

				// TODO: Got declaration or function body
				exit = true;
				break;
			}

			if (retVal.nonTerminal == nullptr)
			{
				// Received invalid nonterminal

				LogDebug("Received empty non-terminal");

				exit = true;
				break;
			}

			switch (retVal.nonTerminal->type)
			{
			case NonTerminalType::storage_qualifier:
				retVal = S_StorageQualifier((StorageQualifier*)retVal.nonTerminal);
				break;
			case NonTerminalType::type_qualifier:
				retVal = S_TypeQualifier((TypeQualifier*)retVal.nonTerminal);
				break;

			default:
				LogDebug("No shift rule for returned non-terminal");
				exit = true;
				break;
			}

		} while (exit == false);

	} while (1);	
}

ParserReturnValue GLSL_Parser::S_StorageQualifierToken(TokenType::value value)
{
	LogDebug(__func__);

	return ParserReturnValue(new StorageQualifier(value), 1);
}

ParserReturnValue GLSL_Parser::S_StorageQualifier(StorageQualifier* sq)
{
	LogDebug(__func__);

	return ParserReturnValue(new TypeQualifier(sq), 1);
}

ParserReturnValue GLSL_Parser::S_TypeQualifier(TypeQualifier* sq)
{
	LogDebug(__func__);

	return ParserReturnValue(nullptr, 1);
}