#include "GLSL_Parser.h"

using namespace Ceng;

GLSL_Parser::GLSL_Parser()
{
}

void GLSL_Parser::Release()
{
	delete this;
}

const Log& GLSL_Parser::GetLog() const
{
	return log;
}

CRESULT GLSL_Parser::Parse(const std::vector<Token>& in_tokens, GLSL::AbstractSyntaxTree& output)
{
	log.Clear();
	log.FlushMode(true);

	tokens = in_tokens;

	tokenIter = tokens.begin();

	log.Debug("Parsing start");

	S_TranslationUnit();

	log.Debug("Parsing end");

	return CE_OK;
}

const Token& GLSL_Parser::PeekToken()
{
	Ceng::StringUtf8 text;
	text = "PeekToken = ";
	text += tokenIter->ToString();
	log.Debug(text);

	return *tokenIter;
}

const Token GLSL_Parser::NextToken()
{
	Ceng::StringUtf8 text;
	text = "NextToken = ";
	text += tokenIter->ToString();
	log.Debug(text);

	if (tokenIter->type == TokenType::meta_end_of_file)
	{
		return *tokenIter;
	}

	return (*tokenIter++);
}

void GLSL_Parser::DiscardNext()
{
	++tokenIter;
}

ParserReturnValue GLSL_Parser::StateFuncSkeleton(const char* callerName, IStateHandler& handler)
{
	log.Debug(callerName);

	HandlerReturn reductionVal = handler.Reduction(this);

	if (reductionVal.valid)
	{
		Ceng::StringUtf8 text;
		text = "reduction return: ";
		text += callerName;
		text += " , remaining count = ";
		text += reductionVal.retVal.backtrackCounter;
		log.Debug(text);
		return reductionVal.retVal;
	}

	do
	{
		bool earlyContinue = false;

		ParserReturnValue retVal;

		// TODO: reduction handler

		Token next = NextToken();

		if (next.type == TokenType::meta_end_of_file)
		{
			log.Debug("end of file reached");
			return ParserReturnValue();
		}

		auto shiftReturn = handler.Shift(this, next);

		if (!shiftReturn.valid)
		{
			log.Debug("No shift rule for returned non-terminal");
			continue;
		}

		retVal = shiftReturn.retVal;

		// Loop goto action until there is an action that must be handled
		// further down the call stack

		bool exit;

		do
		{
			exit = false;

			retVal.backtrackCounter--;

			if (retVal.backtrackCounter > 0)
			{
				// Reduction is handled further back in the state stack

				Ceng::StringUtf8 text;
				text = "backtrack pass: ";
				text += callerName;
				text += " , remaining count = ";
				text += retVal.backtrackCounter;
				log.Debug(text);

				return retVal;
			}

			Ceng::StringUtf8 text;
			text = "goto action: ";
			text += callerName;
			log.Debug(text);

			if (retVal.nonTerminal == nullptr)
			{
				// Received invalid nonterminal

				log.Debug("Received empty non-terminal");

				return retVal;
			}

			auto gotoRet = handler.Goto(this, retVal.nonTerminal);

			if (!gotoRet.valid)
			{
				Ceng::StringUtf8 text;
				text = "No goto rule for non-terminal: ";
				text += NonTerminalType::ToString(retVal.nonTerminal->type);
				log.Debug(text);
				return gotoRet.retVal;
			}

			retVal = gotoRet.retVal;

		} while (exit == false);

	} while (1);
}

class Handler_S_TranslationUnit : public IStateHandler
{
public:

public:

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		if (next.category == TokenCategory::data_type)
		{
			Ceng::StringUtf8 text;
			text = "no parsing rule for: ";
			text += next.ToString();
			parser->log.Debug(text);
			valid = false;
		}
		else
		{
			switch (next.type)
			{
			case TokenType::keyword_const:
			case TokenType::keyword_attribute:
			case TokenType::keyword_varying:
			case TokenType::keyword_uniform:
			case TokenType::keyword_in:
			case TokenType::keyword_out:
				retVal = parser->S_StorageQualifierToken(next.type);
				break;
			default:
				Ceng::StringUtf8 text;
				text = "no parsing rule for: ";
				text += next.ToString();
				parser->log.Debug(text);

				valid = false;
				break;
			}
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
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
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

};


ParserReturnValue GLSL_Parser::S_TranslationUnit()
{
	Handler_S_TranslationUnit temp;

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_StorageQualifierToken(TokenType::value value)
{
	log.Debug(__func__);

	return { std::make_shared<StorageQualifier>(value), 1 };
}

ParserReturnValue GLSL_Parser::S_StorageQualifier(std::shared_ptr<StorageQualifier>& sq)
{
	log.Debug(__func__);

	return { std::make_shared<TypeQualifier>(*sq), 1 };
}

class Handler_S_TypeQualifier : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier> sq;

public:

	Handler_S_TypeQualifier(std::shared_ptr<TypeQualifier>& sq)
		: sq(sq)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return {ParserReturnValue(),false};
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
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
			/*
			Ceng::StringUtf8 text;
			text = "no parsing rule for: ";
			text += next.ToString();
			LogError(text);
			*/
			valid = false;
		}
		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::type_specifier_nonarray:
			{
				auto temp = std::static_pointer_cast<TypeSpecifierNoArray>(nonTerminal);
				retVal = parser->S_TypeQualifier_TypeSpecifierNonArray(sq, temp);
			}
			break;
		case NonTerminalType::type_specifier_no_prec:
			{
				auto temp = std::static_pointer_cast<TypeSpecifierNoPrec>(nonTerminal);
				retVal = parser->S_TypeQualifier_TypeSpecifierNoPrec(sq, temp);
				break;
			}
		case NonTerminalType::type_specifier:
			{
				auto temp = std::static_pointer_cast<TypeSpecifier>(nonTerminal);
				retVal = parser->S_TypeQualifier_TypeSpecifier(sq, temp);
				break;
			}
		default:
			valid = false;
			break;
		}

		return { retVal,valid };
	}

};

ParserReturnValue GLSL_Parser::S_TypeQualifier(std::shared_ptr<TypeQualifier>& tq)
{
	Handler_S_TypeQualifier temp{ tq };

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_DatatypeToken(TokenType::value value)
{
	log.Debug(__func__);

	return { std::make_unique<TypeSpecifierNoArray>(value), 1 };
}

class Handler_S_TypeQualifier_TypeSpecifierNonArray : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& tq;
	std::shared_ptr<TypeSpecifierNoArray>& st;

public:

	Handler_S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& tq, 
		std::shared_ptr<TypeSpecifierNoArray>& st)
		: tq(tq),st(st)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (parser->PeekToken().type)
		{
		case TokenType::left_bracket:
			break;
		default:
			retVal = ParserReturnValue(std::make_shared<TypeSpecifierNoPrec>(*st), 1);
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& tq, 
	std::shared_ptr<TypeSpecifierNoArray>& ts)
{
	Handler_S_TypeQualifier_TypeSpecifierNonArray temp(tq,ts);

	return StateFuncSkeleton(__func__,temp);
}

class Handler_S_TypeQualifier_TypeSpecifierNoPrec : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier> tq;
	std::shared_ptr<TypeSpecifierNoPrec> ts;

public:

	Handler_S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, 
		std::shared_ptr<TypeSpecifierNoPrec>& ts)
		: tq(tq), ts(ts)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (parser->PeekToken().type)
		{
		default:
			retVal = ParserReturnValue(std::make_shared<TypeSpecifier>(*ts), 1);
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, 
	std::shared_ptr<TypeSpecifierNoPrec>& ts)
{
	Handler_S_TypeQualifier_TypeSpecifierNoPrec temp(tq, ts);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_TypeQualifier_TypeSpecifier : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& tq;
	std::shared_ptr<TypeSpecifier>& ts;

public:

	Handler_S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, 
		std::shared_ptr<TypeSpecifier>& ts)
		: tq(tq), ts(ts)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (parser->PeekToken().type)
		{
		default:
			retVal = ParserReturnValue(std::make_shared<FullySpecifiedType>(*tq, *ts), 2);
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifier>& ts)
{
	Handler_S_TypeQualifier_TypeSpecifier temp(tq, ts);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_FullySpecifiedType : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;

public:

	Handler_S_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& typeSpec)
		: typeSpec(typeSpec)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::identifier:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(*typeSpec),1),true };
		}		
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::identifier:
			retVal = parser->S_FullySpecifiedType_IdentifierToken(typeSpec,next);
			break;
		default:
			break;
		}

		return { ParserReturnValue(),false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& spec)
{
	Handler_S_FullySpecifiedType temp(spec);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;

public:

	Handler_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token)
		: typeSpec(typeSpec), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::left_bracket:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(*typeSpec),2),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::left_bracket:
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket(typeSpec, next);
			break;
		default:
			break;
		}

		return { ParserReturnValue(),false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken temp(spec,token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken_LBracket : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token)
		: typeSpec(typeSpec), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::right_bracket:
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(typeSpec, next);
			break;
		default:
			return DefaultExpressionShift(parser, next);
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
			break;
		}

		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket temp(spec, token);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<SingleDeclaration>(*spec, token.name), 4);
}

ParserReturnValue GLSL_Parser::S_LiteralToken(const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<PrimaryExpression>(token), 1);
}

ParserReturnValue GLSL_Parser::S_IdentifierToken(const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<PrimaryExpression>(token), 1);
}

ParserReturnValue GLSL_Parser::S_PrimaryExpression(std::shared_ptr<PrimaryExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<PostfixExpression>(ex), 1);
}

class Handler_PostfixExpression : public IStateHandler
{
public:
	std::shared_ptr<PostfixExpression>& ex;

public:

	Handler_PostfixExpression(std::shared_ptr<PostfixExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::inc_op:
		case TokenType::dec_op:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<UnaryExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::left_bracket:
			retVal = parser->S_PostfixExpression_LBracket(ex);
			break;
		case TokenType::dot:
			retVal = parser->S_PostfixExpression_Dot(ex);
			break;
		case TokenType::inc_op:
			retVal = parser->S_PostfixExpression_IncOp(ex);
			break;
		case TokenType::dec_op:
			retVal = parser->S_PostfixExpression_DecOp(ex);
			break;
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_PostfixExpression(std::shared_ptr<PostfixExpression>& ex)
{
	Handler_PostfixExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_IncOp(std::shared_ptr<PostfixExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<PostfixExpression>(ex,PostfixOperator::inc_op), 2);
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_DecOp(std::shared_ptr<PostfixExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue(std::make_shared<PostfixExpression>(ex, PostfixOperator::dec_op), 2);
}

class Handler_PostfixExpression_Dot : public IStateHandler
{
public:
	std::shared_ptr<PostfixExpression>& ex;

public:

	Handler_PostfixExpression_Dot(std::shared_ptr<PostfixExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::identifier:
			retVal = parser->S_PostfixExpression_Dot_IdToken(ex, next);
			break;
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_PostfixExpression_Dot(std::shared_ptr<PostfixExpression>& ex)
{
	Handler_PostfixExpression_Dot temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_Dot_IdToken(std::shared_ptr<PostfixExpression>& ex, const Token& token)
{
	log.Debug(__func__);

	return { std::make_shared<PostfixExpression>(ex,token.name),3 };
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_LBracket(std::shared_ptr<PostfixExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_LBracket_IntExpression(std::shared_ptr<PostfixExpression>& ex, std::shared_ptr<IntegerExpression>& intEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_LBracket_IntExpression_RBracket(std::shared_ptr<PostfixExpression>& ex, std::shared_ptr<IntegerExpression>& intEx)
{
	log.Debug(__func__);

	return { std::make_shared<PostfixExpression>(ex,intEx),4 };
}

ParserReturnValue GLSL_Parser::S_UnaryExpression(std::shared_ptr<UnaryExpression>& ex)
{
	log.Debug(__func__);

	return { std::make_shared<MultiplicativeExpression>(ex),1 };
}

ParserReturnValue GLSL_Parser::S_IncOP_UnaryExpression(std::shared_ptr<UnaryExpression>& ex)
{
	log.Debug(__func__);

	return { std::make_shared<UnaryExpression>(ex,PrefixOperator::inc_op),2 };
}

// DEC_OP unary_expression
ParserReturnValue GLSL_Parser::S_DecOP_UnaryExpression(std::shared_ptr<UnaryExpression>& ex)
{
	log.Debug(__func__);

	return { std::make_shared<UnaryExpression>(ex,PrefixOperator::dec_op),2 };
}

// unary_operator unary_expression
ParserReturnValue GLSL_Parser::S_UnaryOperator_UnaryExpression(std::shared_ptr<UnaryOperator>& op, std::shared_ptr<UnaryExpression>& ex)
{
	log.Debug(__func__);

	return { std::make_shared<UnaryExpression>(op,ex),2 };
}

class Handler_MultiplicativeExpression : public IStateHandler
{
public:
	std::shared_ptr<MultiplicativeExpression>& ex;

public:

	Handler_MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::star:
		case TokenType::slash:
		case TokenType::percent:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<AdditiveExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::star:
		case TokenType::slash:
		case TokenType::percent:
			retVal = parser->S_MultiplicativeExpression_MulToken(ex, next);
			break;
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& ex)
{
	Handler_MultiplicativeExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_MultiplicativeExpression_MulToken : public IStateHandler
{
public:
	std::shared_ptr<MultiplicativeExpression>& ex;
	const Token& token;

public:

	Handler_MultiplicativeExpression_MulToken(std::shared_ptr<MultiplicativeExpression>& ex, const Token& token)
		: ex(ex), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

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

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_MultiplicativeExpression_MulToken(std::shared_ptr<MultiplicativeExpression>& ex, const Token& token)
{
	Handler_MultiplicativeExpression_MulToken temp(ex,token);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_MultiplicativeExpression_MulToken_UnaryExpression(std::shared_ptr<MultiplicativeExpression>& mulEx, const Token& token,
	std::shared_ptr<UnaryExpression>& unaryEx)
{
	log.Debug(__func__);

	return { std::make_shared<MultiplicativeExpression>(mulEx,token,unaryEx),3 };
}

class Handler_AdditiveExpression : public IStateHandler
{
public:
	std::shared_ptr<AdditiveExpression>& ex;

public:

	Handler_AdditiveExpression(std::shared_ptr<AdditiveExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::plus:
		case TokenType::dash:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<ShiftExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::plus:
		case TokenType::dash:
			retVal = parser->S_AdditiveExpression_AddToken(ex, next);
			break;
		default:
			valid = false;
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		return { ParserReturnValue(),false };
	}

};


ParserReturnValue GLSL_Parser::S_AdditiveExpression(std::shared_ptr<AdditiveExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AdditiveExpression_AddToken(std::shared_ptr<AdditiveExpression>& ex, const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AdditiveExpression_AddToken_MultiplicativeEx(std::shared_ptr<AdditiveExpression>& addEx, const Token& token,
	std::shared_ptr<MultiplicativeExpression>& mulEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ShiftExpression(std::shared_ptr<ShiftExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ShiftExpression_ShiftToken(std::shared_ptr<ShiftExpression>& ex, const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue();
}


ParserReturnValue GLSL_Parser::S_ShiftExpression_ShiftToken_AdditiveEx(std::shared_ptr<ShiftExpression>& shiftEx, const Token& token,
	std::shared_ptr<AdditiveExpression>& addEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_RelationalExpression(std::shared_ptr<RelationalExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_RelationalExpression_RelationalToken(std::shared_ptr<RelationalExpression>& ex, const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_RelationalExpression_RelationalToken_ShiftEx(std::shared_ptr<RelationalExpression>& relativeEx, const Token& token,
	std::shared_ptr<ShiftExpression>& shiftEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_EqualityExpression(std::shared_ptr<EqualityExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_EqualityExpression_EqualityToken(std::shared_ptr<EqualityExpression>& ex, const Token& token)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_EqualityExpression_EqualityToken_RelativeEx(std::shared_ptr<EqualityExpression>& equalityEx, const Token& token,
	std::shared_ptr<RelationalExpression>& relativeEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AndExpression(std::shared_ptr<AndExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AndExpression_Ampersand(std::shared_ptr<AndExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AndExpression_Ampersand_RelativeEx(std::shared_ptr<AndExpression>& andEx,
	std::shared_ptr<EqualityExpression>& equalityEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_XorExpression(std::shared_ptr<XorExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_XorExpression_Caret(std::shared_ptr<XorExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_XorExpression_Caret_AndEx(std::shared_ptr<XorExpression>& xorEx,
	std::shared_ptr<AndExpression>& andEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_OrExpression(std::shared_ptr<OrExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_OrExpression_Vbar(std::shared_ptr<OrExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_OrExpression_Vbar_XorEx(std::shared_ptr<OrExpression>& orEx,
	std::shared_ptr<XorExpression>& xorEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalAndExpression_AndOp(std::shared_ptr<LogicalAndExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalAndExpression_AndOp_OrEx(std::shared_ptr<LogicalAndExpression>& logicAndEx,
	std::shared_ptr<OrExpression>& orEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalXorExpression_XorOp(std::shared_ptr<LogicalXorExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalXorExpression_XorOp_OrEx(std::shared_ptr<LogicalXorExpression>& logicXorEx,
	std::shared_ptr<LogicalAndExpression>& logicAndEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalOrExpression_OrOp(std::shared_ptr<LogicalOrExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_LogicalOrExpression_OrOp_OrEx(std::shared_ptr<LogicalOrExpression>& logicOrEx,
	std::shared_ptr<LogicalXorExpression>& logicXorEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ConditionalExpression(std::shared_ptr<ConditionalExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CondExpression_Question(std::shared_ptr<ConditionalExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CondExpression_Question_Expression(std::shared_ptr<ConditionalExpression>& condEx,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CondExpression_Question_Expression_Colon(std::shared_ptr<ConditionalExpression>& condEx,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CondExpression_Question_Expression_Colon_AssignEx(std::shared_ptr<ConditionalExpression>& condEx,
	std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_AssignmentExpression(std::shared_ptr<AssignmentExpression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Expression(std::shared_ptr<Expression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Expression_Comma(std::shared_ptr<Expression>& ex)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Expression_Comma_AssignmentExpression(std::shared_ptr<Expression>& expression,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}