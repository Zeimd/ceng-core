#include <memory>

#include <ceng/tokenizer.h>

#include "keyword_db.h"

using namespace Ceng;

Tokenizer::Tokenizer()
{

}

Tokenizer::~Tokenizer()
{

}



Ceng::CRESULT Tokenizer::Tokenize(const Ceng::StringUtf8& fileName, const Ceng::StringUtf8& source, std::vector<Token>& out_tokens)
{
	CRESULT cresult;

	std::vector<Token> tokens;

	auto sourceFile = std::make_shared<const Ceng::StringUtf8>(fileName);

	Ceng::UINT32 line = 1;
	Ceng::UINT32 position = 0;

	if (source.Length() == 0)
	{
		out_tokens = std::move(tokens);
		return CE_ERR_INVALID_PARAM;
	}

	bool leftSpace = false;
	bool rightSpace = false;

	bool startLine = false;
	bool endLine = false;

	bool prevIsOperator = false;
	bool currentIsOperator = false;

	// Does operator detected appear in a combined operator, such as "<" in "<<".
	bool trailingOperator = false;

	bool flushSection = false;

	SectionType::value sectionType = SectionType::unused;
	Ceng::StringUtf8::CONST_ITERATOR_TYPE sectionStart,sectionEnd;
	
	 
	TokenType::value prevToken = TokenType::meta_uninitialized;;
	TokenType::value currentToken = TokenType::meta_uninitialized;;

	for (auto iter = source.ConstBeginIterator(); iter != source.ConstEndIterator(); iter++)
	{
		prevToken = currentToken;
		currentToken = TokenType::meta_uninitialized;

		prevIsOperator = currentIsOperator;
		currentIsOperator = false;
		trailingOperator = false;

		++position;

		char currentChar;
		
		(*iter).ToChar(&currentChar);

		printf("DEBUG: currentChar = %c\n", currentChar);

		switch (currentChar)
		{
		case ' ':
		case '\t':
			if (tokens.size() > 0)
			{
				tokens.back().rightSpace = true;
			}

			flushSection = true;

			currentToken = TokenType::meta_whitespace;
			leftSpace = true;
			break;
		case '\n':
			if (tokens.size() > 0)
			{
				tokens.back().endLine = true;
			}

			flushSection = true;

			currentToken = TokenType::meta_whitespace;

			position = 0;
			++line;
			leftSpace = false;
			startLine = false;
			endLine = false;
			rightSpace = false;
			break;
		case '!':
			flushSection = true;
			currentIsOperator = true;
			trailingOperator = true;
			currentToken = TokenType::bang;
			break;
		case '&':
			currentIsOperator = true;

			if (prevToken == TokenType::ampersand)
			{
				prevIsOperator = false;
				currentToken = TokenType::and_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;
			
			currentToken = TokenType::ampersand;
			break;
		case '|':
			currentIsOperator = true;

			if (prevToken == TokenType::vertical_bar)
			{
				prevIsOperator = false;
				currentToken = TokenType::or_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::vertical_bar;
			break;
		case '^':
			currentIsOperator = true;

			if (prevToken == TokenType::caret)
			{
				prevIsOperator = false;
				currentToken = TokenType::xor_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;
			prevIsOperator = true;
			currentToken = TokenType::caret;
			break;
		case '*':
			currentIsOperator = true;

			if (prevToken == TokenType::slash)
			{
				prevIsOperator = false;
				currentToken = TokenType::preprocess_comment_start;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::star;
			break;
		case '/':
			currentIsOperator = true;

			if (prevToken == TokenType::slash)
			{
				prevIsOperator = false;
				currentToken = TokenType::preprocess_comment;
				break;
			}
			else if 
			(prevToken == TokenType::star)
			{
				prevIsOperator = false;
				currentToken = TokenType::preprocess_comment_end;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::slash;
			break;
		case '-':
			currentIsOperator = true;

			if (prevToken == TokenType::dash)
			{
				prevIsOperator = false;
				currentToken = TokenType::dec_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::dash;
			break;
		case '+':
			currentIsOperator = true;

			if (prevToken == TokenType::plus)
			{
				prevIsOperator = false;
				currentToken = TokenType::inc_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::plus;
			break;
		case '%':
			currentIsOperator = true;
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::percent;
			break;
		case '?':
			currentIsOperator = true;
			trailingOperator = true;
			flushSection = true;
			currentToken = TokenType::question;			
			break;
		case ':':
			currentIsOperator = true;

			if (prevToken == TokenType::question)
			{
				prevIsOperator = false;
				currentToken = TokenType::field_selection;
				break;
			}
			flushSection = true;
			currentToken = TokenType::colon;
			break;
		case '<':
			currentIsOperator = true;

			if (prevToken == TokenType::left_angle)
			{
				prevIsOperator = false;
				currentToken = TokenType::left_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::left_angle;
			break;
		case '>':
			currentIsOperator = true;

			if (prevToken == TokenType::right_angle)
			{
				prevIsOperator = false;
				currentToken = TokenType::right_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::right_angle;
			break;
		case '=':
			currentIsOperator = true;

			switch (prevToken)
			{
			case TokenType::plus:
				prevIsOperator = false;
				currentToken = TokenType::add_assign;
				break;
			case TokenType::dash:
				prevIsOperator = false;
				currentToken = TokenType::sub_assign;
				break;
			case TokenType::star:
				prevIsOperator = false;
				currentToken = TokenType::mul_assign;
				break;
			case TokenType::slash:
				prevIsOperator = false;
				currentToken = TokenType::div_assign;
				break;
			case TokenType::percent:
				prevIsOperator = false;
				currentToken = TokenType::mod_assign;
				break;
			case TokenType::ampersand:
				prevIsOperator = false;
				currentToken = TokenType::and_assign;
				break;
			case TokenType::vertical_bar:
				prevIsOperator = false;
				currentToken = TokenType::or_assign;
				break;
			case TokenType::caret:
				prevIsOperator = false;
				currentToken = TokenType::xor_assign;
				break;
			case TokenType::equal:
				prevIsOperator = false;
				currentToken = TokenType::eq_op;
				break;
			case TokenType::left_angle:
				prevIsOperator = false;
				currentToken = TokenType::le_op;
				break;
			case TokenType::right_angle:
				prevIsOperator = false;
				currentToken = TokenType::ge_op;
				break;
			case TokenType::left_op:
				prevIsOperator = false;
				currentToken = TokenType::left_assign;
				break;
			case TokenType::right_op:
				prevIsOperator = false;
				currentToken = TokenType::right_assign;
				break;
			case TokenType::bang:
				prevIsOperator = false;
				currentToken = TokenType::ne_op;
				break;
			default:
				trailingOperator = true;
				flushSection = true;				
				currentToken = TokenType::equal;
				break;
			}
			break;
		case ';':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::semicolon;
			break;
		case ',':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::comma;
			break;
		case '.':
			currentIsOperator = true;

			if (sectionType == SectionType::text)
			{
				flushSection = true;
			}
			currentToken = TokenType::dot;
			break;
		case '~':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::tilde;
			break;
		case '(':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::left_paren;
			break;
		case ')':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::right_paren;
			break;
		case '[':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::left_bracket;
			break;
		case ']':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::right_bracket;
			break;
		case '{':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::left_brace;
			break;
		case '}':
			currentIsOperator = true;
			flushSection = true;
			currentToken = TokenType::right_brace;
			break;
		};

		if (flushSection)
		{			
			if (sectionType != SectionType::unused)
			{
				//printf("Debug: Flush section, sectionType = %i\n", sectionType);
				
				sectionEnd = iter;
				
				//printf("Debug: sectionStart = %i, sectionEnd = %i\n", sectionStart.Index(), sectionEnd.Index());

				Token token;

				cresult = TokenizeString(sectionType, sectionStart, sectionEnd, token);

				if (cresult == CE_OK)
				{
					tokens.push_back(token);
				}
			}
			
			sectionType = SectionType::unused;
			flushSection = false;
		}

		if (trailingOperator)
		{
			trailingOperator = false;
			continue;
		}
		else
		{
			if (currentIsOperator)
			{
				tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, currentToken);
				currentToken = TokenType::meta_uninitialized;
				currentIsOperator = false;
				continue;
			}
			else if (prevIsOperator)
			{
				tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, prevToken);
			}
			
			if (currentToken == TokenType::meta_uninitialized)
			{
				if (sectionType == SectionType::unused)
				{
					sectionStart = iter;

					switch (currentChar)
					{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '.':
						sectionType = SectionType::number;
						break;
					default:
						sectionType = SectionType::text;
						break;
					}
				}
			}
		}
	}

	out_tokens = std::move(tokens);

	return CE_OK;
}

Ceng::CRESULT Tokenizer::TokenizeString(SectionType::value type,Ceng::StringUtf8::CONST_ITERATOR_TYPE start, 
	Ceng::StringUtf8::CONST_ITERATOR_TYPE& end, Token& out_token)
{
	Ceng::StringUtf8 text;

	while (start < end)
	{
		char temp;

		(*start).ToChar(&temp);
	
		text += temp; 
		++start;
	};

	printf("DEBUG: string to parse = \"%s\"\n", text.ToCString());

	if (type == SectionType::text)
	{
		auto iter = keywords.find(text.ToCString());

		if (iter != keywords.end())
		{
			out_token.type = iter->second;
			return CE_OK;
		}

		out_token.type = TokenType::identifier;
		out_token.name = text;
		
	}

	return CE_OK;
}