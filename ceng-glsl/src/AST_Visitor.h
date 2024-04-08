#ifndef CENG_AST_VISITOR_H
#define CENG_AST_VISITOR_H

#include <memory>

#include "AdditiveExpression.h"
#include "AndExpression.h"
#include "AssignmentExpression.h"
#include "CaseLabel.h"
#include "CompoundStatement.h"
#include "CompoundStatementNoNewScope.h"
#include "Condition.h"
#include "ConditionOpt.h"
#include "ConstantExpression.h"
#include "Declaration.h"
#include "DeclarationStatement.h"
#include "ForInitStatement.h"
#include "ForRestStatement.h"
#include "FuncCallHeaderNoParams.h"
#include "FuncCallHeaderParams.h"
#include "FunctionCallGeneric.h"
#include "FunctionCallOrMethod.h"
#include "FunctionDeclarator.h"
#include "FunctionDefinition.h"
#include "FunctionPrototype.h"

#include "IntegerExpression.h"
#include "InterpolationQualifier.h"

#include "IterationStatement.h"
#include "JumpStatement.h"

#include "LayoutQualifier.h"
#include "LayoutQualifierId.h"
#include "LayoutQualifierIdList.h"

#include "LogicalAndExpression.h"
#include "LogicalXorExpression.h"
#include "LogicalOrExpression.h"

#include "ParameterDeclaration.h"
#include "ParameterDeclarator.h"
#include "ParameterQualifier.h"
#include "ParameterTypeQualifier.h"
#include "SelectionRestStatement.h"
#include "SelectionStatement.h"
#include "SimpleStatement.h"
#include "ShiftExpression.h"

#include "StorageQualifier.h"
#include "StructDeclaration.h"
#include "StructDeclarationList.h"
#include "StructDeclarator.h"
#include "StructDeclaratorList.h"
#include "StructSpecifier.h"

#include "SingleDeclaration.h"
#include "SwitchStatement.h"
#include "SwitchStatementList.h"

#include "TranslationUnit.h"

#include "TypeQualifier.h"
#include "TypeSpecifier.h"
#include "TypeSpecifierNoArray.h"
#include "TypeSpecifierNoPrecision.h"

namespace Ceng
{
	class AST_Visitor
	{
	public:

	public:

		using return_type = void;

		virtual return_type V_AdditiveExpression(AdditiveExpression& item) = 0;
		virtual return_type V_AndExpression(AndExpression& item) = 0;
		virtual return_type V_AssignmentExpression(AssignmentExpression& item) = 0;
		virtual return_type V_AssignmentOperator(AssignmentOperator& item) = 0;

		virtual return_type V_CaseLabel(CaseLabel& item) = 0;
		virtual return_type V_CompoundStatement(CompoundStatement& item) = 0;
		virtual return_type V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item) = 0;
		virtual return_type V_Condition(Condition& item) = 0;
		virtual return_type V_ConditionalExpression(ConditionalExpression& item) = 0;
		virtual return_type V_ConditionOpt(ConditionOpt& item) = 0;
		virtual return_type V_ConstantExpression(ConstantExpression& item) = 0;

		virtual return_type V_Declaration(Declaration& item) = 0;
		virtual return_type V_DeclarationStatement(DeclarationStatement& item) = 0;

		virtual return_type V_EqualityExpression(EqualityExpression& item) = 0;
		virtual return_type V_Expression(Expression& item) = 0;
		virtual return_type V_ExpressionStatement(ExpressionStatement& item) = 0;

		virtual return_type V_ForInitStatement(ForInitStatement& item) = 0;
		virtual return_type V_ForRestStatement(ForRestStatement& item) = 0;
		virtual return_type V_FullySpecifiedType(FullySpecifiedType& item) = 0;
		virtual return_type V_FuncCallHeaderNoParams(FuncCallHeaderNoParams& item) = 0;
		virtual return_type V_FuncCallHeaderParams(FuncCallHeaderParams& item) = 0;
		virtual return_type V_FunctionCall(FunctionCall& item) = 0;
		virtual return_type V_FunctionCallGeneric(FunctionCallGeneric& item) = 0;
		virtual return_type V_FunctionCallHeader(FunctionCallHeader& item) = 0;
		virtual return_type V_FunctionCallOrMethod(FunctionCallOrMethod& item) = 0;
		virtual return_type V_FunctionDeclarator(FunctionDeclarator& item) = 0;
		virtual return_type V_FunctionDefinition(FunctionDefinition& item) = 0;
		virtual return_type V_FunctionHeader(FunctionHeader& item) = 0;
		virtual return_type V_FunctionHeaderWithParams(FunctionHeaderWithParams& item) = 0;
		virtual return_type V_FunctionIdentifier(FunctionIdentifier& item) = 0;
		virtual return_type V_FunctionPrototype(FunctionPrototype& item) = 0;

		virtual return_type V_InitDeclaratorList(InitDeclaratorList& item) = 0;
		virtual return_type V_Initializer(Initializer& item) = 0;
		virtual return_type V_IntegerExpression(IntegerExpression& item) = 0;
		virtual return_type V_InterpolationQualifier(InterpolationQualifier& item) = 0;
		virtual return_type V_IterationStatement(IterationStatement& item) = 0;

		virtual return_type V_JumpStatement(JumpStatement& item) = 0;

		virtual return_type V_LayoutQualifier(LayoutQualifier& item) = 0;
		virtual return_type V_LayoutQualifierId(LayoutQualifierId& item) = 0;
		virtual return_type V_LayoutQualifierIdList(LayoutQualifierIdList& item) = 0;
		virtual return_type V_LogicalAndExpression(LogicalAndExpression& item) = 0;
		virtual return_type V_LogicalOrExpression(LogicalOrExpression& item) = 0;
		virtual return_type V_LogicalXorExpression(LogicalXorExpression& item) = 0;

		virtual return_type V_MultiplicativeExpression(MultiplicativeExpression& item) = 0;

		virtual return_type V_OrExpression(OrExpression& item) = 0;

		virtual return_type V_ParameterDeclaration(ParameterDeclaration& item) = 0;
		virtual return_type V_ParameterDeclarator(ParameterDeclarator& item) = 0;
		virtual return_type V_ParameterQualifier(ParameterQualifier& item) = 0;
		virtual return_type V_ParameterTypeQualifier(ParameterTypeQualifier& item) = 0;
		virtual return_type V_PostfixExpression(PostfixExpression& item) = 0;
		virtual return_type V_PrecisionQualifier(PrecisionQualifier& item) = 0;
		virtual return_type V_PrimaryExpression(PrimaryExpression& item) = 0;

		virtual return_type V_RelationalExpression(RelationalExpression& item) = 0;

		virtual return_type V_SelectionRestStatement(SelectionRestStatement& item) = 0;
		virtual return_type V_SelectionStatement(SelectionStatement& item) = 0;
		virtual return_type V_ShiftExpression(ShiftExpression& item) = 0;
		virtual return_type V_SimpleStatement(SimpleStatement& item) = 0;
		virtual return_type V_SingleDeclaration(SingleDeclaration& item) = 0;
		virtual return_type V_Statement(Statement& item) = 0;
		virtual return_type V_StatementList(StatementList& item) = 0;
		virtual return_type V_StatementNoNewScope(StatementNoNewScope& item) = 0;
		virtual return_type V_StorageQualifier(StorageQualifier& item) = 0;
		virtual return_type V_StructDeclaration(StructDeclaration& item) = 0;
		virtual return_type V_StructDeclarationList(StructDeclarationList& item) = 0;
		virtual return_type V_StructDeclarator(StructDeclarator& item) = 0;
		virtual return_type V_StructDeclaratorList(StructDeclaratorList& item) = 0;
		virtual return_type V_StructSpecifier(StructSpecifier& item) = 0;
		virtual return_type V_SwitchStatement(SwitchStatement& item) = 0;
		virtual return_type V_SwitchStatementList(SwitchStatementList& item) = 0;

		virtual return_type V_TranslationUnit(TranslationUnit& item) = 0;
		virtual return_type V_TypeQualifier(TypeQualifier& item) = 0;
		virtual return_type V_TypeSpecifier(TypeSpecifier& item) = 0;
		virtual return_type V_TypeSpecifierNoArray(TypeSpecifierNoArray& item) = 0;
		virtual return_type V_TypeSpecifierNoPrec(TypeSpecifierNoPrec& item) = 0;

		virtual return_type V_UnaryExpression(UnaryExpression& item) = 0;
		virtual return_type V_UnaryOperator(UnaryOperator& item) = 0;
		virtual return_type V_XorExpression(XorExpression& item) = 0;


		/*
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
		*/



	};
}

#endif