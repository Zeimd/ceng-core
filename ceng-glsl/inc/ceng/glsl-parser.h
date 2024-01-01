#ifndef CENG_GLSL_PARSER_H
#define CENG_GLSL_PARSER_H

#include <ceng/datatypes/return-val.h>

#include <vector>
#include "token.h"

#include "storage-qualifier.h"
#include "type-spec-no-arr.h"

namespace Ceng
{
	class GLSL_Parser
	{
	public:

		std::vector<Token> tokens;

		std::vector<Token>::const_iterator tokenIter;

		Ceng::StringUtf8 log;

		enum LogPrefix
		{
			log_nominal,
			log_error,
			log_debug,
		};

	public:
		
		CRESULT Parse(const std::vector<Token>& in_tokens);

		const Token& PeekToken();

		const Token NextToken();

		// Used when PeekToken() has been used to deduce next parser action
		void DiscardNext();

		void Log(const char* text, LogPrefix prefix=log_nominal);
		void Log(const Ceng::StringUtf8& text, LogPrefix prefix = log_nominal);

		void LogError(const char* error);
		void LogError(const char* fmt_str,...);
		void LogError(const Ceng::StringUtf8& error);

		void LogDebug(const char* error);
		void LogDebug(const Ceng::StringUtf8& error);

		static const char* GetPrefixText(LogPrefix prefix);

	protected:

		void S_Translation_Unit();
		void S_TU_TypeSpecNoArr(const TypeSpecifierNoArray& typeSpec);

		void S_TU_TypeSpecNoArr_LB(const TypeSpecifierNoArray& typeSpec);

		void S_TU_TypeSpecNoPrec(const TypeSpecifierNoArray& typeSpec);
		void S_TU_StorageQ(StorageQualifier::value sq);
	};
}

#endif