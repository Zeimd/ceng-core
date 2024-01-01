#ifndef CENG_GLSL_TOKENIZER_H
#define CENG_GLSL_TOKENIZER_H

#include <vector>

#include <ceng/datatypes/return-val.h>

#include <ceng/GLSL/Token.h>

namespace Ceng
{
	namespace SectionType
	{
		enum value
		{
			text,
			number,
			unused,
		};
	};

	class Tokenizer
	{
	protected:

	public:
		Tokenizer();
		~Tokenizer();

		Ceng::CRESULT Tokenize(const Ceng::StringUtf8& fileName, const Ceng::StringUtf8& source, std::vector<Token>& out_tokens);

		Ceng::CRESULT RemoveComments(const std::vector<Token>& in_tokens, std::vector<Token>& out_tokens);

		static Ceng::CRESULT TokenizeString(SectionType::value type, Ceng::StringUtf8::CONST_ITERATOR_TYPE start, Ceng::StringUtf8::CONST_ITERATOR_TYPE& end, Token& out_token);
	};
}

#endif