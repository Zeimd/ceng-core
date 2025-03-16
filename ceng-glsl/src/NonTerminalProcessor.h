#ifndef CENG_GLSL_NONTERMINAL_PROCESSOR_H
#define CENG_GLSL_NONTERMINAL_PROCESSOR_H

#include <memory>

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

	class NonTerminalProcessor
	{
	public:
		using return_type = void;

		virtual return_type V_AdditiveExpression(std::shared_ptr<AdditiveExpression>& item) = 0;
		virtual return_type V_AndExpression(std::shared_ptr<AndExpression>& item) = 0;
		virtual return_type V_AssignmentExpression(std::shared_ptr<AssignmentExpression>& item) = 0;
		virtual return_type V_AssignmentOperator(std::shared_ptr<AssignmentOperator>& item) = 0;

		virtual return_type V_CaseLabel(std::shared_ptr<CaseLabel>& item) = 0;
		virtual return_type V_CompoundStatement(std::shared_ptr<CompoundStatement>& item) = 0;
		virtual return_type V_CompoundStatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& item) = 0;
		virtual return_type V_Condition(std::shared_ptr<Condition>& item) = 0;
		virtual return_type V_ConditionalExpression(std::shared_ptr<ConditionalExpression>& item) = 0;
		virtual return_type V_ConditionOpt(std::shared_ptr<ConditionOpt>& item) = 0;
		virtual return_type V_ConstantExpression(std::shared_ptr<ConstantExpression>& item) = 0;

		virtual return_type V_Declaration(std::shared_ptr<Declaration>& item) = 0;
		virtual return_type V_DeclarationStatement(std::shared_ptr<DeclarationStatement>& item) = 0;

		virtual return_type V_EqualityExpression(std::shared_ptr<EqualityExpression>& item) = 0;
		virtual return_type V_Expression(std::shared_ptr<Expression>& item) = 0;

		virtual return_type V_ForInitStatement(std::shared_ptr<ForInitStatement>& item) = 0;
		virtual return_type V_ForRestStatement(std::shared_ptr<ForRestStatement>& item) = 0;
		virtual return_type V_FullySpecifiedType(std::shared_ptr<FullySpecifiedType>& item) = 0;
		virtual return_type V_FuncCallHeaderNoParams(std::shared_ptr<FuncCallHeaderNoParams>& item) = 0;
		virtual return_type V_FuncCallHeaderParams(std::shared_ptr<FuncCallHeaderParams>& item) = 0;
		virtual return_type V_FunctionCall(std::shared_ptr<FunctionCall>& item) = 0;
		virtual return_type V_FunctionCallGeneric(std::shared_ptr<FunctionCallGeneric>& item) = 0;
		virtual return_type V_FunctionCallHeader(std::shared_ptr<FunctionCallHeader>& item) = 0;
		virtual return_type V_FunctionCallOrMethod(std::shared_ptr<FunctionCallOrMethod>& item) = 0;
		virtual return_type V_FunctionDeclarator(std::shared_ptr<FunctionDeclarator>& item) = 0;
		virtual return_type V_FunctionDefinition(std::shared_ptr<FunctionDefinition>& item) = 0;
		virtual return_type V_FunctionHeader(std::shared_ptr<FunctionHeader>& item) = 0;
		virtual return_type V_FunctionHeaderWithParams(std::shared_ptr<FunctionHeaderWithParams>& item) = 0;
		virtual return_type V_FunctionIdentifier(std::shared_ptr<FunctionIdentifier>& item) = 0;
		virtual return_type V_FunctionPrototype(std::shared_ptr<FunctionPrototype>& item) = 0;

		virtual return_type V_InitDeclaratorList(std::shared_ptr<InitDeclaratorList>& item) = 0;
		virtual return_type V_Initializer(std::shared_ptr<Initializer>& item) = 0;
		virtual return_type V_IntegerExpression(std::shared_ptr<IntegerExpression>& item) = 0;
		virtual return_type V_InterpolationQualifier(std::shared_ptr<InterpolationQualifier>& item) = 0;
		virtual return_type V_IterationStatement(std::shared_ptr<IterationStatement>& item) = 0;

		virtual return_type V_JumpStatement(std::shared_ptr<JumpStatement>& item) = 0;

		virtual return_type V_LayoutQualifier(std::shared_ptr<LayoutQualifier>& item) = 0;
		virtual return_type V_LayoutQualifierId(std::shared_ptr<LayoutQualifierId>& item) = 0;
		virtual return_type V_LayoutQualifierIdList(std::shared_ptr<LayoutQualifierIdList>& item) = 0;
		virtual return_type V_LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& item) = 0;
		virtual return_type V_LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& item) = 0;
		virtual return_type V_LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& item) = 0;

		virtual return_type V_MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& item) = 0;

		virtual return_type V_OrExpression(std::shared_ptr<OrExpression>& item) = 0;

		virtual return_type V_ParameterDeclaration(std::shared_ptr<ParameterDeclaration>& item) = 0;
		virtual return_type V_ParameterDeclarator(std::shared_ptr<ParameterDeclarator>& item) = 0;
		virtual return_type V_ParameterQualifier(std::shared_ptr<ParameterQualifier>& item) = 0;
		virtual return_type V_ParameterTypeQualifier(std::shared_ptr<ParameterTypeQualifier>& item) = 0;
		virtual return_type V_PostfixExpression(std::shared_ptr<PostfixExpression>& item) = 0;
		virtual return_type V_PrecisionQualifier(std::shared_ptr<PrecisionQualifier>& item) = 0;
		virtual return_type V_PrimaryExpression(std::shared_ptr<PrimaryExpression>& item) = 0;

		virtual return_type V_RelationalExpression(std::shared_ptr<RelationalExpression>& item) = 0;

		virtual return_type V_SelectionRestStatement(std::shared_ptr<SelectionRestStatement>& item) = 0;
		virtual return_type V_SelectionStatement(std::shared_ptr<SelectionStatement>& item) = 0;
		virtual return_type V_ShiftExpression(std::shared_ptr<ShiftExpression>& item) = 0;
		virtual return_type V_SimpleStatement(std::shared_ptr<SimpleStatement>& item) = 0;
		virtual return_type V_SingleDeclaration(std::shared_ptr<SingleDeclaration>& item) = 0;
		virtual return_type V_Statement(std::shared_ptr<Statement>& item) = 0;
		virtual return_type V_StatementList(std::shared_ptr<StatementList>& item) = 0;
		virtual return_type V_StatementNoNewScope(std::shared_ptr<StatementNoNewScope>& item) = 0;
		virtual return_type V_StorageQualifier(std::shared_ptr<StorageQualifier>& item) = 0;
		virtual return_type V_StructDeclaration(std::shared_ptr<StructDeclaration>& item) = 0;
		virtual return_type V_StructDeclarationList(std::shared_ptr<StructDeclarationList>& item) = 0;
		virtual return_type V_StructStructDeclarator(std::shared_ptr<StructDeclarator>& item) = 0;
		virtual return_type V_StructStructDeclaratorList(std::shared_ptr<StructDeclaratorList>& item) = 0;
		virtual return_type V_StructSpecifier(std::shared_ptr<StructSpecifier>& item) = 0;
		virtual return_type V_SwitchStatement(std::shared_ptr<SwitchStatement>& item) = 0;
		virtual return_type V_SwitchStatementList(std::shared_ptr<SwitchStatementList>& item) = 0;

		virtual return_type V_TranslationUnit(std::shared_ptr<TranslationUnit>& item) = 0;
		virtual return_type V_TypeQualifier(std::shared_ptr<TypeQualifier>& item) = 0;
		virtual return_type V_TypeSpecifier(std::shared_ptr<TypeSpecifier>& item) = 0;
		virtual return_type V_TypeSpecifierNoArray(std::shared_ptr<TypeSpecifierNoArray>& item) = 0;
		virtual return_type V_TypeSpecifierNoPrec(std::shared_ptr<TypeSpecifierNoPrec>& item) = 0;

		virtual return_type V_UnaryExpression(std::shared_ptr<UnaryExpression>& item) = 0;
		virtual return_type V_XorExpression(std::shared_ptr<XorExpression>& item) = 0;

	};
}

#endif