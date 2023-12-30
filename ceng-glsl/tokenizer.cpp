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

	bool prevIsOperator = false;

	 
	TokenType::value prevToken = TokenType::meta_uninitialized;;
	TokenType::value currentToken = TokenType::meta_uninitialized;;

	for (auto iter = source.ConstBeginIterator(); iter != source.ConstEndIterator(); iter++)
	{
		prevToken = currentToken;

		currentToken = TokenType::meta_uninitialized;

		++position;

		char currentChar;
		
		(*iter).ToChar(&currentChar);

		switch (currentChar)
		{
		case ' ':
		case '\t':
			if (tokens.size() > 0)
			{
				tokens.back().rightSpace = true;
			}

			if (prevIsOperator && prevToken != TokenType::meta_uninitialized)
			{
				tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, prevToken);
				prevIsOperator = false;
			}

			currentToken = TokenType::meta_uninitialized;
			leftSpace = true;
			continue;
		case '\n':
			if (tokens.size() > 0)
			{
				tokens.back().endLine = true;
			}

			if (prevIsOperator && prevToken != TokenType::meta_uninitialized)
			{
				tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, prevToken);
				prevIsOperator = false;
			}

			currentToken = TokenType::meta_uninitialized;

			position = 0;
			++line;
			leftSpace = false;
			startLine = false;
			endLine = false;
			rightSpace = false;
			continue;
		case '!':
			prevIsOperator = true;
			currentToken = TokenType::bang;
			continue;
		case '&':
			if (prevToken == TokenType::ampersand)
			{
				prevIsOperator = false;
				currentToken = TokenType::and_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::ampersand;
			continue;
		case '|':
			if (prevToken == TokenType::vertical_bar)
			{
				prevIsOperator = false;
				currentToken = TokenType::or_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::vertical_bar;
			continue;
		case '^':
			if (prevToken == TokenType::caret)
			{
				prevIsOperator = false;
				currentToken = TokenType::xor_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::caret;
			continue;
		case '*':
			if (prevToken == TokenType::slash)
			{
				prevIsOperator = false;
				currentToken = TokenType::preprocess_comment_start;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::star;
			continue;
		case '/':
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
			prevIsOperator = true;
			currentToken = TokenType::slash;
			continue;
		case '-':
			if (prevToken == TokenType::dash)
			{
				prevIsOperator = false;
				currentToken = TokenType::dec_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::dash;
			continue;
		case '+':
			if (prevToken == TokenType::plus)
			{
				prevIsOperator = false;
				currentToken = TokenType::inc_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::plus;
			continue;
		case '%':
			prevIsOperator = true;
			currentToken = TokenType::percent;
			continue;
		case '?':
			currentToken = TokenType::question;
			prevIsOperator = true;
			continue;
		case ':':
			if (prevToken == TokenType::question)
			{
				prevIsOperator = false;
				currentToken = TokenType::field_selection;
				break;
			}
			currentToken = TokenType::colon;
			break;
		case '<':
			if (prevToken == TokenType::left_angle)
			{
				prevIsOperator = false;
				currentToken = TokenType::left_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::left_angle;
			continue;
		case '>':
			if (prevToken == TokenType::right_angle)
			{
				prevIsOperator = false;
				currentToken = TokenType::right_op;
				break;
			}
			prevIsOperator = true;
			currentToken = TokenType::right_angle;
			continue;
		case '=':
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
				prevIsOperator = true;
				currentToken = TokenType::equal;
				continue;
			}
			break;
		case ';':
			currentToken = TokenType::semicolon;
			break;
		case ',':
			currentToken = TokenType::comma;
			break;
		case '.':
			currentToken = TokenType::dot;
			break;
		case '~':
			currentToken = TokenType::tilde;
			break;
		case '(':
			currentToken = TokenType::left_paren;
			break;
		case ')':
			currentToken = TokenType::right_paren;
			break;
		case '[':
			currentToken = TokenType::left_bracket;
			break;
		case ']':
			currentToken = TokenType::right_bracket;
			break;
		case '{':
			currentToken = TokenType::left_brace;
			break;
		case '}':
			currentToken = TokenType::right_brace;
			break;
		};

		if (prevIsOperator && prevToken != TokenType::meta_uninitialized)
		{
			tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, prevToken);
		}

		prevIsOperator = false;

		if (currentToken != TokenType::meta_uninitialized)
		{
			tokens.emplace_back(sourceFile, line, position, leftSpace, rightSpace, startLine, endLine, currentToken);
			continue;
		}

	}

	out_tokens = std::move(tokens);

	return CE_OK;
}