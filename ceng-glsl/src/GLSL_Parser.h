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
#include "UnaryExpression.h"
#include "UnaryOperator.h"
#include "MultiplicativeExpression.h"
#include "AdditiveExpression.h"
#include "ShiftExpression.h"
#include "RelationalExpression.h"
#include "EqualityExpression.h"
#include "AndExpression.h"
#include "XorExpression.h"
#include "OrExpression.h"
#include "LogicalAndExpression.h"
#include "LogicalOrExpression.h"
#include "LogicalXorExpression.h"
#include "ConditionalExpression.h"
#include "AssignmentExpression.h"
#include "AssignmentOperator.h"
#include "Expression.h"

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

		ParserReturnValue S_IdentifierToken(const Token& token);

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

		ParserReturnValue S_UnaryExpression(std::shared_ptr<UnaryExpression>& ex);

		// reduce [EQUAL, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, ADD_ASSIGN, SUB_ASSIGN, LEFT_ASSIGN, RIGHT_ASSIGN, AND_ASSIGN, OR_ASSIGN, XOR_ASSIGN]
		ParserReturnValue S_AssignToken(const Token& token);

		ParserReturnValue S_UnaryExpression_AssignOperator(std::shared_ptr<UnaryExpression>& ex, std::shared_ptr<AssignmentOperator>& assignOp);

		// reduction: unary_expression assignment_operator assignment_expression
		ParserReturnValue S_UnaryExpression_AssignOperator_AssignExpression(std::shared_ptr<UnaryExpression>& ex, 
			std::shared_ptr<AssignmentOperator>& assignOp, std::shared_ptr<AssignmentExpression>& assignEx);

		// INC_OP
		// NOTE: entered only if stack top is an operator
		ParserReturnValue S_IncOP();

		// DEC_OP
		// NOTE: entered only if stack top is an operator
		ParserReturnValue S_DecOP();

		// INC_OP unary_expression
		ParserReturnValue S_IncOP_UnaryExpression(std::shared_ptr<UnaryExpression>& ex);

		// DEC_OP unary_expression
		ParserReturnValue S_DecOP_UnaryExpression(std::shared_ptr<UnaryExpression>& ex);

		// unary_operator unary_expression
		ParserReturnValue S_UnaryOperator_UnaryExpression(std::shared_ptr<UnaryOperator>& op, std::shared_ptr<UnaryExpression>& ex);

		// unary_expression
		ParserReturnValue S_MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& ex);

		ParserReturnValue S_MultiplicativeExpression_MulToken(std::shared_ptr<MultiplicativeExpression>& ex, const Token& token);

		// multiplicative_expression [STAR | SLASH | PERCENT ] unary_expression
		ParserReturnValue S_MultiplicativeExpression_MulToken_UnaryExpression(std::shared_ptr<MultiplicativeExpression>& mulEx, const Token& token,
			std::shared_ptr<UnaryExpression>& unaryEx);

		// multiplicative_expression
		ParserReturnValue S_AdditiveExpression(std::shared_ptr<AdditiveExpression>& ex);

		ParserReturnValue S_AdditiveExpression_AddToken(std::shared_ptr<AdditiveExpression>& ex, const Token& token);

		// additive_expression [PLUS | DASH] unary_expression
		ParserReturnValue S_AdditiveExpression_AddToken_MultiplicativeEx(std::shared_ptr<AdditiveExpression>& addEx, const Token& token,
			std::shared_ptr<MultiplicativeExpression>& mulEx);

		// additive_expression
		ParserReturnValue S_ShiftExpression(std::shared_ptr<ShiftExpression>& ex);

		ParserReturnValue S_ShiftExpression_ShiftToken(std::shared_ptr<ShiftExpression>& ex, const Token& token);

		// shift_expression [LEFT_OP | RIGHT_OP] additive_expression
		ParserReturnValue S_ShiftExpression_ShiftToken_AdditiveEx(std::shared_ptr<ShiftExpression>& shiftEx, const Token& token,
			std::shared_ptr<AdditiveExpression>& addEx);

		// shift_expression
		ParserReturnValue S_RelationalExpression(std::shared_ptr<RelationalExpression>& ex);

		ParserReturnValue S_RelationalExpression_RelationalToken(std::shared_ptr<RelationalExpression>& ex, const Token& token);

		// relational_expression [LEFT_ANGLE | RIGHT_ANGLE | GE_OP | LE_OP] shift_expression
		ParserReturnValue S_RelationalExpression_RelationalToken_ShiftEx(std::shared_ptr<RelationalExpression>& relativeEx, const Token& token,
			std::shared_ptr<ShiftExpression>& shiftEx);

		// relational_expression
		ParserReturnValue S_EqualityExpression(std::shared_ptr<EqualityExpression>& ex);

		ParserReturnValue S_EqualityExpression_EqualityToken(std::shared_ptr<EqualityExpression>& ex, const Token& token);

		// equality_expression [EQ_OP | NE_OP] relational_expression
		ParserReturnValue S_EqualityExpression_EqualityToken_RelativeEx(std::shared_ptr<EqualityExpression>& equalityEx, const Token& token,
			std::shared_ptr<RelationalExpression>& relativeEx);

		// equality_expression
		ParserReturnValue S_AndExpression(std::shared_ptr<AndExpression>& ex);

		ParserReturnValue S_AndExpression_Ampersand(std::shared_ptr<AndExpression>& ex);

		// and_expression AMPERSAND equality_expression
		ParserReturnValue S_AndExpression_Ampersand_RelativeEx(std::shared_ptr<AndExpression>& andEx,
			std::shared_ptr<EqualityExpression>& equalityEx);

		// and_expression
		ParserReturnValue S_XorExpression(std::shared_ptr<XorExpression>& ex);

		ParserReturnValue S_XorExpression_Caret(std::shared_ptr<XorExpression>& ex);

		// xor_expression CARET and_expression
		ParserReturnValue S_XorExpression_Caret_AndEx(std::shared_ptr<XorExpression>& xorEx,
			std::shared_ptr<AndExpression>& andEx);

		// xor_expression
		ParserReturnValue S_OrExpression(std::shared_ptr<OrExpression>& ex);

		ParserReturnValue S_OrExpression_Vbar(std::shared_ptr<OrExpression>& ex);

		// or_expression VERTICAL_BAR xor_expression
		ParserReturnValue S_OrExpression_Vbar_XorEx(std::shared_ptr<OrExpression>& orEx,
			std::shared_ptr<XorExpression>& xorEx);

		// or_expression
		ParserReturnValue S_LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& ex);

		ParserReturnValue S_LogicalAndExpression_AndOp(std::shared_ptr<LogicalAndExpression>& ex);

		// logical_and_expression AND_OP or_expression
		ParserReturnValue S_LogicalAndExpression_AndOp_OrEx(std::shared_ptr<LogicalAndExpression>& logicAndEx,
			std::shared_ptr<OrExpression>& orEx);

		// logical_and_expression
		ParserReturnValue S_LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& ex);

		ParserReturnValue S_LogicalXorExpression_XorOp(std::shared_ptr<LogicalXorExpression>& ex);

		// logical_xor_expression XOR_OP logical_and_expression
		ParserReturnValue S_LogicalXorExpression_XorOp_OrEx(std::shared_ptr<LogicalXorExpression>& logicXorEx,
			std::shared_ptr<LogicalAndExpression>& logicAndEx);

		// logical_xor_expression
		ParserReturnValue S_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& ex);

		ParserReturnValue S_LogicalOrExpression_OrOp(std::shared_ptr<LogicalOrExpression>& ex);

		// logical_or_expression OR_OP logical_xor_expression
		ParserReturnValue S_LogicalOrExpression_OrOp_OrEx(std::shared_ptr<LogicalOrExpression>& logicOrEx,
			std::shared_ptr<LogicalXorExpression>& logicXorEx);

		// logical_or_expression
		ParserReturnValue S_ConditionalExpression(std::shared_ptr<ConditionalExpression>& ex);

		ParserReturnValue S_CondExpression_Question(std::shared_ptr<ConditionalExpression>& ex);

		ParserReturnValue S_CondExpression_Question_Expression(std::shared_ptr<ConditionalExpression>& condEx,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_CondExpression_Question_Expression_Colon(std::shared_ptr<ConditionalExpression>& condEx,
			std::shared_ptr<Expression>& expression);

		// conditional_expression QUESTION expression COLON assignment_expression
		ParserReturnValue S_CondExpression_Question_Expression_Colon_AssignEx(std::shared_ptr<ConditionalExpression>& condEx,
			std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx);

		// conditional_expression
		ParserReturnValue S_AssignmentExpression(std::shared_ptr<AssignmentExpression>& ex);

		// reduction: assignment_expression
		ParserReturnValue S_Expression(std::shared_ptr<Expression>& ex);

		ParserReturnValue S_Expression_Comma(std::shared_ptr<Expression>& ex);

		// reduction: expression COMMA assignment_expression
		ParserReturnValue S_Expression_Comma_AssignmentExpression(std::shared_ptr<Expression>& expression,
			std::shared_ptr<AssignmentExpression>& assignEx);
	};
}

#endif