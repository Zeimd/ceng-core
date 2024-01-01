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

		// Number of shifts since last reduction
		Ceng::UINT32 shiftCount;

		enum LogPrefix
		{
			log_nominal,
			log_error,
			log_debug,
		};

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

		ParserReturnValue S_Translation_Unit();
		ParserReturnValue S_StorageQ(StorageQualifier* sq);


		//void S_TU_TypeSpecNoArr(const TypeSpecifierNoArray& typeSpec);

		//void S_TU_TypeSpecNoArr_LB(const TypeSpecifierNoArray& typeSpec);

		//void S_TU_TypeSpecNoPrec(const TypeSpecifierNoArray& typeSpec);

		//void S_TU_TypeQ(const TypeQualifier& typeQualifier);

		/*
		void S_TU_TypeQ_TypeSpecNoArr(const TypeQualifier& typeQualifier, const TypeSpecifierNoArray& typeSpecNoArr);
		void S_TU_TypeQ_TypeSpecNoPrec(const TypeQualifier& typeQualifier, const TypeSpecifierNoPrec& typeSpecNoPrec);
		void S_TU_TypeQ_TypeSpecifier(const TypeQualifier& typeQualifier, const TypeSpecifier& typeSpec);
		void S_TU_FullSpecType(const FullySpecifiedType& typeSpec);
		void S_TU_FullSpecType_identifier(const FullySpecifiedType& typeSpec, const Ceng::StringUtf8& name);
		void S_TU_SingleDeclaration(const SingleDeclaration& singleDecl);
		void S_TU_InitDeclList(const InitDeclaratorList& initDeclList);
		*/
		

		
	};
}

#endif