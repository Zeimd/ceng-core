#ifndef CENG_GLSL_TOKEN_H
#define CENG_GLSL_TOKEN_H

#include <ceng/datatypes/ce-string.h>

#include <memory>
#include <vector>

#include "token-type.h"

namespace Ceng
{
	class Token
	{
	public:
		std::shared_ptr<const Ceng::StringUtf8> file;
		Ceng::UINT32 line;
		Ceng::UINT32 position;

		// Was there a space on the left side in the source file
		bool leftSpace;

		// Was there a space on the right side in the source file
		bool rightSpace;

		// Was first non-white space on source line
		bool startLine;

		// Was last non-white space on source line
		bool endLine;

		Ceng::TokenType::value type;

		// Name of identifier or user-defined type
		Ceng::StringUtf8 name;

		// Value of literal
		std::vector<Ceng::UINT8> literalData;

	public:

		Token();

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const Ceng::StringUtf8& name);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const char* name);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const Ceng::StringUtf8& name, bool value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const Ceng::StringUtf8& name, Ceng::UINT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const Ceng::StringUtf8& name, Ceng::FLOAT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const char* name, bool value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const char* name, Ceng::UINT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
			const char* name, Ceng::FLOAT32 value);

		Ceng::StringUtf8 ToString();

		//static const char* TokenTypeText(TokenType::value type);
	};
}

#endif