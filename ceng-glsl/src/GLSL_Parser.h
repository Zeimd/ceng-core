#ifndef CENG_GLSL_PARSER_H
#define CENG_GLSL_PARSER_H

#include <ceng/datatypes/return-val.h>

#include <vector>
#include <ceng/GLSL/Token.h>
#include <ceng/GLSL/IParser.h>

#include <ceng/GLSL/ShaderType.h>

#include "ParserReturnValue.h"
#include "HandlerReturn.h"
#include "IStateHandler.h"

#include "Symbol.h"
#include "SymbolDatabase.h"

namespace Ceng
{
	class AdditiveExpression;
	class AndExpression;
	class AssignmentExpression;
	class AssignmentOperator;

	class CaseLabel;
	class CompoundStatement;
	class CompoundStatementNoNewScope;
	class Condition;
	class ConditionalExpression;
	class ConditionOpt;
	class ConstantExpression;

	class Declaration;
	class DeclarationStatement;

	class EqualityExpression;
	class Expression;
	class ExpressionStatement;

	class ForInitStatement;
	class ForRestStatement;
	class FullySpecifiedType;
	class FuncCallHeaderNoParams;
	class FuncCallHeaderParams;
	class FunctionCall;
	class FunctionCallGeneric;
	class FunctionCallHeader;
	class FunctionCallOrMethod;
	class FunctionDeclarator;
	class FunctionDefinition;
	class FunctionHeader;
	class FunctionHeaderWithParams;
	class FunctionIdentifier;
	class FunctionPrototype;

	class InitDeclaratorList;
	class Initializer;
	class IntegerExpression;
	class InterpolationQualifier;
	class IterationStatement;

	class JumpStatement;

	class LayoutQualifier;
	class LayoutQualifierId;
	class LayoutQualifierIdList;
	class LogicalAndExpression;
	class LogicalOrExpression;
	class LogicalXorExpression;

	class MultiplicativeExpression;

	class OrExpression;

	class ParameterDeclaration;
	class ParameterDeclarator;
	class ParameterQualifier;
	class ParameterTypeQualifier;
	class PostfixExpression;
	class PrecisionQualifier;
	class PrimaryExpression;

	class RelationalExpression;

	class SelectionRestStatement;
	class SelectionStatement;
	class ShiftExpression;
	class SimpleStatement;
	class SingleDeclaration;
	class Statement;
	class StatementList;
	class StatementNoNewScope;
	class StorageQualifier;
	class StructDeclaration;
	class StructDeclarationList;
	class StructDeclarator;
	class StructDeclaratorList;
	class StructSpecifier;
	class SwitchStatement;
	class SwitchStatementList;

	class TranslationUnit;
	class TypeQualifier;
	class TypeSpecifier;
	class TypeSpecifierNoArray;
	class TypeSpecifierNoPrec;

	class UnaryExpression;
	class UnaryOperator;
	class XorExpression;

	class GLSL_Parser : public GLSL::IParser
	{
	public:

		std::vector<Token> tokens;

		std::vector<Token>::const_iterator tokenIter;

		Log log;

		std::shared_ptr<SymbolDatabase> symbolDatabase;

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
		
		CRESULT Parse(GLSL::ShaderType::value shader, const std::vector<Token>& in_tokens, GLSL::AbstractSyntaxTree& output) override;

		const Token& PeekToken();

		const Token NextToken();

		// Used when PeekToken() has been used to deduce next parser action
		void DiscardNext();

	public:

		ParserReturnValue StateFuncSkeleton(const char* callerName, IStateHandler& handler);

		ParserReturnValue S_TranslationUnit();
		
		ParserReturnValue S_InvariantToken();

		ParserReturnValue S_InvariantToken_IdentifierToken(const Token& token);

		ParserReturnValue S_InvariantToken_InterpolationQualifier(std::shared_ptr<InterpolationQualifier>& interpolation);

		ParserReturnValue S_InvariantToken_InterpolationQualifier_StorageQualifier(std::shared_ptr<InterpolationQualifier>& interpolation,
			std::shared_ptr<StorageQualifier>& sq);

		ParserReturnValue S_InvariantToken_StorageQualifier(std::shared_ptr<StorageQualifier>& sq);

		ParserReturnValue S_PrecisionToken();

		ParserReturnValue S_PrecisionToken_PrecisionQualifier(std::shared_ptr<PrecisionQualifier>& qualifier);

		ParserReturnValue S_PrecisionToken_PrecisionQualifier_TypeSpecifierNoPrec(std::shared_ptr<PrecisionQualifier>& qualifier,
			std::shared_ptr<TypeSpecifierNoPrec>& typeNoPrec);

		ParserReturnValue S_PrecisionToken_PrecisionQualifier_TypeSpecifierNoPrec_Semicolon(std::shared_ptr<PrecisionQualifier>& qualifier,
			std::shared_ptr<TypeSpecifierNoPrec>& typeNoPrec);

		ParserReturnValue S_PrecisionQualifierToken(const Token& qualifier);

		ParserReturnValue S_PrecisionQualifier(std::shared_ptr<PrecisionQualifier>& qualifier);

		ParserReturnValue S_PrecisionQualifier_TypeSpecNoPrec(std::shared_ptr<PrecisionQualifier>& qualifier,
			std::shared_ptr<TypeSpecifierNoPrec>& typeSpec);

		ParserReturnValue S_StructToken();

		ParserReturnValue S_StructToken_IdentifierToken(const Token& structName);

		ParserReturnValue S_StructToken_IdentifierToken_LBrace(const Token& structName);

		ParserReturnValue S_StructToken_IdentifierToken_LBrace_StructDeclaration(const Token& structName, std::shared_ptr<StructDeclaration>& decl);

		ParserReturnValue S_StructToken_IdentifierToken_LBrace_StructDeclarationList(const Token& structName, std::shared_ptr<StructDeclarationList>& list);

		ParserReturnValue S_StructToken_IdentifierToken_LBrace_StructDeclarationList_StructDeclaration(const Token& structName, 
			std::shared_ptr<StructDeclarationList>& list, std::shared_ptr<StructDeclaration>& decl);

		// Reduction: struct_specifier
		ParserReturnValue S_StructToken_IdentifierToken_LBrace_StructDeclarationList_RBrace(const Token& structName, std::shared_ptr<StructDeclarationList>& list);

		ParserReturnValue S_StructToken_LBrace();

		ParserReturnValue S_StructToken_LBrace_StructDeclaration(std::shared_ptr<StructDeclaration>& decl);

		ParserReturnValue S_StructToken_LBrace_StructDeclarationList_StructDeclaration(std::shared_ptr<StructDeclarationList>& list,
			std::shared_ptr<StructDeclaration>& decl);

		ParserReturnValue S_StructToken_LBrace_StructDeclarationList(std::shared_ptr<StructDeclarationList>& list);

		// Reduction: struct_specifier
		ParserReturnValue S_StructToken_LBrace_StructDeclarationList_RBrace(std::shared_ptr<StructDeclarationList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier(std::shared_ptr<TypeQualifier>& typeQ);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& typeQ, std::shared_ptr<TypeSpecifier>& typeSpec);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList(std::shared_ptr<TypeQualifier>& typeQ, 
			std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeQualifier>& typeQ,
			std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(std::shared_ptr<TypeQualifier>& typeQ,
			std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list,std::shared_ptr<StructDeclarator>& decl);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeQualifier_TypeSpecifier_StructDeclaratorList_Semicolon(std::shared_ptr<TypeQualifier>& typeQ, 
			std::shared_ptr<TypeSpecifier>& typeSpec, std::shared_ptr<StructDeclaratorList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeSpecifier(std::shared_ptr<TypeSpecifier>& typeSpec);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeSpecifier_StructDeclaratorList(std::shared_ptr<TypeSpecifier>& typeSpec, 
			std::shared_ptr<StructDeclaratorList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma(std::shared_ptr<TypeSpecifier>& typeSpec,
			std::shared_ptr<StructDeclaratorList>& list);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE {struct_declaration_list}
		ParserReturnValue S_StructHeader_TypeSpecifier_StructDeclaratorList_Comma_StructDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec,
			std::shared_ptr<StructDeclaratorList>& list, std::shared_ptr<StructDeclarator>& decl);

		// StructHeader = STRUCT IDENTIFIER LEFT_BRACE
		ParserReturnValue S_StructHeader_TypeSpecifier_StructDeclaratorList_Semicolon(std::shared_ptr<TypeSpecifier>& typeSpec,
			std::shared_ptr<StructDeclaratorList>& list);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_IdentifierToken(const Token& id);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_IdentifierToken_LBracket(const Token& id);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_IdentifierToken_LBracket_RBracket(const Token& id);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_IdentifierToken_LBracket_Expression(const Token& id, std::shared_ptr<Expression>& arraySize);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_IdentifierToken_LBracket_Expression_RBracket(const Token& id, std::shared_ptr<Expression>& arraySize);

		// StructDecl = StructHeader {type_qualifier} type_specifier 
		ParserReturnValue S_StructDecl_StructDeclarator(std::shared_ptr<StructDeclarator>& decl);

		ParserReturnValue S_StructSpecifier(std::shared_ptr<StructSpecifier>& structSpec);

		ParserReturnValue S_CentroidToken(const Token& centroid);

		ParserReturnValue S_CentroidToken_InToken(const Token& centroid, const Token& in);

		ParserReturnValue S_CentroidToken_OutToken(const Token& centroid, const Token& out);

		ParserReturnValue S_StorageQualifierToken(TokenType::value value);

		ParserReturnValue S_LiteralToken(const Token& token);

		ParserReturnValue S_IdentifierToken(const Token& token);

		ParserReturnValue S_DatatypeToken(TokenType::value value);

		//ParserReturnValue S_CustomTypeToken(const Token& typeName);

		ParserReturnValue S_LayoutToken();

		ParserReturnValue S_LayoutToken_LParen();

		ParserReturnValue S_LayoutToken_LParen_LayoutQualifierId(std::shared_ptr<LayoutQualifierId>& qualifier);

		ParserReturnValue S_LayoutToken_LParen_LayoutQualifierIdList(std::shared_ptr<LayoutQualifierIdList>& list);

		ParserReturnValue S_LayoutToken_LParen_LayoutQualifierIdList_Comma(std::shared_ptr<LayoutQualifierIdList>& list);

		ParserReturnValue S_LayoutToken_LParen_LayoutQualifierIdList_Comma_LayoutQualifierId(std::shared_ptr<LayoutQualifierIdList>& list,
			std::shared_ptr<LayoutQualifierId>& qualifier);

		ParserReturnValue S_LayoutToken_LParen_LayoutQualifierIdList_RParen(std::shared_ptr<LayoutQualifierIdList>& list);

		ParserReturnValue S_LayoutIdBuilder_Identifier(const Token& id);

		ParserReturnValue S_LayoutIdBuilder_Identifier_Equal(const Token& id);

		ParserReturnValue S_LayoutIdBuilder_Identifier_Equal_IntConstant(const Token& id, const Ceng::INT32 value);

		ParserReturnValue S_LayoutQualifier(std::shared_ptr<LayoutQualifier>& layout);

		ParserReturnValue S_LayoutQualifier_StorageQualifier(std::shared_ptr<LayoutQualifier>& layout,
			std::shared_ptr<StorageQualifier>& sq);

		ParserReturnValue S_InterpolationToken(const Token& interpolation);

		ParserReturnValue S_InterpolationQualifier(std::shared_ptr<InterpolationQualifier>& interpolation);

		ParserReturnValue S_InterpolationQualifier_StorageQualifier(std::shared_ptr<InterpolationQualifier>& interpolation,
			std::shared_ptr<StorageQualifier>& sq);

		ParserReturnValue S_StorageQualifier(std::shared_ptr<StorageQualifier>& sq);
		
		ParserReturnValue S_TypeQualifier(std::shared_ptr<TypeQualifier>& tq);

		ParserReturnValue S_TypeQualifier_Semicolon(std::shared_ptr<TypeQualifier>& tq);

		ParserReturnValue S_TypeQualifier_TypeSpecifierNonArray(std::shared_ptr<TypeQualifier>& sq, std::shared_ptr<TypeSpecifierNoArray>& ts);
		ParserReturnValue S_TypeQualifier_TypeSpecifierNoPrec(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifierNoPrec>& ts);

		ParserReturnValue S_TypeQualifier_TypeSpecifier(std::shared_ptr<TypeQualifier>& tq, std::shared_ptr<TypeSpecifier>& ts);

		ParserReturnValue S_TypeQualifier_Identifier(std::shared_ptr<TypeQualifier>& tq, const Token& interfaceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace(std::shared_ptr<TypeQualifier>& tq, const Token& interfaceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclaration(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName, std::shared_ptr<StructDeclaration>& decl);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList(std::shared_ptr<TypeQualifier>& typeQ, 
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_StructDeclaration(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName, std::shared_ptr<StructDeclarationList>& list, std::shared_ptr<StructDeclaration>& decl);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Semicolon(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_Semicolon(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket_RBracket(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket_RBracket_Semicolon(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket_Expression(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName, std::shared_ptr<Expression>& expression);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket_Expression_RBracket(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName, std::shared_ptr<Expression>& expression);

		ParserReturnValue S_TypeQualifier_Identifier_LBrace_StructDeclarationList_RBrace_Identifier_LBracket_Expression_RBracket_Semicolon(std::shared_ptr<TypeQualifier>& typeQ,
			const Token& interfaceName,	std::shared_ptr<StructDeclarationList>& list, const Token& instanceName, std::shared_ptr<Expression>& expression);

		ParserReturnValue S_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& spec);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Initializer>& initializer);

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

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal(std::shared_ptr<FullySpecifiedType>& spec, const Token& token);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_FullySpecifiedType_IdentifierToken_LBracket_RBracket_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& spec, const Token& token,
			std::shared_ptr<Initializer>& initializer);

		ParserReturnValue S_FullySpecifiedType_Identifier_LParen(std::shared_ptr<FullySpecifiedType>& type, const Token& id);

		ParserReturnValue S_FunctionHeader(std::shared_ptr<FunctionHeader>& header);

		ParserReturnValue S_ParameterDeclarator(std::shared_ptr<ParameterDeclarator>& decl);

		ParserReturnValue S_FunctionHeader_ParameterDeclaration(std::shared_ptr<FunctionHeader>& header, std::shared_ptr<ParameterDeclaration>& decl);

		ParserReturnValue S_FunctionHeaderWithParams(std::shared_ptr<FunctionHeaderWithParams>& header);

		ParserReturnValue S_FunctionHeaderWithParams_Comma(std::shared_ptr<FunctionHeaderWithParams>& header);

		ParserReturnValue S_FunctionHeaderWithParams_Comma_ParameterDeclaration(std::shared_ptr<FunctionHeaderWithParams>& header, 
			std::shared_ptr<ParameterDeclaration>& decl);

		ParserReturnValue S_FunctionDeclarator(std::shared_ptr<FunctionDeclarator>& decl);

		ParserReturnValue S_FunctionDeclarator_RParen(std::shared_ptr<FunctionDeclarator>& decl);

		ParserReturnValue S_FunctionPrototype(std::shared_ptr<FunctionPrototype>& prototype);

		ParserReturnValue S_FunctionPrototype_Semicolon(std::shared_ptr<FunctionPrototype>& prototype);

		ParserReturnValue S_FunctionPrototype_LBrace(std::shared_ptr<FunctionPrototype>& prototype);

		ParserReturnValue S_FunctionPrototype_LBrace_RBrace(std::shared_ptr<FunctionPrototype>& prototype);

		ParserReturnValue S_FunctionPrototype_LBrace_Statement(std::shared_ptr<FunctionPrototype>& prototype, std::shared_ptr<Statement>& statement);

		ParserReturnValue S_FunctionPrototype_LBrace_StatementList(std::shared_ptr<FunctionPrototype>& prototype, std::shared_ptr<StatementList>& list);

		ParserReturnValue S_FunctionPrototype_LBrace_StatementList_Statement(std::shared_ptr<FunctionPrototype>& prototype, 
			std::shared_ptr<StatementList>& list, std::shared_ptr<Statement>& statement);

		ParserReturnValue S_FunctionPrototype_LBrace_StatementList_RBrace(std::shared_ptr<FunctionPrototype>& prototype, std::shared_ptr<StatementList>& list);

		ParserReturnValue S_FunctionPrototype_CompoundStatementNoNewScope(std::shared_ptr<FunctionPrototype>& prototype, 
			std::shared_ptr<CompoundStatementNoNewScope>& statement);

		ParserReturnValue S_ParamBuilder_TypeSpecifier_Identifier(std::shared_ptr<TypeSpecifier>& type, const Token& id);

		ParserReturnValue S_ParamBuilder_TypeSpecifier_Identifier_LBracket(std::shared_ptr<TypeSpecifier>& type, const Token& id);

		ParserReturnValue S_ParamBuilder_TypeSpecifier_Identifier_LBracket_Expression(std::shared_ptr<TypeSpecifier>& type, const Token& id,
			std::shared_ptr<Expression>& ex);

		ParserReturnValue S_ParamBuilder_TypeSpecifier_Identifier_LBracket_Expression_RBracket(std::shared_ptr<TypeSpecifier>& type, const Token& id,
			std::shared_ptr<Expression>& ex);

		ParserReturnValue S_ParamBuilder_ParameterTypeQualifierToken(const Token& token);

		ParserReturnValue S_ParamBuilder_ParameterQualifierToken(const Token& token);

		ParserReturnValue S_ParameterTypeQualifier(std::shared_ptr<ParameterTypeQualifier>& typeQ);

		ParserReturnValue S_ParamBuilder_TypeSpecifier(std::shared_ptr<TypeSpecifier>& spec);

		ParserReturnValue S_ParameterTypeQualifier_ParameterQualifier(std::shared_ptr<ParameterTypeQualifier>& typeQ,
			std::shared_ptr<ParameterQualifier>& paramQ);

		ParserReturnValue S_ParameterTypeQualifier_ParameterDeclarator(std::shared_ptr<ParameterTypeQualifier>& typeQ,
			std::shared_ptr<ParameterDeclarator>& decl);

		ParserReturnValue S_ParameterTypeQualifier_TypeSpecifier(std::shared_ptr<ParameterTypeQualifier>& typeQ,
			std::shared_ptr<TypeSpecifier>& spec);

		ParserReturnValue S_ParameterTypeQualifier_ParameterQualifier_ParameterDeclarator(std::shared_ptr<ParameterTypeQualifier>& typeQ,
			std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<ParameterDeclarator>& decl);

		ParserReturnValue S_ParameterTypeQualifier_ParameterQualifier_TypeSpecifier(std::shared_ptr<ParameterTypeQualifier>& typeQ,
			std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<TypeSpecifier>& spec);

		ParserReturnValue S_ParameterQualifier(std::shared_ptr<ParameterQualifier>& paramQ);

		ParserReturnValue S_ParameterQualifier_ParameterDeclarator(std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<ParameterDeclarator>& decl);

		ParserReturnValue S_ParameterQualifier_TypeSpecifier(std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<TypeSpecifier>& spec);

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

		ParserReturnValue S_UnaryOperatorToken(const Token& token);

		// unary_operator 
		ParserReturnValue S_UnaryOperator(std::shared_ptr<UnaryOperator>& op);

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
		ParserReturnValue S_LogicalXorExpression_XorOp_LogicalAndEx(std::shared_ptr<LogicalXorExpression>& logicXorEx,
			std::shared_ptr<LogicalAndExpression>& logicAndEx);

		// logical_xor_expression
		ParserReturnValue S_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& ex);

		ParserReturnValue S_LogicalOrExpression_OrOp(std::shared_ptr<LogicalOrExpression>& ex);

		// logical_or_expression OR_OP logical_xor_expression
		ParserReturnValue S_LogicalOrExpression_OrOp_LogicalXorEx(std::shared_ptr<LogicalOrExpression>& logicOrEx,
			std::shared_ptr<LogicalXorExpression>& logicXorEx);

		// logical_or_expression
		ParserReturnValue S_ConditionalExpression(std::shared_ptr<ConditionalExpression>& ex);

		ParserReturnValue S_LogicalOrExpression_Question(std::shared_ptr<LogicalOrExpression>& logicalOrex);

		ParserReturnValue S_LogicalOrExpression_Question_Expression(std::shared_ptr<LogicalOrExpression>& logicalOrex,
			std::shared_ptr<Expression>& expression);

		ParserReturnValue S_LogicalOrExpression_Question_Expression_Colon(std::shared_ptr<LogicalOrExpression>& logicalOrex,
			std::shared_ptr<Expression>& expression);

		// conditional_expression QUESTION expression COLON assignment_expression
		ParserReturnValue S_LogicalOrExpression_Question_Expression_Colon_AssignEx(std::shared_ptr<LogicalOrExpression>& logicalOrex,
			std::shared_ptr<Expression>& expression, std::shared_ptr<AssignmentExpression>& assignEx);

		// conditional_expression
		ParserReturnValue S_AssignmentExpression(std::shared_ptr<AssignmentExpression>& ex);

		ParserReturnValue S_Semicolon();

		ParserReturnValue S_LParen();

		ParserReturnValue S_LParen_Expression(std::shared_ptr<Expression>& ex);

		ParserReturnValue S_LParen_Expression_RParen(std::shared_ptr<Expression>& ex);

		// compound_statement start
		ParserReturnValue S_LBrace();

		// compound_statement end
		ParserReturnValue S_LBrace_RBrace();

		ParserReturnValue S_LBrace_Statement(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_LBrace_StatementList(std::shared_ptr<StatementList>& list);

		ParserReturnValue S_LBrace_StatementList_Statement(std::shared_ptr<StatementList>& list, std::shared_ptr<Statement>& statement);

		// compound_statement end
		ParserReturnValue S_LBrace_StatementList_RBrace(std::shared_ptr<StatementList>& list);

		// compound_statement_no_new_scope start
		ParserReturnValue S_NoScope_LBrace();

		// compound_statement_no_new_scope end
		ParserReturnValue S_NoScope_LBrace_RBrace();

		ParserReturnValue S_NoScope_LBrace_Statement(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_NoScope_LBrace_StatementList(std::shared_ptr<StatementList>& list);

		ParserReturnValue S_NoScope_LBrace_StatementList_Statement(std::shared_ptr<StatementList>& list, std::shared_ptr<Statement>& statement);

		// compound_statement_no_new_scope end
		ParserReturnValue S_NoScope_LBrace_StatementList_RBrace(std::shared_ptr<StatementList>& list);

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

		// Special branch for statement that is parsed as part of selection statement
		ParserReturnValue S_Selection_Statement(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_Statement_ElseToken(std::shared_ptr<Statement>& statement);

		ParserReturnValue S_Statement_ElseToken_Statement(std::shared_ptr<Statement>& a, std::shared_ptr<Statement>& b);

		ParserReturnValue S_SelectionRestStatement(std::shared_ptr<SelectionRestStatement>& selectionRest);

		ParserReturnValue S_Statement(std::shared_ptr<Statement>& statement);

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

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_RBrace(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_Statement(std::shared_ptr<Expression>& expression,
			std::shared_ptr<Statement>& statement);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_StatementList(std::shared_ptr<Expression>& expression,
			std::shared_ptr<StatementList>& list);

		ParserReturnValue S_SwitchToken_LParen_Expression_RParen_LBrace_StatementList_Statement(std::shared_ptr<Expression>& expression,
			std::shared_ptr<StatementList>& list, std::shared_ptr<Statement>& statement);

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

		ParserReturnValue S_ForRestStatement(std::shared_ptr<ForRestStatement>& statement);

		ParserReturnValue S_WhileToken();

		ParserReturnValue S_WhileToken_LParen();

		ParserReturnValue S_WhileToken_LParen_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ConditionBuilder_FullType(std::shared_ptr<FullySpecifiedType>& fullType);

		ParserReturnValue S_ConditionBuilder_FullType_Identifier(std::shared_ptr<FullySpecifiedType>& fullType, const Token& id);
		
		ParserReturnValue S_ConditionBuilder_FullType_Identifier_Equal(std::shared_ptr<FullySpecifiedType>& fullType, const Token& id);

		ParserReturnValue S_ConditionBuilder_FullType_Identifier_Equal_AssignEx(std::shared_ptr<FullySpecifiedType>& fullType, const Token& id,
			std::shared_ptr<AssignmentExpression>& assignEx);

		ParserReturnValue S_ConditionBuilder_FullType_Identifier_Equal_Initializer(std::shared_ptr<FullySpecifiedType>& fullType, const Token& id,
			std::shared_ptr<Initializer>& initializer);

		ParserReturnValue S_WhileToken_LParen_Condition(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_WhileToken_LParen_Condition_RParen(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_WhileToken_LParen_Condition_RParen_StatementNoNewScope(std::shared_ptr<Condition>& condition,
			std::shared_ptr<StatementNoNewScope>& block);

		ParserReturnValue S_ForWhile_SimpleStatement(std::shared_ptr<SimpleStatement>& statement);

		ParserReturnValue S_ForWhile_CompoundStatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& statement);

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

		ParserReturnValue S_ForRest_Semicolon();

		ParserReturnValue S_ForRest_Semicolon_Expression(std::shared_ptr<Expression>& expression);

		ParserReturnValue S_ForRest_Condition(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_ForRest_Condition_Semicolon(std::shared_ptr<Condition>& condition);

		ParserReturnValue S_ForRest_Condition_Semicolon_Expression(std::shared_ptr<Condition>& condition, std::shared_ptr<Expression>& expression);

		ParserReturnValue S_IterationStatement(std::shared_ptr<IterationStatement>& statement);

		ParserReturnValue S_StatementNoNewScope(std::shared_ptr<StatementNoNewScope>& block);

		ParserReturnValue S_CompoundStatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& block);

		ParserReturnValue S_CompoundStatement(std::shared_ptr<CompoundStatement>& statement);

	};
}

#endif