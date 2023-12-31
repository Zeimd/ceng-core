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
	bool startLine = true;
	bool endLine = false;

	bool prevIsStart = false;
	bool prevIsOperator = false;
	bool currentIsOperator = false;

	// Does operator detected appear in a combined operator, such as "<" in "<<".
	bool trailingOperator = false;

	Ceng::UINT32 sectionStartPos = 0;
	bool flushSection = false;

	bool sectionLeftSpace = false;
	bool sectionStartLine = false;
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

		if (endLine)
		{
			startLine = true;
			position = 0;
			++line;
			endLine = false;
		}

		++position;

		char currentChar;
		
		(*iter).ToChar(&currentChar);

		//printf("DEBUG: currentChar = %c\n", currentChar);

		switch (currentChar)
		{
		case ' ':
		case '\t':
			flushSection = true;
			leftSpace = true;

			currentToken = TokenType::meta_whitespace;
			
			break;
		case '\n':
			flushSection = true;

			currentToken = TokenType::meta_end_of_line;
			break;
		case '#':
			currentIsOperator = true;

			if (prevToken == TokenType::preprocess_hash)
			{
				currentToken = TokenType::preprocess_concatenate_op;
				break;
			}

			if (startLine)
			{
				currentToken = TokenType::preprocess_hash;
			}
			else
			{
				currentToken = TokenType::preprocess_stringize;
			}

			flushSection = true;
			trailingOperator = true;
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
				currentToken = TokenType::xor_op;
				break;
			}
			trailingOperator = true;
			flushSection = true;
			currentToken = TokenType::caret;
			break;
		case '*':
			currentIsOperator = true;

			if (prevToken == TokenType::slash)
			{
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
				currentToken = TokenType::preprocess_comment;
				break;
			}
			else if (prevToken == TokenType::star)
			{
				currentToken = TokenType::preprocess_comment_end;
				break;
			}
			trailingOperator = true;
			flushSection = true;			
			currentToken = TokenType::slash;
			break;
		case '-':
			if (sectionType == SectionType::number)
			{
				break;
			}
			
			currentIsOperator = true;

			if (prevToken == TokenType::dash)
			{
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
				currentToken = TokenType::add_assign;
				break;
			case TokenType::dash:
				currentToken = TokenType::sub_assign;
				break;
			case TokenType::star:
				currentToken = TokenType::mul_assign;
				break;
			case TokenType::slash:
				currentToken = TokenType::div_assign;
				break;
			case TokenType::percent:
				currentToken = TokenType::mod_assign;
				break;
			case TokenType::ampersand:
				currentToken = TokenType::and_assign;
				break;
			case TokenType::vertical_bar:
				currentToken = TokenType::or_assign;
				break;
			case TokenType::caret:
				currentToken = TokenType::xor_assign;
				break;
			case TokenType::equal:
				currentToken = TokenType::eq_op;
				break;
			case TokenType::left_angle:
				currentToken = TokenType::le_op;
				break;
			case TokenType::right_angle:
				currentToken = TokenType::ge_op;
				break;
			case TokenType::left_op:
				currentToken = TokenType::left_assign;
				break;
			case TokenType::right_op:
				currentToken = TokenType::right_assign;
				break;
			case TokenType::bang:
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
			if (sectionType == SectionType::text)
			{
				flushSection = true;
			}

			if (sectionType == SectionType::number)
			{
				break;
			}

			currentIsOperator = true;
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

		bool rightSpace = currentToken == TokenType::meta_whitespace;
		endLine = currentToken == TokenType::meta_end_of_line;

		//printf("DEBUG: rightSpace=%i, endLine=%i\n", rightSpace, endLine);
		//printf("DEBUG: currentIsOperator=%i, prevIsOperator=%i\n", currentIsOperator, prevIsOperator);

		bool localStart = startLine;
		if (endLine)
		{
			localStart = false;
		}

		if (flushSection)
		{			
			if (sectionType != SectionType::unused)
			{
				sectionEnd = iter;
				
				Token token;

				cresult = TokenizeString(sectionType, sectionStart, sectionEnd, token);

				token.file = sourceFile;
				token.position = sectionStartPos;
				token.line = line;
				token.leftSpace = sectionLeftSpace;
				token.rightSpace = rightSpace;
				token.startLine = sectionStartLine;
				token.endLine = endLine;

				if (cresult == CE_OK)
				{
					tokens.push_back(token);
				}
			}
			
			sectionType = SectionType::unused;
			flushSection = false;
			leftSpace = false;
			startLine = false;
			sectionStartLine = false;
			sectionLeftSpace = false;
		}

		if (trailingOperator)
		{
			prevIsStart = startLine;
			trailingOperator = false;
			continue;
		}
		else
		{
			if (currentIsOperator)
			{
				Ceng::UINT32 startPos = position;
				if (prevIsOperator)
				{
					--startPos;
				}

				tokens.emplace_back(sourceFile, line, startPos, leftSpace, rightSpace, startLine, endLine, currentToken);
				currentToken = TokenType::meta_uninitialized;
				currentIsOperator = false;
				leftSpace = false;
				startLine = false;
				continue;
			}
			else if (prevIsOperator)
			{
				tokens.emplace_back(sourceFile, line, position-1, leftSpace, rightSpace, prevIsStart, endLine, prevToken);
				prevIsStart = false;
				leftSpace = false;
				startLine = false;
			}
			else if (currentToken == TokenType::meta_end_of_line)
			{
				leftSpace = false;

				if (tokens.size() > 0)
				{
					tokens.back().endLine = true;
				}
			}
			
			if (currentToken == TokenType::meta_uninitialized)
			{
				if (sectionType == SectionType::unused)
				{
					sectionLeftSpace = leftSpace;
					leftSpace = false;
					sectionStartLine = startLine;
					startLine = false;
					sectionStart = iter;
					sectionStartPos = position;

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

	//printf("DEBUG: string to parse = \"%s\"\n", text.ToCString());

	if (type == SectionType::text)
	{
		auto iter = keywords.find(text.ToCString());

		if (iter != keywords.end())
		{
			out_token.type = iter->second;
			return CE_OK;
		}

		if (text == "true")
		{
			out_token.type = TokenType::bool_constant;
			out_token.value.boolVal = true;
			return CE_OK;
		}
		else if (text == "false")
		{
			out_token.type = TokenType::bool_constant;
			out_token.value.boolVal = false;
			return CE_OK;
		}

		out_token.type = TokenType::identifier;
		out_token.name = text;		
	}
	else if (type == SectionType::number)
	{
		auto iter = text.FindFirstOf(".e", text.ConstBeginIterator());

		if (iter == text.ConstEndIterator())
		{
			out_token.type = TokenType::int_constant;
			out_token.value.intVal = atoi(text.ToCString());
		}
		else
		{
			out_token.type = TokenType::float_constant;
			out_token.value.floatVal = atof(text.ToCString());
		}

	}

	return CE_OK;
}

Ceng::CRESULT Tokenizer::RemoveComments(const std::vector<Token>& in_tokens, std::vector<Token>& out_tokens)
{
	std::vector<Token> tokens;

	//auto iter = in_tokens.cbegin();

	bool singleLine = false;
	bool comment = false;

	for(auto&x : in_tokens)
	{
		if (x.type == TokenType::preprocess_comment)
		{
			singleLine = true;
			comment = true;
			continue;
		}
		else if (x.type == TokenType::preprocess_comment_start)
		{
			singleLine = false;
			comment = true;
			continue;
		}
		else if (x.type == TokenType::preprocess_comment_end)
		{
			singleLine = false;
			comment = false;
			continue;
		}

		if (!comment)
		{
			tokens.push_back(x);
		}
		else
		{
			if (singleLine)
			{
				if (x.endLine)
				{
					singleLine = false;
					comment = false;

					if (tokens.size() > 0)
					{
						tokens.back().endLine = true;
					}					
				}
			}
		}
	}

	out_tokens = std::move(tokens);
	return Ceng::CE_OK;
}