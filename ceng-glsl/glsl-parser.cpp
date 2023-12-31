#include "inc/ceng/glsl-parser.h"

using namespace Ceng;

CRESULT GLSL_Parser::Parse(const std::vector<Token>& in_tokens)
{
	tokens = in_tokens;

	void State_Translation_Unit();

	return CE_OK;
}

const Token& GLSL_Parser::PeekToken()
{
	return tokens.back();
}

const Token GLSL_Parser::NextToken()
{
	Token temp = tokens.back();

	tokens.pop_back();

	return temp;
}

void GLSL_Parser::S_Translation_Unit()
{

}