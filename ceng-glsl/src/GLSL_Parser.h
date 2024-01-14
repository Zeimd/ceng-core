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
#include "PrimaryExpression.h"
#include "Expression.h"
#include "PostfixExpression.h"

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

		ParserReturnValue S_LiteralToken(const Token& token);

		ParserReturnValue S_StorageQualifier(std::shared_ptr<StorageQualifier>& sq);
		
		ParserReturnValue S_TypeQualifier(std::shared_ptr<TypeQualifier>& tq);

		ParserReturnValue S_DatatypeToken(TokenType::value value);

		ParserReturnValue S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& sq, std::shared_ptr<TypeSpecifierNoArray>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifierNoPrec>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifier>& ts);

		ParserReturnValue S_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& spec);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);
		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_PrimaryExpression(std::shared_ptr<PrimaryExpression>& ex);

		ParserReturnValue S_PostfixExpression(std::shared_ptr<PostfixExpression>& ex);
		
		// postfix_expression INC_OP
		ParserReturnValue S_PostfixExpression_IncOp(std::shared_ptr<PostfixExpression>& ex);

		// postfix_expression DEC_OP
		ParserReturnValue S_PostfixExpression_DecOp(std::shared_ptr<PostfixExpression>& ex);

		ParserReturnValue S_PostfixExpression_Dot(std::shared_ptr<PostfixExpression>& ex);

		// postfix_expression DOT FIELD_SELECTION
		ParserReturnValue S_PostfixExpression_Dot_IdToken(std::shared_ptr<PostfixExpression>& ex, const Token& token);

		ParserReturnValue S_PostfixExpression_LBracket(std::shared_ptr<PostfixExpression>& ex);
		ParserReturnValue S_PostfixExpression_LBracket_IntExpression(std::shared_ptr<PostfixExpression>& ex,std::shared_ptr<IntegerExpression>& intEx);

		// postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET
		ParserReturnValue S_PostfixExpression_LBracket_IntExpression_RBracket(std::shared_ptr<PostfixExpression>& ex, std::shared_ptr<IntegerExpression>& intEx);
		
	};
}

#endif