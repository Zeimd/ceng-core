#ifndef CENG_GLSL_TOKENIZER_H
#define CENG_GLSL_TOKENIZER_H

#include <vector>

#include <ceng/datatypes/return-val.h>

#include "token.h"

namespace Ceng
{
	class Tokenizer
	{
	protected:

	public:
		Tokenizer();
		~Tokenizer();

		Ceng::CRESULT Tokenize(const Ceng::StringUtf8& fileName, const Ceng::StringUtf8& source, std::vector<Token>& out_tokens);
	};
}

#endif