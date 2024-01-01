#ifndef CENG_GLSL_TOKEN_H
#define CENG_GLSL_TOKEN_H

#include <ceng/datatypes/ce-string.h>

#include <memory>
#include <vector>

#include "token-type.h"
#include "token-category.h"

namespace Ceng
{
	union LiteralValue
	{
		Ceng::FLOAT64 doubleVal;
		Ceng::UINT64 longVal;
		Ceng::UINT32 intVal;
		Ceng::FLOAT32 floatVal;
		bool boolVal;
	};

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

		Ceng::TokenCategory::value category;

		// Name of identifier or user-defined type
		Ceng::StringUtf8 name;

		// Value of literal. Space reserved up to double precision.
		LiteralValue value;

	public:

		Token();

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const Ceng::StringUtf8& name);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const char* name);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const Ceng::StringUtf8& name, bool value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const Ceng::StringUtf8& name, Ceng::UINT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const Ceng::StringUtf8& name, Ceng::FLOAT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const char* name, bool value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const char* name, Ceng::UINT32 value);

		Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
			bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
			const char* name, Ceng::FLOAT32 value);

		Ceng::StringUtf8 ToString() const;

		Ceng::StringUtf8 ToDiagnosticString() const;

		//static const char* TokenTypeText(TokenType::value type);
	};
}

#endif