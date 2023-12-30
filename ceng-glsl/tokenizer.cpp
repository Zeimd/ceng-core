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

	TokenType::value prevTokenType;
	TokenType::value tokenType = TokenType::meta_uninitialized;

	for (auto iter = source.ConstBeginIterator(); iter != source.ConstEndIterator(); iter++)
	{
		prevTokenType = tokenType;

		++position;

		char item;
		
		(*iter).ToChar(&item);

		switch (item)
		{
		case ' ':
		case '\t':
			if (tokens.size() > 0)
			{
				tokens.back().rightSpace = true;
			}

			leftSpace = true;
			continue;
		case '\n':
			if (tokens.size() > 0)
			{
				tokens.back().endLine = true;
			}

			position = 0;
			++line;
			leftSpace = false;
			startLine = false;
			endLine = false;
			rightSpace = false;
			continue;
		case '!':
			tokenType = TokenType::bang;
			break;
		case '&':
			tokenType = TokenType::ampersand;
			break;
		case '^':
			tokenType = TokenType::caret;
			break;
		case '*':
			tokenType = TokenType::star;
			break;
		case '/':
			tokenType = TokenType::slash;
			break;
		case '-':
			tokenType = TokenType::dash;
			break;
		case '+':
			tokenType = TokenType::plus;
			break;
		case '%':
			tokenType = TokenType::percent;
			break;
		case '?':
			tokenType = TokenType::question;
			break;
		case ':':
			tokenType = TokenType::colon;
			break;
		case ';':
			tokenType = TokenType::semicolon;
			break;
		case ',':
			tokenType = TokenType::comma;
			break;
		case '.':
			tokenType = TokenType::dot;
			break;
		case '~':
			tokenType = TokenType::tilde;
			break;
		case '|':
			tokenType = TokenType::vertical_bar;
			break;
		case '(':
			tokenType = TokenType::left_paren;
			break;
		case ')':
			tokenType = TokenType::right_paren;
			break;
		case '[':
			tokenType = TokenType::left_bracket;
			break;
		case ']':
			tokenType = TokenType::right_bracket;
			break;
		case '{':
			tokenType = TokenType::left_brace;
			break;
		case '}':
			tokenType = TokenType::right_brace;
			break;
		case '<':
			tokenType = TokenType::left_angle;
			break;
		case '>':
			tokenType = TokenType::right_angle;
			break;
		case '=':
			tokenType = TokenType::equal;
			break;
		}


	

	}


	out_tokens = std::move(tokens);

	return CE_OK;
}