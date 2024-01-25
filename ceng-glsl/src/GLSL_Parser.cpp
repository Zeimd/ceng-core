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

		Ceng::StringUtf8 text;
		text = "shift action: ";
		text += callerName;
		log.Debug(text);

		auto shiftReturn = handler.Shift(this, next);

		if (!shiftReturn.valid)
		{
			Ceng::StringUtf8 text;
			text = "No shift rule for token: ";
			text += next.ToString();
			log.Error(text);
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
				log.Error(text);
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
			retVal = ParserReturnValue(std::make_shared<TypeSpecifierNoPrec>(st), 1);
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

class Handler_TypeSpecifierNonArray : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifierNoArray>& typeSpec;

public:

	Handler_TypeSpecifierNonArray(std::shared_ptr<TypeSpecifierNoArray>& typeSpec)
		: typeSpec(typeSpec)
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
			valid = false;
			break;
		default:
			retVal = ParserReturnValue(std::make_shared<TypeSpecifierNoPrec>(typeSpec), 1);
			break;
		}

		return { retVal, valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::left_bracket:
			retVal = parser->S_TypeSpecifierNonArray_LBracket(typeSpec);
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

ParserReturnValue GLSL_Parser::S_TypeSpecifierNonArray(std::shared_ptr<TypeSpecifierNoArray>& ts)
{
	Handler_TypeSpecifierNonArray temp(ts);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_TypeSpecifierNonArray_LBracket : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifierNoArray>& typeSpec;

public:

	Handler_TypeSpecifierNonArray_LBracket(std::shared_ptr<TypeSpecifierNoArray>& typeSpec)
		: typeSpec(typeSpec)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::right_bracket:
			retVal = parser->S_TypeSpecifierNonArray_LBracket_RBracket(typeSpec);
		default:
			return DefaultExpressionShift(parser, next);
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (nonTerminal->type)
		{
		case NonTerminalType::expression:
			{
				std::shared_ptr<Expression> temp = std::static_pointer_cast<Expression>(nonTerminal);
				return { parser->S_TypeSpecifierNonArray_LBracket_Expression(typeSpec, temp),true };
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
	}

};

ParserReturnValue GLSL_Parser::S_TypeSpecifierNonArray_LBracket(std::shared_ptr<TypeSpecifierNoArray>& ts)
{
	Handler_TypeSpecifierNonArray_LBracket temp(ts);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_TypeSpecifierNonArray_LBracket_Expression : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifierNoArray>& typeSpec;
	std::shared_ptr<Expression>& expression;

public:

	Handler_TypeSpecifierNonArray_LBracket_Expression(std::shared_ptr<TypeSpecifierNoArray>& typeSpec,
		std::shared_ptr<Expression>& expression)
		: typeSpec(typeSpec),expression(expression)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::right_bracket:
			retVal = parser->S_TypeSpecifierNonArray_LBracket_Expression_RBracket(typeSpec, expression);
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
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_TypeSpecifierNonArray_LBracket_Expression(std::shared_ptr<TypeSpecifierNoArray>& ts,
	std::shared_ptr<Expression>& expression)
{
	Handler_TypeSpecifierNonArray_LBracket_Expression temp(ts,expression);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_TypeSpecifierNonArray_LBracket_Expression_RBracket(std::shared_ptr<TypeSpecifierNoArray>& ts,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return { std::make_shared<TypeSpecifierNoPrec>(ts,expression),4 };
}

ParserReturnValue GLSL_Parser::S_TypeSpecifierNonArray_LBracket_RBracket(std::shared_ptr<TypeSpecifierNoArray>& ts)
{
	log.Debug(__func__);
	return { std::make_shared<TypeSpecifierNoPrec>(ts),3 };
}

class Handler_TypeSpecifierNoPrec : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifierNoPrec> ts;

public:

	Handler_TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoPrec>& ts)
		: ts(ts)
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

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		default:
			valid = false;
		}

		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoPrec>& ts)
{
	Handler_TypeSpecifierNoPrec temp(ts);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_S_TypeSpecifier : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifier> typeSpec;

public:

	Handler_S_TypeSpecifier(std::shared_ptr<TypeSpecifier>& typeSpec)
		: typeSpec(typeSpec)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (parser->PeekToken().type)
		{
		case TokenType::left_paren:
			retVal = ParserReturnValue(std::make_shared<FunctionIdentifier>(typeSpec), 1);
			break;
		default:
			valid = false;
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


ParserReturnValue GLSL_Parser::S_TypeSpecifier(std::shared_ptr<TypeSpecifier>& ts)
{
	Handler_S_TypeSpecifier temp(ts);

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
		case TokenType::left_paren:
			break;
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
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec),1),true };
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
			valid = false;
			break;
		}

		return { retVal,valid };
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
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec),2),true };
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
		case NonTerminalType::expression:
			{
				std::shared_ptr<Expression> temp = std::static_pointer_cast<Expression>(nonTerminal);
				retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_Expression(typeSpec, token, temp);
			}
			break;
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

class Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token,
		std::shared_ptr<Expression>& expression)
		: typeSpec(typeSpec), token(token), expression(expression)
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
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket(typeSpec, token, expression);
			break;
		default:
			valid = false;
		}

		
		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_Expression(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression temp(spec, token, expression);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token,
		std::shared_ptr<Expression>& expression)
		: typeSpec(typeSpec), token(token), expression(expression)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::equal:
			break;
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec,token.name,expression), 5), true};
		}

		return { ParserReturnValue(), false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::equal:
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal(typeSpec, token, expression);
			break;
		default:
			valid = false;
		}


		return { retVal, valid };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket temp(spec, token, expression);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token,
		std::shared_ptr<Expression>& expression)
		: typeSpec(typeSpec), token(token), expression(expression)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::assignment_expression:
			{
				std::shared_ptr<AssignmentExpression> temp = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
				retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_AssignEx(typeSpec, token, expression, temp);
			}
			break;
		case NonTerminalType::initializer:
			{
				std::shared_ptr<Initializer> temp = std::static_pointer_cast<Initializer>(nonTerminal);
				retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_Initializer(typeSpec, token, expression, temp);
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal temp(spec, token, expression);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	return { std::make_shared<Initializer>(assignEx),1 };
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_Expression_RBracket_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Expression>& expression, std::shared_ptr<Initializer>& initializer)
{
	log.Debug(__func__);
	return { std::make_shared<SingleDeclaration>(spec,token.name,expression,initializer),7 };
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	log.Debug(__func__);

	return { std::make_shared<SingleDeclaration>(spec, token.name), 4 };
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
		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::function_identifier:
			{
				std::shared_ptr<FunctionIdentifier> temp = std::static_pointer_cast<FunctionIdentifier>(nonTerminal);
				retVal = parser->S_FunctionIdentifier(temp);
			}
			break;
		default:
			valid = false;
			break;
		}

		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_PostfixExpression_Dot(std::shared_ptr<PostfixExpression>& ex)
{
	Handler_PostfixExpression_Dot temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_PostfixExpression_Dot_FunctionCallGeneric(std::shared_ptr<PostfixExpression>& ex,
	std::shared_ptr<FunctionCallGeneric>& funcCall)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCallOrMethod>(ex,funcCall),3 };
}

class Handler_PostfixExpression_Dot_IdToken : public IStateHandler
{
public:
	std::shared_ptr<PostfixExpression>& ex;
	const Token& token;

public:

	Handler_PostfixExpression_Dot_IdToken(std::shared_ptr<PostfixExpression>& ex, const Token& token)
		: ex(ex), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::left_paren:
			return { ParserReturnValue(std::make_shared<FunctionIdentifier>(token.name),1), true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		return { ParserReturnValue(),false };
	}

};

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
		default:
			return DefaultExpressionShift(parser, next);
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
	Handler_AdditiveExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_ShiftExpression : public IStateHandler
{
public:
	std::shared_ptr<ShiftExpression>& ex;

public:

	Handler_ShiftExpression(std::shared_ptr<ShiftExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::left_op:
		case TokenType::right_op:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<RelationalExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::left_op:
		case TokenType::right_op:
			retVal = parser->S_ShiftExpression_ShiftToken(ex, next);
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

ParserReturnValue GLSL_Parser::S_ShiftExpression(std::shared_ptr<ShiftExpression>& ex)
{
	Handler_ShiftExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_RelationalExpression : public IStateHandler
{
public:
	std::shared_ptr<RelationalExpression>& ex;

public:

	Handler_RelationalExpression(std::shared_ptr<RelationalExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::left_angle:
		case TokenType::right_angle:
		case TokenType::le_op:
		case TokenType::ge_op:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<EqualityExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::left_angle:
		case TokenType::right_angle:
		case TokenType::le_op:
		case TokenType::ge_op:
			retVal = parser->S_RelationalExpression_RelationalToken(ex, next);
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


ParserReturnValue GLSL_Parser::S_RelationalExpression(std::shared_ptr<RelationalExpression>& ex)
{
	Handler_RelationalExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_EqualityExpression : public IStateHandler
{
public:
	std::shared_ptr<EqualityExpression>& ex;

public:

	Handler_EqualityExpression(std::shared_ptr<EqualityExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::eq_op:
		case TokenType::ne_op:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<AndExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::eq_op:
		case TokenType::ne_op:
			retVal = parser->S_EqualityExpression_EqualityToken(ex, next);
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

ParserReturnValue GLSL_Parser::S_EqualityExpression(std::shared_ptr<EqualityExpression>& ex)
{
	Handler_EqualityExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_AndExpression : public IStateHandler
{
public:
	std::shared_ptr<AndExpression>& ex;

public:

	Handler_AndExpression(std::shared_ptr<AndExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::ampersand:
		default:
			return { ParserReturnValue(std::make_shared<XorExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::ampersand:
			retVal = parser->S_AndExpression_Ampersand(ex);
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

ParserReturnValue GLSL_Parser::S_AndExpression(std::shared_ptr<AndExpression>& ex)
{
	Handler_AndExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_XorExpression : public IStateHandler
{
public:
	std::shared_ptr<XorExpression>& ex;

public:

	Handler_XorExpression(std::shared_ptr<XorExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::caret:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<OrExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::caret:
			retVal = parser->S_XorExpression_Caret(ex);
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

ParserReturnValue GLSL_Parser::S_XorExpression(std::shared_ptr<XorExpression>& ex)
{
	Handler_XorExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_OrExpression : public IStateHandler
{
public:
	std::shared_ptr<OrExpression>& ex;

public:

	Handler_OrExpression(std::shared_ptr<OrExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::vertical_bar:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<LogicalAndExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::vertical_bar:
			retVal = parser->S_OrExpression_Vbar(ex);
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


ParserReturnValue GLSL_Parser::S_OrExpression(std::shared_ptr<OrExpression>& ex)
{
	Handler_OrExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_LogicalAndExpression : public IStateHandler
{
public:
	std::shared_ptr<LogicalAndExpression>& ex;

public:

	Handler_LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::and_op:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<LogicalXorExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::and_op:
			retVal = parser->S_LogicalAndExpression_AndOp(ex);
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

ParserReturnValue GLSL_Parser::S_LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& ex)
{
	Handler_LogicalAndExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_LogicalXorExpression : public IStateHandler
{
public:
	std::shared_ptr<LogicalXorExpression>& ex;

public:

	Handler_LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::xor_op:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<LogicalOrExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::and_op:
			retVal = parser->S_LogicalXorExpression_XorOp(ex);
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

ParserReturnValue GLSL_Parser::S_LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& ex)
{
	Handler_LogicalXorExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_LogicalOrExpression : public IStateHandler
{
public:
	std::shared_ptr<LogicalOrExpression>& ex;

public:

	Handler_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::or_op:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<ConditionalExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::or_op:
			retVal = parser->S_LogicalOrExpression_OrOp(ex);
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

ParserReturnValue GLSL_Parser::S_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& ex)
{
	Handler_LogicalOrExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

class Handler_ConditionalExpression : public IStateHandler
{
public:
	std::shared_ptr<ConditionalExpression>& ex;

public:

	Handler_ConditionalExpression(std::shared_ptr<ConditionalExpression>& ex)
		: ex(ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::question:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<AssignmentExpression>(ex),1),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::question:
			retVal = parser->S_CondExpression_Question(ex);
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

ParserReturnValue GLSL_Parser::S_ConditionalExpression(std::shared_ptr<ConditionalExpression>& ex)
{
	Handler_ConditionalExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
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

	return { std::make_shared<Expression>(ex),1 };
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

ParserReturnValue GLSL_Parser::S_FunctionIdentifier(std::shared_ptr<FunctionIdentifier>& funcId)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

// Reduction: function_identifier LPAREN
ParserReturnValue GLSL_Parser::S_FunctionIdentifier_Lparen(std::shared_ptr<FunctionIdentifier>& funcId)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeader(std::shared_ptr<FunctionCallHeader>& funcHeader)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeader_VoidToken(std::shared_ptr<FunctionCallHeader>& funcHeader)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderNoParams(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

// Reduction: function_call_header_no_params RIGHT_PAREN
ParserReturnValue GLSL_Parser::S_FunctionCallHeaderNoParams_RParen(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeader_AssignEx(std::shared_ptr<FunctionCallHeader>& funcHeader,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

// Reduction: function_call_header_with_params RIGHT_PAREN
ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_RParen(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_Comma(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_Comma_AssignEx(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallGeneric(std::shared_ptr<FunctionCallGeneric>& funcCall)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCallOrMethod(std::shared_ptr<FunctionCallOrMethod>& funcCall)
{
	log.Debug(__func__);

	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_FunctionCall(std::shared_ptr<FunctionCall>& funcCall)
{
	log.Debug(__func__);

	return ParserReturnValue();
}