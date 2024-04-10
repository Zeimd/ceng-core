#include "IStateHandler.h"

#include "GLSL_Parser.h"

#include "TranslationUnit.h"

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

#include "StructDeclarator.h"
#include "StructDeclaratorList.h"
#include "StructDeclaration.h"
#include "StructDeclarationList.h"
#include "StructSpecifier.h"

#include "FunctionHeader.h"
#include "FunctionHeaderWithParams.h"
#include "ParameterDeclaration.h"
#include "ParameterDeclarator.h"
#include "ParameterQualifier.h"
#include "ParameterTypeQualifier.h"
#include "FunctionDeclarator.h"
#include "FunctionPrototype.h"
#include "FunctionDefinition.h"

#include "LayoutQualifier.h"
#include "LayoutQualifierId.h"
#include "LayoutQualifierIdList.h"


using namespace Ceng;

HandlerReturn IStateHandler::DefaultExpressionShift(GLSL_Parser* parser, const Token& next)
{
	parser->log.Debug(__FUNCTION__);

	ParserReturnValue retVal;
	bool valid = true;

	if (next.category == TokenCategory::data_type)
	{
		retVal = parser->S_DatatypeToken(next.type);
	}
	else
	{
		switch (next.type)
		{
		case TokenType::identifier:
			if (parser->symbolDatabase->IsCustomType(next.name))
			{
				retVal = parser->S_CustomTypeToken(next);
			}
			else
			{
				retVal = parser->S_IdentifierToken(next);
			}			
			break;
		case TokenType::keyword_const:
		case TokenType::keyword_attribute:
		case TokenType::keyword_varying:
		case TokenType::keyword_uniform:
		case TokenType::keyword_in:
		case TokenType::keyword_out:
			retVal = parser->S_StorageQualifierToken(next.type);
			break;
		case TokenType::keyword_precision:
			retVal = parser->S_PrecisionToken();
			break;
		case TokenType::keyword_low_precision:
		case TokenType::keyword_medium_precision:
		case TokenType::keyword_high_precision:
			retVal = parser->S_PrecisionQualifierToken(next);
			break;
		case TokenType::keyword_noperspective:
		case TokenType::keyword_smooth:
		case TokenType::keyword_flat:
			retVal = parser->S_InterpolationToken(next);
			break;
		case TokenType::keyword_invariant:
			retVal = parser->S_InvariantToken();
			break;
		case TokenType::keyword_layout:
			retVal = parser->S_LayoutToken();
			break;
		case TokenType::int_constant:
		case TokenType::float_constant:
		case TokenType::bool_constant:
			retVal = parser->S_LiteralToken(next);
			break;
		case TokenType::keyword_struct:
			retVal = parser->S_StructToken();
			break;
		case TokenType::equal:
		case TokenType::mul_assign:
		case TokenType::div_assign:
		case TokenType::mod_assign:
		case TokenType::add_assign:
		case TokenType::sub_assign:
		case TokenType::or_assign:
		case TokenType::and_assign:
		case TokenType::xor_assign:
		case TokenType::left_assign:
		case TokenType::right_assign:
			retVal = parser->S_AssignToken(next);
			break;	
		case TokenType::inc_op:
			retVal = parser->S_IncOP();
			break;
		case TokenType::dec_op:
			retVal = parser->S_DecOP();
			break;
		case TokenType::bang:
		case TokenType::plus:
		case TokenType::dash:
		case TokenType::tilde:
			retVal = parser->S_UnaryOperatorToken(next);
			break;
		case TokenType::semicolon:
			retVal = parser->S_Semicolon();
			break;
		case TokenType::left_paren:
			retVal = parser->S_LParen();
			break;
		case TokenType::left_brace:
			retVal = parser->S_LBrace();
			break;
		case TokenType::keyword_if:
			retVal = parser->S_IfToken();
			break;
		case TokenType::keyword_switch:
			retVal = parser->S_SwitchToken();
			break;
		case TokenType::keyword_case:
			retVal = parser->S_CaseToken();
			break;
		case TokenType::keyword_break:
			retVal = parser->S_BreakToken();
			break;
		case TokenType::keyword_default:
			retVal = parser->S_DefaultToken();
			break;
		case TokenType::keyword_continue:
			retVal = parser->S_ContinueToken();
			break;
		case TokenType::keyword_discard:
			retVal = parser->S_DiscardToken();
			break;
		case TokenType::keyword_return:
			retVal = parser->S_ReturnToken();
			break;
		case TokenType::keyword_while:
			retVal = parser->S_WhileToken();
			break;
		case TokenType::keyword_do:
			retVal = parser->S_DoToken();
			break;
		case TokenType::keyword_for:
			retVal = parser->S_ForToken();
			break;
		default:
			valid = false;
			break;
		}
	}



	return { retVal, valid };
}

HandlerReturn IStateHandler::DefaultExpressionGoto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal)
{
	parser->log.Debug(__FUNCTION__);

	ParserReturnValue retVal;
	bool valid = true;

	switch (nonTerminal->type)
	{
	case NonTerminalType::storage_qualifier:
		{
			auto temp = std::static_pointer_cast<StorageQualifier>(nonTerminal);
			retVal = parser->S_StorageQualifier(temp);
		}
		break;
	case NonTerminalType::layout_qualifier:
		{
			auto temp = std::static_pointer_cast<LayoutQualifier>(nonTerminal);
			retVal = parser->S_LayoutQualifier(temp);
		}
		break;
	case NonTerminalType::precision_qualifier:
		{
			auto temp = std::static_pointer_cast<PrecisionQualifier>(nonTerminal);
			retVal = parser->S_PrecisionQualifier(temp);
		}
		break;
	case NonTerminalType::interpolation_qualifier:
		{
			auto temp = std::static_pointer_cast<InterpolationQualifier>(nonTerminal);
			retVal = parser->S_InterpolationQualifier(temp);
		}
		break;
	case NonTerminalType::type_qualifier:
		{
			auto temp = std::static_pointer_cast<TypeQualifier>(nonTerminal);
			retVal = parser->S_TypeQualifier(temp);
		}
		break;
	case NonTerminalType::fully_specified_type:
		{
			auto temp = std::static_pointer_cast<FullySpecifiedType>(nonTerminal);
			retVal = parser->S_FullySpecifiedType(temp);
		}
		break;
	case NonTerminalType::struct_specifier:
		{
			std::shared_ptr<StructSpecifier> temp = std::static_pointer_cast<StructSpecifier>(nonTerminal);
			retVal = parser->S_StructSpecifier(temp);
		}
		break;
	case NonTerminalType::type_specifier_nonarray:
		{
			std::shared_ptr<TypeSpecifierNoArray> temp = std::static_pointer_cast<TypeSpecifierNoArray>(nonTerminal);
			retVal = parser->S_TypeSpecifierNonArray(temp);
		}
		break;
	case NonTerminalType::type_specifier_no_prec:
		{
			std::shared_ptr<TypeSpecifierNoPrec> temp = std::static_pointer_cast<TypeSpecifierNoPrec>(nonTerminal);
			retVal = parser->S_TypeSpecifierNoPrec(temp);
		}
		break;
	case NonTerminalType::type_specifier:
		{
			std::shared_ptr<TypeSpecifier> temp = std::static_pointer_cast<TypeSpecifier>(nonTerminal);
			retVal = parser->S_TypeSpecifier(temp);
		}
		break;
	case NonTerminalType::function_header:
		{
			std::shared_ptr<FunctionHeader> temp = std::static_pointer_cast<FunctionHeader>(nonTerminal);
			retVal = parser->S_FunctionHeader(temp);
		}
		break;
	case NonTerminalType::function_header_with_parameters:
		{
			std::shared_ptr<FunctionHeaderWithParams> temp = std::static_pointer_cast<FunctionHeaderWithParams>(nonTerminal);
			retVal = parser->S_FunctionHeaderWithParams(temp);
		}
		break;
	case NonTerminalType::function_declarator:
		{
			std::shared_ptr<FunctionDeclarator> temp = std::static_pointer_cast<FunctionDeclarator>(nonTerminal);
			retVal = parser->S_FunctionDeclarator(temp);
		}
		break;
	case NonTerminalType::function_prototype:
		{
			std::shared_ptr<FunctionPrototype> temp = std::static_pointer_cast<FunctionPrototype>(nonTerminal);
			retVal = parser->S_FunctionPrototype(temp);
		}
		break;
	case NonTerminalType::primary_expression:
		{
			std::shared_ptr<PrimaryExpression> temp = std::static_pointer_cast<PrimaryExpression>(nonTerminal);
			retVal = parser->S_PrimaryExpression(temp);
		}
		break;
	case NonTerminalType::postfix_expression:
		{
			std::shared_ptr<PostfixExpression> temp = std::static_pointer_cast<PostfixExpression>(nonTerminal);
			retVal = parser->S_PostfixExpression(temp);
		}
		break;
	case NonTerminalType::unary_operator:
		{
			std::shared_ptr<UnaryOperator> temp = std::static_pointer_cast<UnaryOperator>(nonTerminal);
			retVal = parser->S_UnaryOperator(temp);
		}
		break;
	case NonTerminalType::unary_expression:
		{
			std::shared_ptr<UnaryExpression> temp = std::static_pointer_cast<UnaryExpression>(nonTerminal);
			retVal = parser->S_UnaryExpression(temp);
		}
		break;
	case NonTerminalType::multiplicative_expression:
		{
			std::shared_ptr<MultiplicativeExpression> temp = std::static_pointer_cast<MultiplicativeExpression>(nonTerminal);
			retVal = parser->S_MultiplicativeExpression(temp);
		}
		break;
	case NonTerminalType::additive_expression:
		{
			std::shared_ptr<AdditiveExpression> temp = std::static_pointer_cast<AdditiveExpression>(nonTerminal);
			retVal = parser->S_AdditiveExpression(temp);
		}
		break;
	case NonTerminalType::shift_expression:
		{
			std::shared_ptr<ShiftExpression> temp = std::static_pointer_cast<ShiftExpression>(nonTerminal);
			retVal = parser->S_ShiftExpression(temp);
		}
		break;
	case NonTerminalType::relational_expression:
		{
			std::shared_ptr<RelationalExpression> temp = std::static_pointer_cast<RelationalExpression>(nonTerminal);
			retVal = parser->S_RelationalExpression(temp);
		}
		break;
	case NonTerminalType::equality_expression:
		{
			std::shared_ptr<EqualityExpression> temp = std::static_pointer_cast<EqualityExpression>(nonTerminal);
			retVal = parser->S_EqualityExpression(temp);
		}
		break;
	case NonTerminalType::and_expression:
		{
			std::shared_ptr<AndExpression> temp = std::static_pointer_cast<AndExpression>(nonTerminal);
			retVal = parser->S_AndExpression(temp);
		}
		break;
	case NonTerminalType::xor_expression:
		{
			std::shared_ptr<XorExpression> temp = std::static_pointer_cast<XorExpression>(nonTerminal);
			retVal = parser->S_XorExpression(temp);
		}
		break;
	case NonTerminalType::or_expression:
		{
			std::shared_ptr<OrExpression> temp = std::static_pointer_cast<OrExpression>(nonTerminal);
			retVal = parser->S_OrExpression(temp);
		}
		break;
	case NonTerminalType::logical_and_expression:
		{
			std::shared_ptr<LogicalAndExpression> temp = std::static_pointer_cast<LogicalAndExpression>(nonTerminal);
			retVal = parser->S_LogicalAndExpression(temp);
		}
		break;
	case NonTerminalType::logical_xor_expression:
		{
			std::shared_ptr<LogicalXorExpression> temp = std::static_pointer_cast<LogicalXorExpression>(nonTerminal);
			retVal = parser->S_LogicalXorExpression(temp);
		}
		break;
	case NonTerminalType::logical_or_expression:
		{
			std::shared_ptr<LogicalOrExpression> temp = std::static_pointer_cast<LogicalOrExpression>(nonTerminal);
			retVal = parser->S_LogicalOrExpression(temp);
		}
		break;
	case NonTerminalType::conditional_expression:
		{
			std::shared_ptr<ConditionalExpression> temp = std::static_pointer_cast<ConditionalExpression>(nonTerminal);
			retVal = parser->S_ConditionalExpression(temp);
		}
		break;
	case NonTerminalType::assignment_expression:
		{
			std::shared_ptr<AssignmentExpression> temp = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
			retVal = parser->S_AssignmentExpression(temp);
		}
		break;
	case NonTerminalType::expression:
		{
			std::shared_ptr<Expression> temp = std::static_pointer_cast<Expression>(nonTerminal);
			retVal = parser->S_Expression(temp);
		}
		break;
	case NonTerminalType::declaration:
		{
			std::shared_ptr<Declaration> temp = std::static_pointer_cast<Declaration>(nonTerminal);
			retVal = parser->S_Declaration(temp);
		}
		break;
	case NonTerminalType::declaration_statement:
		{
			std::shared_ptr<DeclarationStatement> temp = std::static_pointer_cast<DeclarationStatement>(nonTerminal);
			retVal = parser->S_DeclarationStatement(temp);
		}
		break;
	case NonTerminalType::expression_statement:
		{
			std::shared_ptr<ExpressionStatement> temp = std::static_pointer_cast<ExpressionStatement>(nonTerminal);
			retVal = parser->S_ExpressionStatement(temp);
		}
		break;
	case NonTerminalType::simple_statement:
		{
			std::shared_ptr<SimpleStatement> temp = std::static_pointer_cast<SimpleStatement>(nonTerminal);
			retVal = parser->S_SimpleStatement(temp);
		}
		break;
	case NonTerminalType::selection_statement:
		{
			std::shared_ptr<SelectionStatement> temp = std::static_pointer_cast<SelectionStatement>(nonTerminal);
			retVal = parser->S_SelectionStatement(temp);
		}
		break;
	case NonTerminalType::switch_statement:
		{
			std::shared_ptr<SwitchStatement> temp = std::static_pointer_cast<SwitchStatement>(nonTerminal);
			retVal = parser->S_SwitchStatement(temp);
		}
		break;
	case NonTerminalType::case_label:
		{
			std::shared_ptr<CaseLabel> temp = std::static_pointer_cast<CaseLabel>(nonTerminal);
			retVal = parser->S_CaseLabel(temp);
		}
		break;
	case NonTerminalType::jump_statement:
		{
			std::shared_ptr<JumpStatement> temp = std::static_pointer_cast<JumpStatement>(nonTerminal);
			retVal = parser->S_JumpStatement(temp);
		}
		break;
	case NonTerminalType::iteration_statement:
		{
			std::shared_ptr<IterationStatement> temp = std::static_pointer_cast<IterationStatement>(nonTerminal);
			retVal = parser->S_IterationStatement(temp);
		}
		break;
	case NonTerminalType::compound_statement:
		{
			std::shared_ptr<CompoundStatement> temp = std::static_pointer_cast<CompoundStatement>(nonTerminal);
			retVal = parser->S_CompoundStatement(temp);
		}
		break;
	case NonTerminalType::statement:
		{
			std::shared_ptr<Statement> temp = std::static_pointer_cast<Statement>(nonTerminal);
			retVal = parser->S_Statement(temp);
		}
		break;
	case NonTerminalType::statement_list:
		{
			std::shared_ptr<StatementList> temp = std::static_pointer_cast<StatementList>(nonTerminal);
			retVal = parser->S_StatementList(temp);
		}
		break;
	case NonTerminalType::function_identifier:
		{
			std::shared_ptr<FunctionIdentifier> temp = std::static_pointer_cast<FunctionIdentifier>(nonTerminal);
			retVal = parser->S_FunctionIdentifier(temp);
		}
		break;
	case NonTerminalType::function_call_header:
		{
			std::shared_ptr<FunctionCallHeader> temp = std::static_pointer_cast<FunctionCallHeader>(nonTerminal);
			retVal = parser->S_FunctionCallHeader(temp);
		}
		break;
	case NonTerminalType::function_call_header_no_parameters:
		{
			std::shared_ptr<FuncCallHeaderNoParams> temp = std::static_pointer_cast<FuncCallHeaderNoParams>(nonTerminal);
			retVal = parser->S_FunctionCallHeaderNoParams(temp);
		}
		break;
	case NonTerminalType::function_call_header_with_parameters:
		{
			std::shared_ptr<FuncCallHeaderParams> temp = std::static_pointer_cast<FuncCallHeaderParams>(nonTerminal);
			retVal = parser->S_FunctionCallHeaderWithParams(temp);
		}
		break;
	case NonTerminalType::function_call_generic:
		{
			std::shared_ptr<FunctionCallGeneric> temp = std::static_pointer_cast<FunctionCallGeneric>(nonTerminal);
			retVal = parser->S_FunctionCallGeneric(temp);
		}
		break;
	case NonTerminalType::function_call_or_method:
		{
			std::shared_ptr<FunctionCallOrMethod> temp = std::static_pointer_cast<FunctionCallOrMethod>(nonTerminal);
			retVal = parser->S_FunctionCallOrMethod(temp);
		}
		break;
	case NonTerminalType::function_call:
		{
			std::shared_ptr<FunctionCall> temp = std::static_pointer_cast<FunctionCall>(nonTerminal);
			retVal = parser->S_FunctionCall(temp);
		}
		break;
	case NonTerminalType::single_declaration:
		{
			std::shared_ptr<SingleDeclaration> temp = std::static_pointer_cast<SingleDeclaration>(nonTerminal);
			retVal = parser->S_SingleDeclaration(temp);
		}
		break;
	case NonTerminalType::init_declarator_list:
		{
			std::shared_ptr<InitDeclaratorList> temp = std::static_pointer_cast<InitDeclaratorList>(nonTerminal);
			retVal = parser->S_InitDeclaratorList(temp);
		}
		break;
	default:
		valid = false;
		break;
	}

	return { retVal, valid };
}