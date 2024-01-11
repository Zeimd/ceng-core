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

	S_TranslationUnit();

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

ParserReturnValue GLSL_Parser::StateFuncSkeleton(const char* callerName,ShiftHandler shiftHandler, GotoHandler gotoHandler)
{
	do
	{
		bool earlyContinue = false;

		ParserReturnValue retVal;

		// TODO: reduction handler

		Token next = NextToken();

		if (next.type == TokenType::meta_end_of_file)
		{
			LogDebug("end of file reached");
			return ParserReturnValue();
		}

		auto shiftReturn = (this->*shiftHandler)(next);

		if (shiftReturn.invalid)
		{
			LogDebug("No shift rule for returned non-terminal");
			continue;
		}

		retVal = shiftReturn.retVal;

		// Loop goto action until there is an action that must be handled
		// further down the call stack

		bool exit;

		do
		{
			exit = false;

			retVal.backtrackCounter--;

			if (retVal.backtrackCounter > 0)
			{
				// Reduction is handled further back in the state stack

				Ceng::StringUtf8 text;
				text = "backtrack pass: ";
				text += callerName;
				text += " , remaining count = ";
				text += retVal.backtrackCounter;
				LogDebug(text);

				return retVal;
			}

			Ceng::StringUtf8 text;
			text = "goto action: ";
			text += callerName;
			LogDebug(text);

			if (retVal.nonTerminal == nullptr)
			{
				// Received invalid nonterminal

				LogDebug("Received empty non-terminal");

				return retVal;
			}

			auto gotoRet = (this->*gotoHandler)(retVal.nonTerminal);

			if (gotoRet.invalid)
			{
				LogDebug("No goto rule for returned non-terminal");
				return gotoRet.retVal;
			}

			retVal = gotoRet.retVal;

		} while (exit == false);

	} while (1);
}

GLSL_Parser::ShiftHandlerReturn GLSL_Parser::Shift_S_TranslationUnit(const Token& next)
{
	ParserReturnValue retVal;
	bool invalid = false;

	if (next.category == TokenCategory::data_type)
	{
		Ceng::StringUtf8 text;
		text = "no parsing rule for: ";
		text += next.ToString();
		LogError(text);
		invalid = true;
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

			invalid = true;
			break;
		}
	}

	return { retVal,invalid };
}

GLSL_Parser::ShiftHandlerReturn GLSL_Parser::Goto_S_TranslationUnit(INonTerminal* nonTerminal)
{
	ParserReturnValue retVal;
	bool invalid = false;

	switch (nonTerminal->type)
	{
	case NonTerminalType::storage_qualifier:
		retVal = S_StorageQualifier((StorageQualifier*)retVal.nonTerminal);
		break;
	case NonTerminalType::type_qualifier:
		retVal = S_TypeQualifier((TypeQualifier*)retVal.nonTerminal);
		break;

	default:
		invalid = true;
		break;
	}

	return { retVal,invalid };
}

ParserReturnValue GLSL_Parser::S_TranslationUnit()
{
	LogDebug(__func__);

	return StateFuncSkeleton(__func__,&GLSL_Parser::Shift_S_TranslationUnit, &GLSL_Parser::Goto_S_TranslationUnit);
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

GLSL_Parser::ShiftHandlerReturn GLSL_Parser::Shift_S_TypeQualifier(const Token& next)
{
	ParserReturnValue retVal;
	bool invalid = false;

	if (next.category == TokenCategory::data_type)
	{
		retVal = S_DatatypeToken(next.type);
	}
	else
	{
		/*
		Ceng::StringUtf8 text;
		text = "no parsing rule for: ";
		text += next.ToString();
		LogError(text);
		*/
		invalid = true;
	}
	return { retVal,invalid };
}

GLSL_Parser::ShiftHandlerReturn GLSL_Parser::Goto_S_TypeQualifier(INonTerminal* nonTerminal)
{
	ParserReturnValue retVal;
	bool invalid = false;

	switch (nonTerminal->type)
	{
	case NonTerminalType::type_specifier_nonarray:
		//retVal = S_TypeQualifier_TypeSpecifierNonArray();
		break;
	default:
		invalid = true;
	}

	return { retVal,invalid };
}


ParserReturnValue GLSL_Parser::S_TypeQualifier(TypeQualifier* sq)
{
	LogDebug(__func__);

	return StateFuncSkeleton(__func__,&GLSL_Parser::Shift_S_TypeQualifier, &GLSL_Parser::Goto_S_TypeQualifier);

	ParserReturnValue retVal;

	Token next = NextToken();

	

	return retVal;
}

ParserReturnValue GLSL_Parser::S_DatatypeToken(TokenType::value value)
{
	LogDebug(__func__);

	return ParserReturnValue(new TypeSpecifierNoArray(value), 1);
}