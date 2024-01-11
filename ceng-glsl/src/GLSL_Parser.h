#ifndef CENG_GLSL_PARSER_H
#define CENG_GLSL_PARSER_H

#include <ceng/datatypes/return-val.h>

#include <vector>
#include <ceng/GLSL/Token.h>
#include <ceng/GLSL/IParser.h>

#include "StorageQualifier.h"
#include "TypeSpecifierNoArray.h"
#include "TypeQualifier.h"
#include "TypeSpecifierNoPrecision.h"
#include "TypeSpecifier.h"
#include "FullySpecifiedType.h"
#include "SingleDeclaration.h"
#include "InitDeclaratorList.h"
#include "Declaration.h"
#include "StorageQualifierType.h"

#include "ParserReturnValue.h"

namespace Ceng
{
	class GLSL_Parser : public GLSL::IParser
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

		struct ShiftHandlerReturn
		{
			ParserReturnValue retVal;
			bool invalid;
		};

		typedef ShiftHandlerReturn (GLSL_Parser::* ReductionHandler)(const Token& token);
		typedef ShiftHandlerReturn (GLSL_Parser::* ShiftHandler)(const Token& token);
		typedef ShiftHandlerReturn (GLSL_Parser::* GotoHandler)(INonTerminal* nonTerminal);

	protected:
		~GLSL_Parser() override
		{
		}
	public:
		GLSL_Parser();

		void Release() override;

		const Ceng::StringUtf8 GetLog() const override;
		
		CRESULT Parse(const std::vector<Token>& in_tokens, GLSL::AbstractSyntaxTree& output) override;

		const Token& PeekToken();

		const Token NextToken();

		// Used when PeekToken() has been used to deduce next parser action
		void DiscardNext();

		void Log(const char* text, LogPrefix prefix=log_nominal);
		void Log(const Ceng::StringUtf8& text, LogPrefix prefix = log_nominal);

		void LogError(const char* error);
		//void LogError(const char* fmt_str,...);
		void LogError(const Ceng::StringUtf8& error);

		void LogDebug(const char* error);
		void LogDebug(const Ceng::StringUtf8& error);

		static const char* GetPrefixText(LogPrefix prefix);

	protected:

		ParserReturnValue StateFuncSkeleton(const char* callerName,ShiftHandler shiftHandler, GotoHandler gotoHandler);

		ParserReturnValue S_TranslationUnit();

		ShiftHandlerReturn Shift_S_TranslationUnit(const Token& token);
		ShiftHandlerReturn Goto_S_TranslationUnit(INonTerminal* nonTerminal);
		
		ParserReturnValue S_StorageQualifierToken(TokenType::value value);
		ParserReturnValue S_StorageQualifier(StorageQualifier* sq);
		
		ParserReturnValue S_TypeQualifier(TypeQualifier* sq);

		ShiftHandlerReturn Shift_S_TypeQualifier(const Token& token);
		ShiftHandlerReturn Goto_S_TypeQualifier(INonTerminal* nonTerminal);

		ParserReturnValue S_DatatypeToken(TokenType::value value);


		
	};
}

#endif