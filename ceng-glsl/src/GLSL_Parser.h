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
#include "HandlerReturn.h"
#include "IStateHandler.h"

namespace Ceng
{
	class GLSL_Parser : public GLSL::IParser
	{
	public:

		std::vector<Token> tokens;

		std::vector<Token>::const_iterator tokenIter;

		Log log;

		typedef HandlerReturn (GLSL_Parser::* ReductionHandler)(const Token& next);
		typedef HandlerReturn (GLSL_Parser::* ShiftHandler)(const Token& next);
		typedef HandlerReturn (GLSL_Parser::* GotoHandler)(INonTerminal* nonTerminal);

	protected:
		~GLSL_Parser() override
		{
		}
	public:
		GLSL_Parser();

		void Release() override;

		const Log& GetLog() const override;
		
		CRESULT Parse(const std::vector<Token>& in_tokens, GLSL::AbstractSyntaxTree& output) override;

		const Token& PeekToken();

		const Token NextToken();

		// Used when PeekToken() has been used to deduce next parser action
		void DiscardNext();

	public:

		ParserReturnValue StateFuncSkeleton(const char* callerName, IStateHandler& handler);

		ParserReturnValue S_TranslationUnit();
		
		ParserReturnValue S_StorageQualifierToken(TokenType::value value);
		ParserReturnValue S_StorageQualifier(std::shared_ptr<StorageQualifier>& sq);
		
		ParserReturnValue S_TypeQualifier(std::shared_ptr<TypeQualifier>& tq);

		ParserReturnValue S_DatatypeToken(TokenType::value value);

		ParserReturnValue S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& sq, std::shared_ptr<TypeSpecifierNoArray>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifierNoPrec>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifier>& ts);


		
	};
}

#endif