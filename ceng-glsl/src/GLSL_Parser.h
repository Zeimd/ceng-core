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
#include "FunctionIdentifier.h"
#include "FunctionCallHeader.h"
#include "FuncCallHeaderParams.h"
#include "FuncCallHeaderNoParams.h"
#include "FunctionCallGeneric.h"
#include "FunctionCallOrMethod.h"
#include "FunctionCall.h"

#include "Statement.h"
#include "StatementList.h"
#include "SwitchStatement.h"
#include "SwitchStatementList.h"
#include "CaseLabel.h"
#include "Condition.h"
#include "ConditionOpt.h"
#include "Declaration.h"
#include "DeclarationStatement.h"
#include "SimpleStatement.h"
#include "SelectionRestStatement.h"
#include "SelectionStatement.h"
#include "ExpressionStatement.h"

#include "CompoundStatement.h"
#include "CompoundStatementNoNewScope.h"
#include "StatementNoNewScope.h"
#include "ForInitStatement.h"
#include "ForRestStatement.h"
#include "JumpStatement.h"
#include "IterationStatement.h"


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

		ParserReturnValue S_TypeSpecifierNonArray(std::shared_ptr<TypeSpecifierNoArray>& ts);

		ParserReturnValue S_TypeSpecifierNonArray_LBracket(std::shared_ptr<TypeSpecifierNoArray>& ts);

		ParserReturnValue S_TypeSpecifierNonArray_LBracket_Expression(std::shared_ptr<TypeSpecifierNoArray>& ts,
			std::shared_ptr<Expression>& expression);

		// Reduction: type_specifier_non_array LBRACKET constant_express RBRACKET
		ParserReturnValue S_TypeSpecifierNonArray_LBracket_Expression_RBracket(std::shared_ptr<TypeSpecifierNoArray>& ts,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_TypeSpecifierNonArray_LBracket_RBracket(std::shared_ptr<TypeSpecifierNoArray>& ts);

		ParserReturnValue S_TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoPrec>& ts);

		ParserReturnValue S_TypeSpecifier(std::shared_ptr<TypeSpecifier>& ts);

		ParserReturnValue S_FunctionIdentifier(std::shared_ptr<FunctionIdentifier>& funcId);

		// Reduction: function_identifier LPAREN
		ParserReturnValue S_FunctionIdentifier_Lparen(std::shared_ptr<FunctionIdentifier>& funcId);

		ParserReturnValue S_FunctionCallHeader(std::shared_ptr<FunctionCallHeader>& funcHeader);

		ParserReturnValue S_FunctionCallHeader_VoidToken(std::shared_ptr<FunctionCallHeader>& funcHeader);

		ParserReturnValue S_FunctionCallHeaderNoParams(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam);

		// Reduction: function_call_header_no_params RIGHT_PAREN
		ParserReturnValue S_FunctionCallHeaderNoParams_RParen(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam);

		ParserReturnValue S_FunctionCallHeader_AssignEx(std::shared_ptr<FunctionCallHeader>& funcHeader,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_FunctionCallHeaderWithParams(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam);

		// Reduction: function_call_header_with_params RIGHT_PAREN
		ParserReturnValue S_FunctionCallHeaderWithParams_RParen(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam);

		ParserReturnValue S_FunctionCallHeaderWithParams_Comma(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam);

		ParserReturnValue S_FunctionCallHeaderWithParams_Comma_AssignEx(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_FunctionCallGeneric(std::shared_ptr<FunctionCallGeneric>& funcCall);

		ParserReturnValue S_FunctionCallOrMethod(std::shared_ptr<FunctionCallOrMethod>& funcCall);

		ParserReturnValue S_FunctionCall(std::shared_ptr<FunctionCall>& funcCall);

		ParserReturnValue S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& sq, std::shared_ptr<TypeSpecifierNoArray>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifierNoPrec>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifier>& ts);

		ParserReturnValue S_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& spec);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_Expression(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Expression>& expression, std::shared_ptr<Initializer>& initializer);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_PrimaryExpression(std::shared_ptr<PrimaryExpression>& ex);

		ParserReturnValue S_PostfixExpression(std::shared_ptr<PostfixExpression>& ex);

		ParserReturnValue S_PostfixExpression_Dot(std::shared_ptr<PostfixExpression>& ex);

		ParserReturnValue S_PostfixExpression_Dot_FunctionCallGeneric(std::shared_ptr<PostfixExpression>& ex,
			std::shared_ptr<FunctionCallGeneric>& funcCall);
		
		// postfix_expression INC_OP
		ParserReturnValue S_PostfixExpression_IncOp(std::shared_ptr<PostfixExpression>& ex);

		// postfix_expression DEC_OP
		ParserReturnValue S_PostfixExpression_DecOp(std::shared_ptr<PostfixExpression>& ex);

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

		// reduction: expression -> assignment_expression
		ParserReturnValue S_Expression(std::shared_ptr<Expression>& ex);

		ParserReturnValue S_Expression_Comma(std::shared_ptr<Expression>& ex);

		// reduction: expression -> expression COMMA assignment_expression
		ParserReturnValue S_Expression_Comma_AssignmentExpression(std::shared_ptr<Expression>& expression,
			std::shared_ptr<AssignmentExpression>& assignEx);

		// reduction: expression_statement -> expression SEMICOLON
		ParserReturnValue S_Expression_Semicolon(std::shared_ptr<Expression>& ex);

		ParserReturnValue S_SingleDeclaration(std::shared_ptr<SingleDeclaration>& singleDecl);

		ParserReturnValue S_InitDeclaratorList(std::shared_ptr<InitDeclaratorList>& initList);

		ParserReturnValue S_InitDeclaratorList_Semicolon(std::shared_ptr<InitDeclaratorList>& initList);

		ParserReturnValue S_InitDeclaratorList_Comma(std::shared_ptr<InitDeclaratorList>& initList);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken(std::shared_ptr<InitDeclaratorList>& initList,const Token& token);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& initList, const Token& token);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_AssignEx(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_Initializer(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Initializer>& initializer);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_Expression(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_AssignEx(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_Initializer(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
			std::shared_ptr<Expression>& expression, std::shared_ptr<Initializer>& initializer);

		ParserReturnValue S_Declaration(std::shared_ptr<Declaration>& singleDecl);

		ParserReturnValue S_DeclarationStatement(std::shared_ptr<DeclarationStatement>& declStatement);

		ParserReturnValue S_SimpleStatement(std::shared_ptr<SimpleStatement>& simpleStatement);

		ParserReturnValue S_Statement(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_Statement_ElseToken(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_Statement_ElseToken_Statement(std::shared_ptr<Statement>& a, std::shared_ptr<Statement>& b);

		ParserReturnValue S_SelectionRestStatement(std::shared_ptr<SelectionRestStatement>& selectionRest);

		ParserReturnValue S_StatementList(std::shared_ptr<StatementList>& statementList);

		ParserReturnValue S_StatementList_Statement(std::shared_ptr<StatementList>& statementList, std::shared_ptr<Statement>& statement);

		ParserReturnValue S_ExpressionStatement(std::shared_ptr<ExpressionStatement>& expressionStatement);

		ParserReturnValue S_SelectionStatement(std::shared_ptr<SelectionStatement>& selectionStatement);

		ParserReturnValue S_IfToken();

		ParserReturnValue S_IfToken_LParen();

		ParserReturnValue S_IfToken_LParen_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_IfToken_LParen_Expression_RParen(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_IfToken_LParen_Expression_RParen_SelectionRestStatement(std::shared_ptr<Expression>& expression, 
			std::shared_ptr<SelectionRestStatement>& selectionRest);

		ParserReturnValue S_Condition(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_SwitchToken();

		ParserReturnValue S_SwitchToken_LParen();

		ParserReturnValue S_SwitchToken_LParen_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_SwitchStatementList(std::shared_ptr<Expression>& expression,
			std::shared_ptr<SwitchStatementList>& statementList);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_SwitchStatementList_RBrace(std::shared_ptr<Expression>& expression,
			std::shared_ptr<SwitchStatementList>& statementList);

		ParserReturnValue S_SwitchStatementList(std::shared_ptr<SwitchStatementList>& condition);

		ParserReturnValue S_SwitchStatement(std::shared_ptr<SwitchStatement>& switchStatement);

		ParserReturnValue S_CaseLabel(std::shared_ptr<CaseLabel>& label);

		ParserReturnValue S_CaseToken();

		ParserReturnValue S_CaseToken_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_CaseToken_Expression_Colon(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_DefaultToken();

		ParserReturnValue S_DefaultToken_Colon();

		ParserReturnValue S_ContinueToken();

		ParserReturnValue S_ContinueToken_Semicolon();

		ParserReturnValue S_BreakToken();

		ParserReturnValue S_BreakToken_Semicolon();

		ParserReturnValue S_ReturnToken();

		ParserReturnValue S_ReturnToken_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ReturnToken_Expression_Semicolon(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ReturnToken_Semicolon();

		ParserReturnValue S_DiscardToken();

		ParserReturnValue S_DiscardToken_Semicolon();

		ParserReturnValue S_JumpStatement(std::shared_ptr<JumpStatement>& jumpStatement);

		ParserReturnValue S_ForInitStatement(std::shared_ptr<ForInitStatement>& statement);

		ParserReturnValue S_ConditionOpt(std::shared_ptr<ConditionOpt>& conditionOpt);

		ParserReturnValue S_ConditionOpt_Semicolon(std::shared_ptr<ConditionOpt>& conditionOpt);

		ParserReturnValue S_ConditionOpt_Semicolon_Expression(std::shared_ptr<ConditionOpt>& conditionOpt,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ForRestStatement(std::shared_ptr<ForRestStatement>& statement);

		ParserReturnValue S_WhileToken();

		ParserReturnValue S_WhileToken_LParen();

		ParserReturnValue S_WhileToken_LParen_Condition(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_WhileToken_LParen_Condition_RParen(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_WhileToken_LParen_Condition_RParen_StatementNoNewScope(std::shared_ptr<Condition>& condition,
			std::shared_ptr<StatementNoNewScope>& block);

		ParserReturnValue S_DoToken();

		ParserReturnValue S_DoToken_Statement(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_DoToken_Statement_WhileToken(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_DoToken_Statement_WhileToken_LParen(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_DoToken_Statement_WhileToken_LParen_Expression(std::shared_ptr<Statement>& statement,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_DoToken_Statement_WhileToken_LParen_Expression_RParen(std::shared_ptr<Statement>& statement,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_DoToken_Statement_WhileToken_LParen_Expression_RParen_Semicolon(std::shared_ptr<Statement>& statement,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ForToken();

		ParserReturnValue S_ForToken_LParen();

		ParserReturnValue S_ForToken_LParen_ForInitStatement(std::shared_ptr<ForInitStatement>& init);

		ParserReturnValue S_ForToken_LParen_ForInitStatement_ForRestStatement(std::shared_ptr<ForInitStatement>& init,
			std::shared_ptr<ForRestStatement>& rest);

		ParserReturnValue S_ForToken_LParen_ForInitStatement_ForRestStatement_RParen(std::shared_ptr<ForInitStatement>& init,
			std::shared_ptr<ForRestStatement>& rest);

		ParserReturnValue S_ForToken_LParen_ForInitStatement_ForRestStatement_RParen_StatementNoNewScope(std::shared_ptr<ForInitStatement>& init,
			std::shared_ptr<ForRestStatement>& rest, std::shared_ptr<StatementNoNewScope>& block);

		ParserReturnValue S_IteratorStatement(std::shared_ptr<IterationStatement>& statement);

		ParserReturnValue S_StatementNoNewScope(std::shared_ptr<StatementNoNewScope>& block);

		ParserReturnValue S_CompoundStatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& block);

		ParserReturnValue S_CompoundStatement(std::shared_ptr<CompoundStatement>& statement);

	};
}

#endif