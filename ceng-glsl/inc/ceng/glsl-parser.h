#ifndef CENG_GLSL_PARSER_H
#define CENG_GLSL_PARSER_H

#include <ceng/datatypes/return-val.h>

#include <vector>
#include "token.h"

namespace Ceng
{
	class GLSL_Parser
	{
	public:

		std::vector<Token> tokens;

	public:
		
		CRESULT Parse(const std::vector<Token>& in_tokens);

		const Token& PeekToken();

		const Token NextToken();

		void S_Translation_Unit();
	};
}

#endif