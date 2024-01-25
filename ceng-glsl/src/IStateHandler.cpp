#include "IStateHandler.h"

#include "GLSL_Parser.h"

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
		case TokenType::int_constant:
		case TokenType::float_constant:
		case TokenType::bool_constant:
			retVal = parser->S_LiteralToken(next);
			break;
		case TokenType::identifier:
			retVal = parser->S_IdentifierToken(next);
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
	default:
		valid = false;
		break;
	}

	return { retVal, valid };
}