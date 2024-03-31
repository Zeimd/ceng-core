#include "GLSL_Parser.h"

#include "TranslationUnit.h"

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

	ParserReturnValue retVal = S_TranslationUnit();

	log.Debug("Parsing end");

	log.Debug("****************************************************************************");
	log.Debug("Roundtrip print:");

	Ceng::StringUtf8 text = retVal.nonTerminal->ToString();
	log.Debug(text);

	log.Debug("****************************************************************************");

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
				return retVal;
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

		return DefaultExpressionShift(parser, next);
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (nonTerminal->type)
		{
		case NonTerminalType::declaration:
		case NonTerminalType::function_definition:
			return { ParserReturnValue(), false };
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
	}

};


ParserReturnValue GLSL_Parser::S_TranslationUnit()
{
	log.Debug(__func__);

	Handler_S_TranslationUnit temp;

	ParserReturnValue retVal;

	std::shared_ptr<TranslationUnit> translationUnit = std::make_shared<TranslationUnit>();;

	do
	{
		retVal = StateFuncSkeleton(__func__, temp);

		log.Debug("Returned to S_TranslationUnit");

		/*
		Ceng::StringUtf8 text;
		text = "nonTerminal: ";
		text += retVal.nonTerminal;
		log.Debug(text);
		*/

		if (retVal.nonTerminal == nullptr)
		{
			break;
		}

		Ceng::StringUtf8 text = "nonTerminal type: ";
		text += NonTerminalType::ToString(retVal.nonTerminal->type);
		log.Debug(text);

		switch (retVal.nonTerminal->type)
		{
		case NonTerminalType::declaration:
		case NonTerminalType::function_definition:
			translationUnit->Append(retVal.nonTerminal);
			break;
		default:
			break;
		}

	} while (1);

	return { translationUnit,0 };
}

class Handler_S_StructToken : public IStateHandler
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

		switch (next.type)
		{
		case TokenType::left_brace:
			return { parser->S_StructToken_LBrace(), true };
		case TokenType::identifier:
			return { parser->S_StructToken_IdentifierToken(next), true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_StructToken()
{
	Handler_S_StructToken temp;

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructToken_LBrace : public IStateHandler
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

		switch (next.type)
		{
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_StructToken_LBrace()
{
	Handler_S_StructToken_LBrace temp;

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructToken_IdentifierToken : public IStateHandler
{
public:
	const Token& id;


public:

	Handler_S_StructToken_IdentifierToken(const Token& _id)
		: id(_id)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::left_brace:
			return { parser->S_StructToken_IdentifierToken_LBrace(id), true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken(const Token& structName)
{
	Handler_S_StructToken_IdentifierToken temp(structName);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructToken_IdentifierToken_LBrace : public IStateHandler
{
public:
	const Token& id;


public:

	Handler_S_StructToken_IdentifierToken_LBrace(const Token& _id)
		: id(_id)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

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
		case NonTerminalType::type_qualifier:
			{
				std::shared_ptr<TypeQualifier> typeQ = std::static_pointer_cast<TypeQualifier>(nonTerminal);
				retVal = parser->S_StructHeader_TypeQualifier(typeQ);
			}
			break;
		case NonTerminalType::type_specifier:
			{
				std::shared_ptr<TypeSpecifier> typeSpec = std::static_pointer_cast<TypeSpecifier>(nonTerminal);
				retVal = parser->S_StructHeader_TypeSpecifier(typeSpec);
			}
			break;
		case NonTerminalType::struct_declaration:
			{
				std::shared_ptr<StructDeclaration> decl = std::static_pointer_cast<StructDeclaration>(nonTerminal);
				retVal = parser->S_StructToken_IdentifierToken_LBrace_StructDeclaration(id, decl);
			}
			break;
		case NonTerminalType::struct_declaration_list:
			{
				std::shared_ptr<StructDeclarationList> list = std::static_pointer_cast<StructDeclarationList>(nonTerminal);
				retVal = parser->S_StructToken_IdentifierToken_LBrace_StructDeclarationList(id, list);
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken_LBrace(const Token& structName)
{
	Handler_S_StructToken_IdentifierToken_LBrace temp(structName);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructHeader_TypeQualifier : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& typeQ;


public:

	Handler_S_StructHeader_TypeQualifier(std::shared_ptr<TypeQualifier>& _typeQ)
		: typeQ(_typeQ)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

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
		case NonTerminalType::type_specifier:
		{
			std::shared_ptr<TypeSpecifier> typeSpec = std::static_pointer_cast<TypeSpecifier>(nonTerminal);
			retVal = parser->S_StructHeader_TypeQualifier_TypeSpecifier(typeQ,typeSpec);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier(std::shared_ptr<TypeQualifier>& typeQ)
{
	Handler_S_StructHeader_TypeQualifier temp(typeQ);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructHeader_TypeQualifier_TypeSpecifier : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& typeQ;
	std::shared_ptr<TypeSpecifier>& typeSpec;


public:

	Handler_S_StructHeader_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& _typeQ,
		std::shared_ptr<TypeSpecifier>& _typeSpec)
		: typeQ(_typeQ),typeSpec(_typeSpec)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_StructDecl_IdentifierToken(next),true };
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
		case NonTerminalType::struct_declarator:
			{
				std::shared_ptr<StructDeclarator> decl = std::static_pointer_cast<StructDeclarator>(nonTerminal);
				retVal = parser->S_StructDecl_StructDeclarator(decl);
			}
			break;
		case NonTerminalType::struct_declarator_list:
			{
				std::shared_ptr<StructDeclaratorList> decl = std::static_pointer_cast<StructDeclaratorList>(nonTerminal);
				retVal = parser->S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList(typeQ, typeSpec, decl);
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& typeQ, std::shared_ptr<TypeSpecifier>& typeSpec)
{
	Handler_S_StructHeader_TypeQualifier_TypeSpecifier temp(typeQ, typeSpec);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_StructDecl_StructDeclarator(std::shared_ptr<StructDeclarator>& decl)
{
	log.Debug(__func__);
	return { std::make_shared<StructDeclaratorList>(decl),1 };
}

class Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& typeQ;
	std::shared_ptr<TypeSpecifier>& typeSpec;
	std::shared_ptr<StructDeclaratorList>& list;


public:

	Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList(std::shared_ptr<TypeQualifier>& _typeQ,
		std::shared_ptr<TypeSpecifier>& _typeSpec, std::shared_ptr<StructDeclaratorList>& _list)
		: typeQ(_typeQ), typeSpec(_typeSpec),list(_list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::comma:
			return { parser->S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma(typeQ,typeSpec,list),true };
		case TokenType::semicolon:
			return { parser->S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Semicolon(typeQ,typeSpec,list),true };
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
		case NonTerminalType::struct_declarator:
		{
			std::shared_ptr<StructDeclarator> decl = std::static_pointer_cast<StructDeclarator>(nonTerminal);
			retVal = parser->S_StructDecl_StructDeclarator(decl);
		}
		break;
		case NonTerminalType::struct_declarator_list:
		{
			std::shared_ptr<StructDeclaratorList> decl = std::static_pointer_cast<StructDeclaratorList>(nonTerminal);
			retVal = parser->S_StructHeader_TypeSpecifier_StructDeclaratorList(typeSpec, decl);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList(std::shared_ptr<TypeQualifier>& typeQ,
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
{
	Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList temp(typeQ, typeSpec, list);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma : public IStateHandler
{
public:
	std::shared_ptr<TypeQualifier>& typeQ;
	std::shared_ptr<TypeSpecifier>& typeSpec;
	std::shared_ptr<StructDeclaratorList>& list;

public:

	Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeQualifier>& _typeQ,
		std::shared_ptr<TypeSpecifier>& _typeSpec,
		std::shared_ptr<StructDeclaratorList>& _list)
		: typeQ(_typeQ),typeSpec(_typeSpec), list(_list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_StructDecl_IdentifierToken(next),true };
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
		case NonTerminalType::struct_declarator:
		{
			std::shared_ptr<StructDeclarator> decl = std::static_pointer_cast<StructDeclarator>(nonTerminal);
			retVal = parser->S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(typeQ,typeSpec, list, decl);
		}
		break;
		case NonTerminalType::struct_declarator_list:
		{
			std::shared_ptr<StructDeclaratorList> decl = std::static_pointer_cast<StructDeclaratorList>(nonTerminal);
			retVal = parser->S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList(typeQ,typeSpec, decl);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};


ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeQualifier>& typeQ,
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
{
	Handler_S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma temp(typeQ, typeSpec, list);

	return StateFuncSkeleton(__func__, temp);
}

// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(std::shared_ptr<TypeQualifier>& typeQ,
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list, std::shared_ptr<StructDeclarator>& decl)
{
	log.Debug(__func__);

	list->Append(decl);

	return { list,3 };
}

ParserReturnValue GLSL_Parser::S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Semicolon(std::shared_ptr<TypeQualifier>& typeQ,
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
{
	log.Debug(__func__);
	return { std::make_shared<StructDeclaration>(*typeQ,*typeSpec,list),4 };
}

class Handler_S_StructHeader_TypeSpecifier : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifier>& typeSpec;


public:

	Handler_S_StructHeader_TypeSpecifier(std::shared_ptr<TypeSpecifier>& _typeSpec)
		: typeSpec(_typeSpec)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_StructDecl_IdentifierToken(next),true };
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
		case NonTerminalType::struct_declarator:
		{
			std::shared_ptr<StructDeclarator> decl = std::static_pointer_cast<StructDeclarator>(nonTerminal);
			retVal = parser->S_StructDecl_StructDeclarator(decl);
		}
		break;
		case NonTerminalType::struct_declarator_list:
		{
			std::shared_ptr<StructDeclaratorList> decl = std::static_pointer_cast<StructDeclaratorList>(nonTerminal);
			retVal = parser->S_StructHeader_TypeSpecifier_StructDeclaratorList(typeSpec, decl);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeSpecifier(std::shared_ptr<TypeSpecifier>& typeSpec)
{
	Handler_S_StructHeader_TypeSpecifier temp(typeSpec);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifier>& typeSpec;
	std::shared_ptr<StructDeclaratorList>& list;


public:

	Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList(std::shared_ptr<TypeSpecifier>& _typeSpec, 
		std::shared_ptr<StructDeclaratorList>& _list)
		: typeSpec(_typeSpec), list(_list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::comma:
			return { parser->S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma(typeSpec,list),true };
		case TokenType::semicolon:
			return { parser->S_StructHeader_TypeSpecifier_StructDeclaratorList_Semicolon(typeSpec,list),true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeSpecifier_StructDeclaratorList(
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
{
	Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList temp(typeSpec, list);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma : public IStateHandler
{
public:
	std::shared_ptr<TypeSpecifier>& typeSpec;
	std::shared_ptr<StructDeclaratorList>& list;

public:

	Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeSpecifier>& _typeSpec,
		std::shared_ptr<StructDeclaratorList>& _list)
		: typeSpec(_typeSpec),list(_list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_StructDecl_IdentifierToken(next),true };
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
		case NonTerminalType::struct_declarator:
		{
			std::shared_ptr<StructDeclarator> decl = std::static_pointer_cast<StructDeclarator>(nonTerminal);
			retVal = parser->S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(typeSpec,list,decl);
		}
		break;
		case NonTerminalType::struct_declarator_list:
		{
			std::shared_ptr<StructDeclaratorList> decl = std::static_pointer_cast<StructDeclaratorList>(nonTerminal);
			retVal = parser->S_StructHeader_TypeSpecifier_StructDeclaratorList(typeSpec, decl);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeSpecifier>& typeSpec,
	std::shared_ptr<StructDeclaratorList>& list)
{
	Handler_S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma temp(typeSpec, list);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec,
	std::shared_ptr<StructDeclaratorList>& list, std::shared_ptr<StructDeclarator>& decl)
{
	log.Debug(__func__);

	list->Append(decl);

	return { list,3 };
}

ParserReturnValue GLSL_Parser::S_StructHeader_TypeSpecifier_StructDeclaratorList_Semicolon(
	std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
{
	log.Debug(__func__);
	return { std::make_shared<StructDeclaration>(*typeSpec,list),3 };
}


class Handler_S_StructDecl_IdentifierToken : public IStateHandler
{
public:
	const Token& id;

public:

	Handler_S_StructDecl_IdentifierToken(const Token& _id)
		: id(_id)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::semicolon:
		case TokenType::comma:
			return { ParserReturnValue(std::make_shared<StructDeclarator>(id.name),1),true };
		default:
			break;
		}

		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::left_bracket:
			return { parser->S_StructDecl_IdentifierToken_LBracket(id),true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_StructDecl_IdentifierToken(const Token& id)
{
	Handler_S_StructDecl_IdentifierToken temp(id);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_StructDecl_IdentifierToken_LBracket : public IStateHandler
{
public:
	const Token& id;

public:

	Handler_S_StructDecl_IdentifierToken_LBracket(const Token& _id)
		: id(_id)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::right_bracket:
			return { parser->S_StructDecl_IdentifierToken_LBracket_RBracket(id),true };
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
		case NonTerminalType::expression:
		{
			std::shared_ptr<Expression> expr = std::static_pointer_cast<Expression>(nonTerminal);
			retVal = parser->S_StructDecl_IdentifierToken_LBracket_Expression(id, expr);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructDecl_IdentifierToken_LBracket(const Token& id)
{
	Handler_S_StructDecl_IdentifierToken_LBracket temp(id);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_StructDecl_IdentifierToken_LBracket_RBracket(const Token& id)
{
	log.Debug(__func__);
	return { std::make_shared<StructDeclarator>(id.name,true), 3 };
}

class Handler_S_StructDecl_IdentifierToken_LBracket_Expression : public IStateHandler
{
public:
	const Token& id;
	std::shared_ptr<Expression>& arraySize;

public:

	Handler_S_StructDecl_IdentifierToken_LBracket_Expression(const Token& _id,
		std::shared_ptr<Expression>& _arraySize)
		: id(_id),arraySize(_arraySize)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::right_bracket:
			return { parser->S_StructDecl_IdentifierToken_LBracket_Expression_RBracket(id,arraySize),true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_StructDecl_IdentifierToken_LBracket_Expression(const Token& id, std::shared_ptr<Expression>& arraySize)
{
	Handler_S_StructDecl_IdentifierToken_LBracket_Expression temp(id,arraySize);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_StructDecl_IdentifierToken_LBracket_Expression_RBracket(const Token& id, std::shared_ptr<Expression>& arraySize)
{
	log.Debug(__func__);
	return { std::make_shared<StructDeclarator>(id.name,arraySize),4 };
}

ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken_LBrace_StructDeclaration(const Token& structName, std::shared_ptr<StructDeclaration>& decl)
{
	log.Debug(__func__);
	return ParserReturnValue(std::make_shared<StructDeclarationList>(decl),1);
}

class Handler_S_StructToken_IdentifierToken_LBrace_StructDeclarationList : public IStateHandler
{
public:
	const Token& id;
	std::shared_ptr<StructDeclarationList>& list;

public:

	Handler_S_StructToken_IdentifierToken_LBrace_StructDeclarationList(const Token& _id,
		std::shared_ptr<StructDeclarationList>& _list)
		: id(_id),list(_list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::right_brace:
			return { parser->S_StructToken_IdentifierToken_LBrace_StructDeclarationList_RBrace(id, list), true };
		default:
			return DefaultExpressionShift(parser,next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::type_qualifier:
		{
			std::shared_ptr<TypeQualifier> typeQ = std::static_pointer_cast<TypeQualifier>(nonTerminal);
			retVal = parser->S_StructHeader_TypeQualifier(typeQ);
		}
		break;
		case NonTerminalType::type_specifier:
		{
			std::shared_ptr<TypeSpecifier> typeSpec = std::static_pointer_cast<TypeSpecifier>(nonTerminal);
			retVal = parser->S_StructHeader_TypeSpecifier(typeSpec);
		}
		break;
		case NonTerminalType::struct_declaration:
		{
			std::shared_ptr<StructDeclaration> decl = std::static_pointer_cast<StructDeclaration>(nonTerminal);
			retVal = parser->S_StructToken_IdentifierToken_LBrace_StructDeclarationList_StructDeclaration(id, list, decl);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken_LBrace_StructDeclarationList(const Token& structName, std::shared_ptr<StructDeclarationList>& list)
{
	Handler_S_StructToken_IdentifierToken_LBrace_StructDeclarationList temp(structName, list);

	return StateFuncSkeleton(__func__, temp);
}


ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken_LBrace_StructDeclarationList_StructDeclaration(const Token& structName,
	std::shared_ptr<StructDeclarationList>& list, std::shared_ptr<StructDeclaration>& decl)
{
	list->Append(decl);

	return ParserReturnValue(list, 2);
}

ParserReturnValue GLSL_Parser::S_StructToken_IdentifierToken_LBrace_StructDeclarationList_RBrace(const Token& structName, std::shared_ptr<StructDeclarationList>& list)
{
	log.Debug(__func__);
	return ParserReturnValue(std::make_shared<StructSpecifier>(structName.name,list), 5);
}

ParserReturnValue GLSL_Parser::S_StructSpecifier(std::shared_ptr<StructSpecifier>& structSpec)
{
	log.Debug(__func__);
	return ParserReturnValue(std::make_shared<TypeSpecifierNoArray>(structSpec), 1);
}

class Handler_S_InvariantToken : public IStateHandler
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

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_InvariantToken_IdentifierToken(next), true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_InvariantToken()
{
	Handler_S_InvariantToken temp;

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_InvariantToken_IdentifierToken(const Token& token)
{
	log.Debug(__func__);

	return { std::make_shared<SingleDeclaration>(token.name),2 };
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
			valid = false;
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
			break;
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
	return { std::make_shared<TypeSpecifierNoPrec>(ts,true),3 };
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
		case TokenType::semicolon:
		case TokenType::identifier:
			retVal = ParserReturnValue(std::make_shared<FullySpecifiedType>(*typeSpec), 1);
			break;
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
		return { ParserReturnValue(), false };
		
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };		
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
			valid = false;
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
		case TokenType::equal:
			return { ParserReturnValue(),false };
			break;
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec,token.name),2),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::equal:
			retVal = parser->S_FullySpecifiedType_IdentifierToken_Equal(typeSpec, token);
			break;
		case TokenType::left_bracket:
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket(typeSpec, token);
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

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken temp(spec,token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken_Equal : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;

public:

	Handler_FullySpecifiedType_IdentifierToken_Equal(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token)
		: typeSpec(typeSpec), token(token)
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
			retVal = parser->S_FullySpecifiedType_IdentifierToken_Equal_AssignEx(typeSpec, token, temp);
		}
		break;
		case NonTerminalType::initializer:
		{
			std::shared_ptr<Initializer> temp = std::static_pointer_cast<Initializer>(nonTerminal);
			retVal = parser->S_FullySpecifiedType_IdentifierToken_Equal_Initializer(typeSpec, token, temp);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken_Equal temp(spec, token);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	return { std::make_shared<Initializer>(assignEx),1 };
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Initializer>& initializer)
{
	log.Debug(__func__);
	return { std::make_shared<SingleDeclaration>(spec,token.name,initializer),4 };
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
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(typeSpec, token);
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
			return { ParserReturnValue(), false };
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec,token.name,expression), 5), true};
		}

		
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

class Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token)
		: typeSpec(typeSpec), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		
		switch (parser->PeekToken().type)
		{
		case TokenType::equal:
			return { ParserReturnValue(), false };
		default:
			return { ParserReturnValue(std::make_shared<SingleDeclaration>(typeSpec, token.name, true), 4 ), true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::equal:
			return { parser->S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal(typeSpec,token), true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};


ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket temp(spec, token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal : public IStateHandler
{
public:
	std::shared_ptr<FullySpecifiedType>& typeSpec;
	const Token& token;

public:

	Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& typeSpec, const Token& token)
		: typeSpec(typeSpec), token(token)
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
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_AssignEx(typeSpec, token, temp);
		}
		break;
		case NonTerminalType::initializer:
		{
			std::shared_ptr<Initializer> temp = std::static_pointer_cast<Initializer>(nonTerminal);
			retVal = parser->S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_Initializer(typeSpec, token, temp);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token)
{
	Handler_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal temp(spec, token);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	return { std::make_shared<Initializer>(assignEx),1 };
}

ParserReturnValue GLSL_Parser::S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
	std::shared_ptr<Initializer>& initializer)
{
	log.Debug(__func__);

	return { std::make_shared<SingleDeclaration>(spec,token.name,true,initializer), 6 };
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
		case TokenType::left_bracket:
		case TokenType::dot:
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

class Handler_S_UnaryExpression : public IStateHandler
{
public:
	std::shared_ptr<UnaryExpression>& ex;

public:

	Handler_S_UnaryExpression(std::shared_ptr<UnaryExpression>& _ex)
		: ex(_ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
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
			return { ParserReturnValue(), false };
		default:
			return { ParserReturnValue(std::make_shared<MultiplicativeExpression>(ex),1),true };
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
		case NonTerminalType::assignment_operator:
		{
			std::shared_ptr<AssignmentOperator> op = std::static_pointer_cast<AssignmentOperator>(nonTerminal);
			retVal = parser->S_UnaryExpression_AssignOperator(ex, op);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_UnaryExpression(std::shared_ptr<UnaryExpression>& ex)
{
	Handler_S_UnaryExpression temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_AssignToken(const Token& token)
{
	log.Debug(__func__);

	return { std::make_shared<AssignmentOperator>(token),1 };
}

class Handler_S_UnaryExpression_AssignOperator : public IStateHandler
{
public:
	std::shared_ptr<UnaryExpression>& ex;
	std::shared_ptr<AssignmentOperator>& assignOp;

public:

	Handler_S_UnaryExpression_AssignOperator(std::shared_ptr<UnaryExpression>& _ex,
		std::shared_ptr<AssignmentOperator>& _assignOp)
		: ex(_ex), assignOp(_assignOp)
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
			std::shared_ptr<AssignmentExpression> assignEx = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
			retVal = parser->S_UnaryExpression_AssignOperator_AssignExpression(ex, assignOp, assignEx);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_UnaryExpression_AssignOperator(std::shared_ptr<UnaryExpression>& ex, std::shared_ptr<AssignmentOperator>& assignOp)
{
	Handler_S_UnaryExpression_AssignOperator temp(ex,assignOp);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_UnaryExpression_AssignOperator_AssignExpression(std::shared_ptr<UnaryExpression>& ex,
	std::shared_ptr<AssignmentOperator>& assignOp, std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return { std::make_shared<AssignmentExpression>(ex,assignOp,assignEx),3 };
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

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::unary_expression:
		{
			std::shared_ptr<UnaryExpression> unaryEx = std::static_pointer_cast<UnaryExpression>(nonTerminal);
			retVal = parser->S_MultiplicativeExpression_MulToken_UnaryExpression(ex, token, unaryEx);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
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

class Handler_S_AdditiveExpression_AddToken : public IStateHandler
{
public:
	std::shared_ptr<AdditiveExpression>& ex;
	const Token& token;

public:

	Handler_S_AdditiveExpression_AddToken(std::shared_ptr<AdditiveExpression>& ex, const Token& token)
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

		ParserReturnValue retVal;
		bool valid = true;

		switch (nonTerminal->type)
		{
		case NonTerminalType::multiplicative_expression:
		{
			std::shared_ptr<MultiplicativeExpression> mulEx = std::static_pointer_cast<MultiplicativeExpression>(nonTerminal);
			retVal = parser->S_AdditiveExpression_AddToken_MultiplicativeEx(ex, token, mulEx);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_AdditiveExpression_AddToken(std::shared_ptr<AdditiveExpression>& ex, const Token& token)
{
	Handler_S_AdditiveExpression_AddToken temp(ex, token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_AdditiveExpression_AddToken_MultiplicativeEx : public IStateHandler
{
public:
	std::shared_ptr<AdditiveExpression>& ex;
	const Token& token;
	std::shared_ptr<MultiplicativeExpression>& mulEx;

public:

	Handler_S_AdditiveExpression_AddToken_MultiplicativeEx(std::shared_ptr<AdditiveExpression>& ex, const Token& token,
		std::shared_ptr<MultiplicativeExpression>& mulEx)
		: ex(ex), token(token), mulEx(mulEx)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::slash:
		case TokenType::star:
		case TokenType::percent:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<AdditiveExpression>(ex,token,mulEx),3),true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::slash:
		case TokenType::star:
		case TokenType::percent:
			return { parser->S_MultiplicativeExpression_MulToken(mulEx, next), true };
		default:
			return DefaultExpressionShift(parser, next);
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

ParserReturnValue GLSL_Parser::S_AdditiveExpression_AddToken_MultiplicativeEx(std::shared_ptr<AdditiveExpression>& addEx, const Token& token,
	std::shared_ptr<MultiplicativeExpression>& mulEx)
{
	Handler_S_AdditiveExpression_AddToken_MultiplicativeEx temp(addEx, token, mulEx);

	return StateFuncSkeleton(__func__, temp);
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
			return { ParserReturnValue(), false };
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

class Handler_S_Expression : public IStateHandler
{
public:
	std::shared_ptr<Expression>& ex;

public:

	Handler_S_Expression(std::shared_ptr<Expression>& _ex)
		: ex(_ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		default:
			return { ParserReturnValue(), false };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::semicolon:
			retVal = parser->S_Expression_Semicolon(ex);
			break;
		case TokenType::comma:
			retVal = parser->S_Expression_Comma(ex);
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

ParserReturnValue GLSL_Parser::S_Expression(std::shared_ptr<Expression>& ex)
{
	Handler_S_Expression temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_S_Expression_Comma : public IStateHandler
{
public:
	std::shared_ptr<Expression>& ex;

public:

	Handler_S_Expression_Comma(std::shared_ptr<Expression>& _ex)
		: ex(_ex)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		default:
			return { ParserReturnValue(), false };
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
		case NonTerminalType::assignment_expression:
		{
			std::shared_ptr<AssignmentExpression> assignEx = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
			retVal = parser->S_Expression_Comma_AssignmentExpression(ex, assignEx);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_Expression_Comma(std::shared_ptr<Expression>& ex)
{
	Handler_S_Expression_Comma temp(ex);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_Expression_Comma_AssignmentExpression(std::shared_ptr<Expression>& expression,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	expression->Append(assignEx);

	return { expression,3 };
}

ParserReturnValue GLSL_Parser::S_Expression_Semicolon(std::shared_ptr<Expression>& ex)
{
	log.Debug(__func__);
	
	return { std::make_shared<ExpressionStatement>(ex), 2 };
}


class Handler_FunctionIdentifier : public IStateHandler
{
public:
	std::shared_ptr<FunctionIdentifier>& funcId;

public:

	Handler_FunctionIdentifier(std::shared_ptr<FunctionIdentifier>& funcId)
		: funcId(funcId)
	{

	}

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

		switch (next.type)
		{
		case TokenType::left_paren:
			retVal = parser->S_FunctionIdentifier_Lparen(funcId);
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

ParserReturnValue GLSL_Parser::S_FunctionIdentifier(std::shared_ptr<FunctionIdentifier>& funcId)
{
	Handler_FunctionIdentifier temp(funcId);

	return StateFuncSkeleton(__func__, temp);
}

// Reduction: function_identifier LPAREN
ParserReturnValue GLSL_Parser::S_FunctionIdentifier_Lparen(std::shared_ptr<FunctionIdentifier>& funcId)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCallHeader>(funcId),2 };
}

class Handler_FunctionCallHeader : public IStateHandler
{
public:
	std::shared_ptr<FunctionCallHeader>& funcHeader;

public:

	Handler_FunctionCallHeader(std::shared_ptr<FunctionCallHeader>& funcHeader)
		: funcHeader(funcHeader)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (parser->PeekToken().type)
		{
		case TokenType::right_paren:
			retVal = { std::make_shared<FuncCallHeaderNoParams>(funcHeader),1 };
			break;
		default:
			valid = false;
			break;
		}

		return { retVal,valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::keyword_void:
			retVal = parser->S_FunctionCallHeader_VoidToken(funcHeader);
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
		case NonTerminalType::assignment_expression:
			{
				std::shared_ptr<AssignmentExpression> temp = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
				retVal = parser->S_FunctionCallHeader_AssignEx(funcHeader,temp);
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}

		return { retVal,valid };
	}

};

ParserReturnValue GLSL_Parser::S_FunctionCallHeader(std::shared_ptr<FunctionCallHeader>& funcHeader)
{
	Handler_FunctionCallHeader temp(funcHeader);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeader_VoidToken(std::shared_ptr<FunctionCallHeader>& funcHeader)
{
	log.Debug(__func__);

	return { std::make_shared<FuncCallHeaderNoParams>(funcHeader),2 };
}

class Handler_FunctionCallHeaderNoParams : public IStateHandler
{
public:
	std::shared_ptr<FuncCallHeaderNoParams>& funcHeader;

public:

	Handler_FunctionCallHeaderNoParams(std::shared_ptr<FuncCallHeaderNoParams>& funcHeader)
		: funcHeader(funcHeader)
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
		case TokenType::right_paren:
			retVal = parser->S_FunctionCallHeaderNoParams_RParen(funcHeader);
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
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderNoParams(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam)
{
	Handler_FunctionCallHeaderNoParams temp(funcHeaderNoParam);

	return StateFuncSkeleton(__func__, temp);
}

// Reduction: function_call_header_no_params RIGHT_PAREN
ParserReturnValue GLSL_Parser::S_FunctionCallHeaderNoParams_RParen(std::shared_ptr<FuncCallHeaderNoParams>& funcHeaderNoParam)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCallGeneric>(funcHeaderNoParam),2 };
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeader_AssignEx(std::shared_ptr<FunctionCallHeader>& funcHeader,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);

	return { std::make_shared<FuncCallHeaderParams>(funcHeader,assignEx),2 };
}

class Handler_FunctionCallHeaderWithParams : public IStateHandler
{
public:
	std::shared_ptr<FuncCallHeaderParams>& funcHeader;

public:

	Handler_FunctionCallHeaderWithParams(std::shared_ptr<FuncCallHeaderParams>& funcHeader)
		: funcHeader(funcHeader)
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
			valid = false;
			break;
		}

		return { retVal,valid };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		ParserReturnValue retVal;
		bool valid = true;

		switch (next.type)
		{
		case TokenType::right_paren:
			retVal = parser->S_FunctionCallHeaderWithParams_RParen(funcHeader);
			break;
		case TokenType::comma:
			retVal = parser->S_FunctionCallHeaderWithParams_Comma(funcHeader);
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

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam)
{
	Handler_FunctionCallHeaderWithParams temp(funcHeaderWithParam);

	return StateFuncSkeleton(__func__, temp);
}

// Reduction: function_call_header_with_params RIGHT_PAREN
ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_RParen(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCallGeneric>(funcHeaderWithParam),2 };
}

class Handler_FunctionCallHeaderWithParams_Comma : public IStateHandler
{
public:
	std::shared_ptr<FuncCallHeaderParams>& funcHeader;

public:

	Handler_FunctionCallHeaderWithParams_Comma(std::shared_ptr<FuncCallHeaderParams>& funcHeader)
		: funcHeader(funcHeader)
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
		case NonTerminalType::assignment_expression:
			{
				std::shared_ptr<AssignmentExpression> temp = std::static_pointer_cast<AssignmentExpression>(nonTerminal);
				retVal = parser->S_FunctionCallHeaderWithParams_Comma_AssignEx(funcHeader, temp);
			}
			break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}

		return { retVal,valid };
	}

};

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_Comma(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam)
{
	Handler_FunctionCallHeaderWithParams_Comma temp(funcHeaderWithParam);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_FunctionCallHeaderWithParams_Comma_AssignEx(std::shared_ptr<FuncCallHeaderParams>& funcHeaderWithParam,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	
	funcHeaderWithParam->Append(assignEx);

	return { funcHeaderWithParam ,3 };
}

ParserReturnValue GLSL_Parser::S_FunctionCallGeneric(std::shared_ptr<FunctionCallGeneric>& funcCall)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCallOrMethod>(funcCall),1 };
}

ParserReturnValue GLSL_Parser::S_FunctionCallOrMethod(std::shared_ptr<FunctionCallOrMethod>& funcCall)
{
	log.Debug(__func__);

	return { std::make_shared<FunctionCall>(funcCall),1 };
}

ParserReturnValue GLSL_Parser::S_FunctionCall(std::shared_ptr<FunctionCall>& funcCall)
{
	log.Debug(__func__);

	return { std::make_shared<PostfixExpression>(funcCall),1 };
}

ParserReturnValue GLSL_Parser::S_SingleDeclaration(std::shared_ptr<SingleDeclaration>& singleDecl)
{
	log.Debug(__func__);
	return { std::make_shared<InitDeclaratorList>(singleDecl),1 };
}

class Handler_InitDeclaratorList : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;

public:

	Handler_InitDeclaratorList(std::shared_ptr<InitDeclaratorList>& list)
		: list(list)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		
		switch (parser->PeekToken().type)
		{
		case TokenType::comma:
			return { ParserReturnValue(),false };
		default:
			return { ParserReturnValue(std::make_shared<Declaration>(list),1) };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::semicolon:
			return { parser->S_InitDeclaratorList_Semicolon(list),true };
		case TokenType::comma:
			return { parser->S_InitDeclaratorList_Comma(list),true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList(std::shared_ptr<InitDeclaratorList>& initList)
{
	Handler_InitDeclaratorList temp(initList);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Semicolon(std::shared_ptr<InitDeclaratorList>& initList)
{
	log.Debug(__func__);
	return { std::make_shared<Declaration>(initList),2 };
}

class Handler_InitDeclaratorList_Comma : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;

public:

	Handler_InitDeclaratorList_Comma(std::shared_ptr<InitDeclaratorList>& list)
		: list(list)
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

		switch (next.type)
		{
		case TokenType::identifier:
			return { parser->S_InitDeclaratorList_Comma_IdToken(list, next),true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma(std::shared_ptr<InitDeclaratorList>& initList)
{
	Handler_InitDeclaratorList_Comma temp(initList);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;

public:

	Handler_InitDeclaratorList_Comma_IdToken(std::shared_ptr<InitDeclaratorList>& list, const Token& token)
		: list(list), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		
		switch (parser->PeekToken().type)
		{
		case TokenType::left_bracket:
			return { ParserReturnValue(),false };
		default:
			DeclarationData data{ token.name };
			list->Append(data);
			return { ParserReturnValue(list,3), true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::left_bracket:
			return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket(list, token),true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(), false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken(std::shared_ptr<InitDeclaratorList>& initList, const Token& token)
{
	Handler_InitDeclaratorList_Comma_IdToken temp(initList, token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket(std::shared_ptr<InitDeclaratorList>& list, const Token& token)
		: list(list), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::right_bracket:
			return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket(list,token),true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		
		switch (nonTerminal->type)
		{
		case NonTerminalType::expression:
			{
				auto temp = std::static_pointer_cast<Expression>(nonTerminal);
				return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket_Expression(list, token, temp),true };
			}
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token)
{
	Handler_InitDeclaratorList_Comma_IdToken_LBracket temp(initList, token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket(std::shared_ptr<InitDeclaratorList>& list, const Token& token)
		: list(list), token(token)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::equal:
			return { ParserReturnValue(),false };
		default:
			DeclarationData data{ token.name, true };
			list->Append(data);
			return { ParserReturnValue(list,5), true };
		}

		
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::equal:
			return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal(list,token),true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token)
{
	Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket temp(initList, token);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& list, const Token& token)
		: list(list), token(token)
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
			retVal = parser->S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_AssignEx(list, token, temp);
		}
		break;
		case NonTerminalType::initializer:
		{
			std::shared_ptr<Initializer> temp = std::static_pointer_cast<Initializer>(nonTerminal);
			retVal = parser->S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_Initializer(list, token, temp);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& initList, const Token& token)
{
	Handler_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal temp(initList, token);

	return StateFuncSkeleton(__func__, temp);
}

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_AssignEx(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	return { std::make_shared<Initializer>(assignEx),1 };
}

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_RBracket_Equal_Initializer(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Initializer>& initializer)
{
	log.Debug(__func__);

	DeclarationData data{ token.name, true, initializer };
	initList->Append(data);
	return { initList, 7 };
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression(std::shared_ptr<InitDeclaratorList>& list, 
		const Token& token, std::shared_ptr<Expression>& expression)
		: list(list), token(token), expression(expression)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::right_bracket:
			return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket(list,token,expression),true };
		default:
			return DefaultExpressionShift(parser, next);
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_Expression(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression temp(initList, token, expression);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket(std::shared_ptr<InitDeclaratorList>& list,
		const Token& token, std::shared_ptr<Expression>& expression)
		: list(list), token(token), expression(expression)
	{

	}

	HandlerReturn Reduction(GLSL_Parser* parser) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (parser->PeekToken().type)
		{
		case TokenType::equal:
			return { ParserReturnValue(),false };
		default:
			DeclarationData data{ token.name, expression };
			list->Append(data);
			return { ParserReturnValue(list,6), true };
		}
	}

	HandlerReturn Shift(GLSL_Parser* parser, const Token& next) override
	{
		parser->log.Debug(__FUNCTION__);

		switch (next.type)
		{
		case TokenType::equal:
			return { parser->S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal(list,token, expression),true };
		default:
			return { ParserReturnValue(),false };
		}
	}

	HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) override
	{
		parser->log.Debug(__FUNCTION__);
		return { ParserReturnValue(),false };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket temp(initList, token, expression);

	return StateFuncSkeleton(__func__, temp);
}

class Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal : public IStateHandler
{
public:
	std::shared_ptr<InitDeclaratorList>& list;
	const Token& token;
	std::shared_ptr<Expression>& expression;

public:

	Handler_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& list,
		const Token& token, std::shared_ptr<Expression>& expression)
		: list(list), token(token), expression(expression)
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
			retVal = parser->S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_AssignEx(list, token, expression, temp);
		}
		break;
		case NonTerminalType::initializer:
		{
			std::shared_ptr<Initializer> temp = std::static_pointer_cast<Initializer>(nonTerminal);
			retVal = parser->S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_Initializer(list, token, expression, temp);
		}
		break;
		default:
			return DefaultExpressionGoto(parser, nonTerminal);
		}
		return { retVal, valid };
	}

};

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}


ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_AssignEx(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx)
{
	log.Debug(__func__);
	return { std::make_shared<Initializer>(assignEx), 1 };
}

ParserReturnValue GLSL_Parser::S_InitDeclaratorList_Comma_IdToken_LBracket_Expression_RBracket_Equal_Initializer(std::shared_ptr<InitDeclaratorList>& initList, const Token& token,
	std::shared_ptr<Expression>& expression, std::shared_ptr<Initializer>& initializer)
{
	log.Debug(__func__);

	DeclarationData data{ token.name, expression, initializer };
	initList->Append(data);
	return { initList, 8 };
}

ParserReturnValue GLSL_Parser::S_Declaration(std::shared_ptr<Declaration>& singleDecl)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DeclarationStatement(std::shared_ptr<DeclarationStatement>& declStatement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SimpleStatement(std::shared_ptr<SimpleStatement>& simpleStatement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Statement(std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Statement_ElseToken(std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Statement_ElseToken_Statement(std::shared_ptr<Statement>& a, std::shared_ptr<Statement>& b)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SelectionRestStatement(std::shared_ptr<SelectionRestStatement>& selectionRest)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_StatementList(std::shared_ptr<StatementList>& statementList)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_StatementList_Statement(std::shared_ptr<StatementList>& statementList, std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ExpressionStatement(std::shared_ptr<ExpressionStatement>& expressionStatement)
{
	log.Debug(__func__);

	return { std::make_shared<SimpleStatement>(expressionStatement),1 };
}

ParserReturnValue GLSL_Parser::S_SelectionStatement(std::shared_ptr<SelectionStatement>& selectionStatement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IfToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IfToken_LParen()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IfToken_LParen_Expression(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IfToken_LParen_Expression_RParen(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IfToken_LParen_Expression_RParen_SelectionRestStatement(std::shared_ptr<Expression>& expression,
	std::shared_ptr<SelectionRestStatement>& selectionRest)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_Condition(std::shared_ptr<Condition>& condition)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen_Expression(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen_Expression_RParen(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen_Expression_RParen_LBrace(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen_Expression_RParen_LBrace_SwitchStatementList(std::shared_ptr<Expression>& expression,
	std::shared_ptr<SwitchStatementList>& statementList)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchToken_LParen_Expression_RParen_LBrace_SwitchStatementList_RBrace(std::shared_ptr<Expression>& expression,
	std::shared_ptr<SwitchStatementList>& statementList)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchStatementList(std::shared_ptr<SwitchStatementList>& condition)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_SwitchStatement(std::shared_ptr<SwitchStatement>& switchStatement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CaseLabel(std::shared_ptr<CaseLabel>& label)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CaseToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CaseToken_Expression(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CaseToken_Expression_Colon(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DefaultToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DefaultToken_Colon()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ContinueToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ContinueToken_Semicolon()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_BreakToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_BreakToken_Semicolon()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ReturnToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ReturnToken_Expression(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ReturnToken_Expression_Semicolon(std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ReturnToken_Semicolon()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DiscardToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DiscardToken_Semicolon()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_JumpStatement(std::shared_ptr<JumpStatement>& jumpStatement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForInitStatement(std::shared_ptr<ForInitStatement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ConditionOpt(std::shared_ptr<ConditionOpt>& conditionOpt)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ConditionOpt_Semicolon(std::shared_ptr<ConditionOpt>& conditionOpt)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ConditionOpt_Semicolon_Expression(std::shared_ptr<ConditionOpt>& conditionOpt,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForRestStatement(std::shared_ptr<ForRestStatement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_WhileToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_WhileToken_LParen()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_WhileToken_LParen_Condition(std::shared_ptr<Condition>& condition)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_WhileToken_LParen_Condition_RParen(std::shared_ptr<Condition>& condition)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_WhileToken_LParen_Condition_RParen_StatementNoNewScope(std::shared_ptr<Condition>& condition,
	std::shared_ptr<StatementNoNewScope>& block)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement(std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement_WhileToken(std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement_WhileToken_LParen(std::shared_ptr<Statement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement_WhileToken_LParen_Expression(std::shared_ptr<Statement>& statement,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement_WhileToken_LParen_Expression_RParen(std::shared_ptr<Statement>& statement,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_DoToken_Statement_WhileToken_LParen_Expression_RParen_Semicolon(std::shared_ptr<Statement>& statement,
	std::shared_ptr<Expression>& expression)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken_LParen()
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken_LParen_ForInitStatement(std::shared_ptr<ForInitStatement>& init)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken_LParen_ForInitStatement_ForRestStatement(std::shared_ptr<ForInitStatement>& init,
	std::shared_ptr<ForRestStatement>& rest)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken_LParen_ForInitStatement_ForRestStatement_RParen(std::shared_ptr<ForInitStatement>& init,
	std::shared_ptr<ForRestStatement>& rest)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_ForToken_LParen_ForInitStatement_ForRestStatement_RParen_StatementNoNewScope(std::shared_ptr<ForInitStatement>& init,
	std::shared_ptr<ForRestStatement>& rest, std::shared_ptr<StatementNoNewScope>& block)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_IteratorStatement(std::shared_ptr<IterationStatement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_StatementNoNewScope(std::shared_ptr<StatementNoNewScope>& block)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CompoundStatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& block)
{
	log.Debug(__func__);
	return ParserReturnValue();
}

ParserReturnValue GLSL_Parser::S_CompoundStatement(std::shared_ptr<CompoundStatement>& statement)
{
	log.Debug(__func__);
	return ParserReturnValue();
}