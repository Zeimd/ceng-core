#ifndef CENG_NonTerminalVisitor_H
#define CENG_NonTerminalVisitor_H

#include <memory>

/*
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
*/

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

	class NonTerminalVisitor
	{
	public:

	public:

		virtual ~NonTerminalVisitor()
		{

		}

		using return_type = int;

		virtual return_type V_AdditiveExpression(AdditiveExpression& item)
		{
			return return_type();
		}
			
		virtual return_type V_AndExpression(AndExpression& item)
		{
			return return_type();
		}

		virtual return_type V_AssignmentExpression(AssignmentExpression& item)
		{
			return return_type();
		}

		virtual return_type V_AssignmentOperator(AssignmentOperator& item)
		{
			return return_type();
		}

		virtual return_type V_CaseLabel(CaseLabel& item)
		{
			return return_type();
		}

		virtual return_type V_CompoundStatement(CompoundStatement& item)
		{
			return return_type();
		}

		virtual return_type V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item)
		{
			return return_type();
		}

		virtual return_type V_Condition(Condition& item)
		{
			return return_type();
		}

		virtual return_type V_ConditionalExpression(ConditionalExpression& item)
		{
			return return_type();
		}

		virtual return_type V_ConditionOpt(ConditionOpt& item)
		{
			return return_type();
		}

		virtual return_type V_ConstantExpression(ConstantExpression& item)
		{
			return return_type();
		}

		virtual return_type V_Declaration(Declaration& item)
		{
			return return_type();
		}

		virtual return_type V_DeclarationStatement(DeclarationStatement& item)
		{
			return return_type();
		}

		virtual return_type V_EqualityExpression(EqualityExpression& item)
		{
			return return_type();
		}

		virtual return_type V_Expression(Expression& item)
		{
			return return_type();
		}

		virtual return_type V_ExpressionStatement(ExpressionStatement& item)
		{
			return return_type();
		}

		virtual return_type V_ForInitStatement(ForInitStatement& item)
		{
			return return_type();
		}

		virtual return_type V_ForRestStatement(ForRestStatement& item)
		{
			return return_type();
		}

		virtual return_type V_FullySpecifiedType(FullySpecifiedType& item)
		{
			return return_type();
		}

		virtual return_type V_FuncCallHeaderNoParams(FuncCallHeaderNoParams& item)
		{
			return return_type();
		}

		virtual return_type V_FuncCallHeaderParams(FuncCallHeaderParams& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionCall(FunctionCall& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionCallGeneric(FunctionCallGeneric& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionCallHeader(FunctionCallHeader& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionCallOrMethod(FunctionCallOrMethod& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionDeclarator(FunctionDeclarator& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionDefinition(FunctionDefinition& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionHeader(FunctionHeader& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionHeaderWithParams(FunctionHeaderWithParams& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionIdentifier(FunctionIdentifier& item)
		{
			return return_type();
		}

		virtual return_type V_FunctionPrototype(FunctionPrototype& item)
		{
			return return_type();
		}

		virtual return_type V_InitDeclaratorList(InitDeclaratorList& item)
		{
			return return_type();
		}

		virtual return_type V_Initializer(Initializer& item)
		{
			return return_type();
		}

		virtual return_type V_IntegerExpression(IntegerExpression& item)
		{
			return return_type();
		}

		virtual return_type V_InterpolationQualifier(InterpolationQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_IterationStatement(IterationStatement& item)
		{
			return return_type();
		}

		virtual return_type V_JumpStatement(JumpStatement& item)
		{
			return return_type();
		}

		virtual return_type V_LayoutQualifier(LayoutQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_LayoutQualifierId(LayoutQualifierId& item)
		{
			return return_type();
		}

		virtual return_type V_LayoutQualifierIdList(LayoutQualifierIdList& item)
		{
			return return_type();
		}

		virtual return_type V_LogicalAndExpression(LogicalAndExpression& item)
		{
			return return_type();
		}

		virtual return_type V_LogicalOrExpression(LogicalOrExpression& item)
		{
			return return_type();
		}

		virtual return_type V_LogicalXorExpression(LogicalXorExpression& item)
		{
			return return_type();
		}

		virtual return_type V_MultiplicativeExpression(MultiplicativeExpression& item)
		{
			return return_type();
		}

		virtual return_type V_OrExpression(OrExpression& item)
		{
			return return_type();
		}

		virtual return_type V_ParameterDeclaration(ParameterDeclaration& item)
		{
			return return_type();
		}

		virtual return_type V_ParameterDeclarator(ParameterDeclarator& item)
		{
			return return_type();
		}

		virtual return_type V_ParameterQualifier(ParameterQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_ParameterTypeQualifier(ParameterTypeQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_PostfixExpression(PostfixExpression& item)
		{
			return return_type();
		}

		virtual return_type V_PrecisionQualifier(PrecisionQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_PrimaryExpression(PrimaryExpression& item)
		{
			return return_type();
		}

		virtual return_type V_RelationalExpression(RelationalExpression& item)
		{
			return return_type();
		}

		virtual return_type V_SelectionRestStatement(SelectionRestStatement& item)
		{
			return return_type();
		}

		virtual return_type V_SelectionStatement(SelectionStatement& item)
		{
			return return_type();
		}

		virtual return_type V_ShiftExpression(ShiftExpression& item)
		{
			return return_type();
		}

		virtual return_type V_SimpleStatement(SimpleStatement& item)
		{
			return return_type();
		}

		virtual return_type V_SingleDeclaration(SingleDeclaration& item)
		{
			return return_type();
		}

		virtual return_type V_Statement(Statement& item)
		{
			return return_type();
		}

		virtual return_type V_StatementList(StatementList& item)
		{
			return return_type();
		}

		virtual return_type V_StatementNoNewScope(StatementNoNewScope& item)
		{
			return return_type();
		}

		virtual return_type V_StorageQualifier(StorageQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_StructDeclaration(StructDeclaration& item)
		{
			return return_type();
		}

		virtual return_type V_StructDeclarationList(StructDeclarationList& item)
		{
			return return_type();
		}

		virtual return_type V_StructDeclarator(StructDeclarator& item)
		{
			return return_type();
		}

		virtual return_type V_StructDeclaratorList(StructDeclaratorList& item)
		{
			return return_type();
		}

		virtual return_type V_StructSpecifier(StructSpecifier& item)
		{
			return return_type();
		}

		virtual return_type V_SwitchStatement(SwitchStatement& item)
		{
			return return_type();
		}

		virtual return_type V_SwitchStatementList(SwitchStatementList& item)
		{
			return return_type();
		}

		virtual return_type V_TranslationUnit(TranslationUnit& item)
		{
			return return_type();
		}

		virtual return_type V_TypeQualifier(TypeQualifier& item)
		{
			return return_type();
		}

		virtual return_type V_TypeSpecifier(TypeSpecifier& item)
		{
			return return_type();
		}

		virtual return_type V_TypeSpecifierNoArray(TypeSpecifierNoArray& item)
		{
			return return_type();
		}

		virtual return_type V_TypeSpecifierNoPrec(TypeSpecifierNoPrec& item)
		{
			return return_type();
		}

		virtual return_type V_UnaryExpression(UnaryExpression& item)
		{
			return return_type();
		}

		virtual return_type V_UnaryOperator(UnaryOperator& item)
		{
			return return_type();
		}

		virtual return_type V_XorExpression(XorExpression& item)
		{
			return return_type();
		}
	};
}

#endif