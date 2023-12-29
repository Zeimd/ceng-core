#ifndef CENG_GLSL_TOKENIZER_H
#define CENG_GLSL_TOKENIZER_H

#include <vector>

#include "token.h"

namespace Ceng
{
	class Tokenizer
	{
	protected:

	public:
		Tokenizer();
		~Tokenizer();

		std::vector<Token> Tokenize(Ceng::StringUtf8& source);
	};
}

#endif