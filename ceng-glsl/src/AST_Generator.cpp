#include <ceng/GLSL/AST_VariableDeclaration.h>

#include "AST_Generator.h"

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

#include "Expression.h"
#include "ExpressionStatement.h"

#include "ForInitStatement.h"
#include "ForRestStatement.h"
#include "FunctionCall.h"
#include "FuncCallHeaderNoParams.h"
#include "FuncCallHeaderParams.h"
#include "FunctionCallGeneric.h"
#include "FunctionCallOrMethod.h"
#include "FunctionDeclarator.h"
#include "FunctionDefinition.h"
#include "FunctionPrototype.h"
#include "FunctionHeader.h"
#include "FunctionHeaderWithParams.h"

#include "IntegerExpression.h"
#include "InterpolationQualifier.h"
#include "InitDeclaratorList.h"
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
#include "StatementList.h"
#include "Statement.h"

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

#include <ceng/GLSL/AST_Datatype.h>
#include <ceng/GLSL/AST_FunctionPrototype.h>
#include <ceng/GLSL/AST_BinaryOperation.h>
#include <ceng/GLSL/AST_AssignmentOperation.h>
#include <ceng/GLSL/AST_ConditionalOperation.h>
#include <ceng/GLSL/AST_UnaryOperation.h>
#include <ceng/GLSL/AST_IncDecOperation.h>
#include <ceng/GLSL/AST_ReturnStatement.h>

using namespace Ceng;


AST_Generator::~AST_Generator()
{

}

AST_Generator::AST_Generator(std::shared_ptr<SymbolDatabase>& symbolDatabase)
	: symbolDatabase(symbolDatabase)
{
	contextStack.emplace_back(&root);
}

GLSL::AbstractSyntaxTree AST_Generator::GenerateTree(std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit)
{
	AST_Generator generator{ symbolDatabase };

	unit->AcceptVisitor(generator);
	
	return GLSL::AbstractSyntaxTree(generator.root);
}

AST_Generator::return_type AST_Generator::V_Expression(Expression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	item.assignEx[0]->AcceptVisitor(*this);
	return 0;
}

AST_Generator::return_type AST_Generator::V_AssignmentExpression(AssignmentExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.unaryEx->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;

		GLSL::Lvalue lhs = a.ToLvalue();

		item.assignEx->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		std::shared_ptr<GLSL::AST_BinaryOperation> output;

		switch (item.op->operation)
		{
		case AssignOpType::equal:
			CurrentContext().parent->children.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
				lhs, b
				));

			returnValue.value = lhs;
			returnValue.valueType = GetDatatype(lhs);
			return 0;
		default:

			GLSL::BinaryOperator::value op = ConvertAssignmentOperator(item.op->operation);

			CurrentContext().parent->children.push_back(std::make_shared< GLSL::AST_BinaryOperation>(
				lhs, a, op, b
				));

			returnValue.value = lhs;
			returnValue.valueType = GetDatatype(lhs);
		
			return 0;
		}

		
		
	}
	else
	{
		item.cond->AcceptVisitor(*this);
		return 0;
	}
}

GLSL::Lvalue AST_Generator::GenerateTemporary(GLSL::AST_Datatype& type)
{
	printf(__FUNCTION__);
	printf("\n");

	Ceng::StringUtf8 name = "_temp";
	name += CurrentContext().tempCounter++;

	printf("variable = %s\n", name.ToCString());

	std::vector<GLSL::LayoutData> layout;

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_VariableDeclaration>(
			false, 
			layout, 
			GLSL::StorageQualifierType::sq_const,
			GLSL::InterpolationQualifierType::unused,
			GLSL::PrecisionQualifierType::unassigned,
			type,
			name
	));

	return { name };
}

AST_Generator::return_type AST_Generator::V_ConditionalExpression(ConditionalExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.a->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;

		item.b->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.c->AcceptVisitor(*this);
		GLSL::Rvalue c = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_ConditionalOperation>
			(
				lhs,
				a,
				b,
				c
			)
		);

		returnValue.value = lhs;
		returnValue.valueType = resultType;

		return 0;
	}
	
	item.a->AcceptVisitor(*this);
	return 0;
}

GLSL::BinaryOperator::value AST_Generator::ConvertAssignmentOperator(AssignOpType::value op)
{
	switch (op)
	{
	case AssignOpType::add:
		return GLSL::BinaryOperator::add;
	case AssignOpType::sub:
		return GLSL::BinaryOperator::sub;
	case AssignOpType::mul:
		return GLSL::BinaryOperator::mul;
	case AssignOpType::div:
		return GLSL::BinaryOperator::div;
	case AssignOpType::mod:
		return GLSL::BinaryOperator::mod;
	case AssignOpType::left:
		return GLSL::BinaryOperator::left_shift;
	case AssignOpType::right:
		return GLSL::BinaryOperator::right_shift;
	case AssignOpType::and_op:
		return GLSL::BinaryOperator::bitwise_and;
	case AssignOpType::or_op:
		return GLSL::BinaryOperator::bitwise_or;
	case AssignOpType::xor_op:
		return GLSL::BinaryOperator::bitwise_xor;
	}
}

AST_Generator::return_type AST_Generator::V_LogicalOrExpression(LogicalOrExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::logical_or, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::logical_or,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}
		
		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_LogicalXorExpression(LogicalXorExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::logical_xor, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::logical_xor,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_LogicalAndExpression(LogicalAndExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::logical_and, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::logical_and,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_OrExpression(OrExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::bitwise_or, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::bitwise_or,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_XorExpression(XorExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::bitwise_xor, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::bitwise_xor,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_AndExpression(AndExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, GLSL::BinaryOperator::bitwise_and, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					GLSL::BinaryOperator::bitwise_and,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_EqualityExpression(EqualityExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != EqualityOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::BinaryOperator::value binaryOp;

		switch (item.operation)
		{
		case EqualityOp::equal:
			binaryOp = GLSL::BinaryOperator::equal;
			break;
		case EqualityOp::not_equal:
			binaryOp = GLSL::BinaryOperator::not_equal;
			break;
		}

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, binaryOp, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					binaryOp,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_RelationalExpression(RelationalExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != RelativeOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::BinaryOperator::value binaryOp;

		switch (item.operation)
		{
		case RelativeOp::less:
			binaryOp = GLSL::BinaryOperator::less;
			break;
		case RelativeOp::less_or_equal:
			binaryOp = GLSL::BinaryOperator::less_eq;
			break;
		case RelativeOp::greater:
			binaryOp = GLSL::BinaryOperator::greater;
			break;
		case RelativeOp::greater_or_equal:
			binaryOp = GLSL::BinaryOperator::greater_eq;
			break;
		}

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, binaryOp, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					binaryOp,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}
	

	return 0;
}

AST_Generator::return_type AST_Generator::V_ShiftExpression(ShiftExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != ShiftOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::BinaryOperator::value binaryOp;

		switch (item.operation)
		{
		case ShiftOp::left:
			binaryOp = GLSL::BinaryOperator::left_shift;
			break;
		case ShiftOp::right:
			binaryOp = GLSL::BinaryOperator::right_shift;
			break;
		}

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, binaryOp, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					binaryOp,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_AdditiveExpression(AdditiveExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != AdditiveOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::BinaryOperator::value binaryOp;

		switch (item.operation)
		{
		case AdditiveOp::add:
			binaryOp = GLSL::BinaryOperator::add;
			break;
		case AdditiveOp::sub:
			binaryOp = GLSL::BinaryOperator::sub;
			break;
		}

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, binaryOp, b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					binaryOp,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;


		}

		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_MultiplicativeExpression(MultiplicativeExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != MultiplicativeOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::BinaryOperator::value binaryOp;

		switch (item.operation)
		{
		case MultiplicativeOp::div:
			binaryOp = GLSL::BinaryOperator::div;
			break;
		case MultiplicativeOp::mul:
			binaryOp = GLSL::BinaryOperator::mul;
			break;
		case MultiplicativeOp::mod:
			binaryOp = GLSL::BinaryOperator::mod;
			break;
		}

		if (a.IsLiteral() && b.IsLiteral())
		{
			returnValue = LiteralBinaryOp(a, binaryOp,b);
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_BinaryOperation>
				(
					lhs,
					a,
					binaryOp,
					b
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;

			
		}
		return 0;
	}
	else
	{
		item.rhs->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_UnaryExpression(UnaryExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.unaryType != UnaryExpressionType::postfix_expression)
	{
		item.unaryExpression->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		GLSL::UnaryOperation::value op;

		switch (item.unaryType)
		{
		case UnaryExpressionType::inc_op:

			if (a.IsLiteral())
			{
				a.PreIncr();

				returnValue.value = a;
				returnValue.valueType = resultType;
			}
			else
			{
				GLSL::Lvalue lhs = a.ToLvalue();

				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs,false
						)
				);

				returnValue.value = lhs;
				returnValue.valueType = resultType;
			}		

			return 0;

			break;
		case UnaryExpressionType::dec_op:

			if (a.IsLiteral())
			{
				a.PreDec();


				returnValue.value = a;
				returnValue.valueType = resultType;
			}
			else
			{
				GLSL::Lvalue lhs = a.ToLvalue();

				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs, true
						)
				);

				returnValue.value = lhs;
				returnValue.valueType = resultType;
			}

			return 0;

			break;
		case UnaryExpressionType::logical_not:
			op = GLSL::UnaryOperation::logical_not;
			break;
		case UnaryExpressionType::negation:
			op = GLSL::UnaryOperation::negation;
			break;
		case UnaryExpressionType::bit_flip:
			op = GLSL::UnaryOperation::bitwise_not;
			break;
		}

		if (a.IsLiteral())
		{
			a.UnaryOp(op);

			returnValue.value = a;
			returnValue.valueType = resultType;
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_UnaryOperation>(
					lhs, op, a
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = resultType;
		}

		

	}
	else
	{
		item.postfixExpression->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_PostfixExpression(PostfixExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.postfixType)
	{
	case PostfixType::primary_expression:
		item.primaryExpression->AcceptVisitor(*this);
		return 0;
	case PostfixType::array_index:
		return 0;
	case PostfixType::field_select:
		return 0;
	case PostfixType::function_call:
		item.functionCall->AcceptVisitor(*this);
		return 0;
	case PostfixType::dec_op:
		{
			item.postfixExpression->AcceptVisitor(*this);

			GLSL::Rvalue input = returnValue.value;
			GLSL::AST_Datatype inputType = returnValue.valueType;

			GLSL::Lvalue lhs = GenerateTemporary(inputType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_AssignmentOperation>(
					lhs, input
					)
			);

			lhs = input.ToLvalue();

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_IncDecOperation>(
					lhs, true
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = inputType;

			return 0;
		}	
	case PostfixType::inc_op:
		{
			item.postfixExpression->AcceptVisitor(*this);

			GLSL::Rvalue input = returnValue.value;
			GLSL::AST_Datatype inputType = returnValue.valueType;

			GLSL::Lvalue lhs = GenerateTemporary(inputType);

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_AssignmentOperation>(
					lhs, input
					)
			);

			lhs = input.ToLvalue();

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_IncDecOperation>(
					lhs, false
					)
			);

			returnValue.value = lhs;
			returnValue.valueType = inputType;

			return 0;
		}
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_PrimaryExpression(PrimaryExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.valuetype)
	{
	case ExpressionType::identifier:
		returnValue.value = { item.name };
		returnValue.valueType = GetDatatype(item.name);
		break;
	case ExpressionType::bool_const:
		returnValue.value = { item.boolValue };
		returnValue.valueType = GLSL::AST_Datatype(GLSL::BasicType::ts_bool);
		break;
	case ExpressionType::int_const:
		returnValue.value = { item.intValue };
		returnValue.valueType = GLSL::AST_Datatype(GLSL::BasicType::ts_int);
		break;
	case ExpressionType::uint_const:
		returnValue.value = { item.uintValue };
		returnValue.valueType = GLSL::AST_Datatype(GLSL::BasicType::ts_uint);
		break;
	case ExpressionType::float_const:
		returnValue.value = { item.floatValue };
		returnValue.valueType = GLSL::AST_Datatype(GLSL::BasicType::ts_float);
		break;
	case ExpressionType::expression:
		item.expression->AcceptVisitor(*this);
		break;
	}

	return 0;
}

GeneratorReturn AST_Generator::LiteralBinaryOp(GLSL::Rvalue& a, GLSL::BinaryOperator::value op, GLSL::Rvalue& b)
{
	printf(__FUNCTION__);
	printf("\n");

	if (a.valueType == GLSL::RvalueType::variable || b.valueType == GLSL::RvalueType::variable)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
	}

	switch (op)
	{
	case GLSL::BinaryOperator::add:
		return LiteralAdd(a, b);
	case GLSL::BinaryOperator::sub:
		return LiteralSub(a, b);
	case GLSL::BinaryOperator::mul:
		return LiteralMul(a, b);
	case GLSL::BinaryOperator::mod:
		return LiteralMod(a, b);
	case GLSL::BinaryOperator::div:
		return LiteralDiv(a, b);
	case GLSL::BinaryOperator::left_shift:
		return LiteralLeftShift(a, b);
	case GLSL::BinaryOperator::right_shift:
		return LiteralLeftShift(a, b);
	case GLSL::BinaryOperator::bitwise_and:
		return LiteralBitwiseAnd(a, b);
	case GLSL::BinaryOperator::bitwise_or:
		return LiteralBitwiseOr(a, b);
	case GLSL::BinaryOperator::bitwise_xor:
		return LiteralBitwiseXor(a, b);
	case GLSL::BinaryOperator::logical_and:
		return LiteralLogicalAnd(a, b);
	case GLSL::BinaryOperator::logical_or:
		return LiteralLogicalOr(a, b);
	case GLSL::BinaryOperator::logical_xor:
		return LiteralLogicalXor(a, b);
	case GLSL::BinaryOperator::equal:
		return LiteralEqual(a, b);
	case GLSL::BinaryOperator::not_equal:
		return LiteralNotEqual(a, b);
	case GLSL::BinaryOperator::less:
		return LiteralLess(a, b);
	case GLSL::BinaryOperator::less_eq:
		return LiteralLessEqual(a, b);
	case GLSL::BinaryOperator::greater:
		return LiteralGreater(a, b);
	case GLSL::BinaryOperator::greater_eq:
		return LiteralGreaterEqual(a, b);
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralAdd(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) + std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) + std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) + std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) + std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) + std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) + std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralSub(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) - std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) - std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) - std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal - Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal - Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) - std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal - Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) - std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) - std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralMul(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	printf(__FUNCTION__);
	printf("\n");

	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) * std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) * std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) * std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal * Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal * Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) * std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal * Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) * std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) * std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralDiv(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	printf(__FUNCTION__);
	printf("\n");

	if (b.IsZero())
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
	}

	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) / std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) / std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) / std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal / Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal / Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) / std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal / Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) / std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) / std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralMod(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (b.IsZero())
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
	}

	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			/*
			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) / std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
			*/

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) % std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) % std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) + std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
			*/

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal % Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			/*
			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) + std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
			*/

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) % std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralLeftShift(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (!a.IsInteger() || !b.IsInteger())
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
	}

	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::int_literal:
			{
				Ceng::INT32 bVal = std::get<Ceng::INT32>(b.value);

				if (bVal < 0)
				{
					return { GLSL::Rvalue(),GLSL::AST_Datatype() };
				}

				return { GLSL::Rvalue(
					std::get<Ceng::INT32>(a.value) << bVal
				), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
			}
		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) << std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::uint_literal:

			Ceng::INT32 bVal = Ceng::INT32(std::get<Ceng::UINT32>(b.value));

			if (bVal < 0)
			{
				return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			}

			return { GLSL::Rvalue(
				aVal << bVal
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::int_literal:

			Ceng::INT32 bVal = std::get<Ceng::INT32>(b.value);

			if (bVal < 0)
			{
				return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			}

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) << bVal
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralRightShift(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (!a.IsInteger() || !b.IsInteger())
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
	}

	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::int_literal:
			{
				Ceng::INT32 bVal = std::get<Ceng::INT32>(b.value);

				if (bVal < 0)
				{
					return { GLSL::Rvalue(),GLSL::AST_Datatype() };
				}

				return { GLSL::Rvalue(
					std::get<Ceng::INT32>(a.value) >> bVal
				), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };

			}
		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) >> std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal + Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::uint_literal:

			Ceng::INT32 bVal = Ceng::INT32(std::get<Ceng::UINT32>(b.value));

			if (bVal < 0)
			{
				return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			}

			return { GLSL::Rvalue(
				aVal >> bVal
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::int_literal:

			Ceng::INT32 bVal = std::get<Ceng::INT32>(b.value);

			if (bVal < 0)
			{
				return { GLSL::Rvalue(),GLSL::AST_Datatype() };
			}

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) >> bVal
			), GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralBitwiseAnd(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralBitwiseOr(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralBitwiseXor(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralLogicalAnd(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(
				std::get<bool>(a.value) && std::get<bool>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) < std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralLogicalOr(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(
				std::get<bool>(a.value) || std::get<bool>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) < std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

bool AST_Generator::LogicalXor(bool a, bool b)
{
	return a != b;
}

GeneratorReturn AST_Generator::LiteralLogicalXor(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(
				LogicalXor(std::get<bool>(a.value),std::get<bool>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

			/*
			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) < std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
			*/
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		/*
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		/*
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
		*/
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralLess(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) < std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal < Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) < std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) < std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralLessEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) <= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) <= std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) <= std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal <= Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal <= Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) <= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal <= Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) <= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) <= std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralGreater(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) > std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) > std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) > std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal > Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal > Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) > std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal > Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) > std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) > std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralGreaterEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) >= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) >= std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) >= std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal >= Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal >= Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) >= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal >= Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) >= std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) >= std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(
				std::get<bool>(a.value) == std::get<bool>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) == std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) == std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) == std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal == Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal == Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) == std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal == Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) == std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) == std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

GeneratorReturn AST_Generator::LiteralNotEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	if (a.valueType == b.valueType)
	{
		switch (a.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(
				std::get<bool>(a.value) != std::get<bool>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::FLOAT32>(a.value) != std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::INT32>(a.value) != std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				std::get<Ceng::UINT32>(a.value) != std::get<Ceng::UINT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	if (a.valueType == GLSL::RvalueType::float_literal)
	{
		Ceng::FLOAT32 aVal = std::get<Ceng::FLOAT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				aVal != Ceng::FLOAT32(std::get<Ceng::INT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal != Ceng::FLOAT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::int_literal)
	{
		Ceng::INT32 aVal = std::get<Ceng::INT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) != std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::uint_literal:

			return { GLSL::Rvalue(
				aVal != Ceng::INT32(std::get<Ceng::UINT32>(b.value))
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}
	else if (a.valueType == GLSL::RvalueType::uint_literal)
	{
		Ceng::UINT32 aVal = std::get<Ceng::UINT32>(a.value);

		switch (b.valueType)
		{
		case GLSL::RvalueType::bool_literal:
			return { GLSL::Rvalue(),GLSL::AST_Datatype() };
		case GLSL::RvalueType::float_literal:

			return { GLSL::Rvalue(
				Ceng::FLOAT32(aVal) != std::get<Ceng::FLOAT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };

		case GLSL::RvalueType::int_literal:

			return { GLSL::Rvalue(
				Ceng::INT32(aVal) != std::get<Ceng::INT32>(b.value)
			), GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
		}
	}

	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}


AST_Generator::return_type AST_Generator::V_TranslationUnit(TranslationUnit& item)
{
	printf(__FUNCTION__);
	printf("\n");

	for (auto& x : item.items)
	{
		x->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_Declaration(Declaration& decl)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (decl.declarationType)
	{
	case DeclarationType::function_prototype:
		decl.prototype->AcceptVisitor(*this);
		break;
	case DeclarationType::init_list:
		decl.declList->AcceptVisitor(*this);
		break;
	case DeclarationType::type_qualifier:
		break;
	}

	return 0;
}

GLSL::AST_Datatype AST_Generator::GetDatatype(const Ceng::StringUtf8& name)
{
	Symbol* symbol = symbolDatabase->Find(name);

	if (symbol == nullptr)
	{
		return GLSL::AST_Datatype();
	}

	switch (symbol->symbolType)
	{
	case SymbolType::function_prototype:
		return GetReturnType(*symbol->decl->prototype);
	case SymbolType::variable:
		return GetDatatype(symbol->decl->declList->fullType);
	case SymbolType::function:
		return GetReturnType(*symbol->prototype);
	case SymbolType::function_parameter:
		return GetDatatype(symbol->param->typeSpec);
	case SymbolType::struct_declaration:		
		{
			GLSL::ArrayIndex index{ false };
			return GLSL::AST_Datatype(symbol->structSpec->name, index);
		}
		break;
	default:
		return GLSL::AST_Datatype();
	}
}

GLSL::AST_Datatype AST_Generator::GetDatatype(std::shared_ptr<FullySpecifiedType>& item)
{
	return GetDatatype(item->typeSpec);
}

GLSL::ArrayIndex AST_Generator::GetArrayIndex(std::shared_ptr<FullySpecifiedType>& item)
{
	return GetArrayIndex(item->typeSpec);
}

GLSL::AST_Datatype AST_Generator::GetDatatype(std::shared_ptr<TypeSpecifier>& item)
{
	return GetDatatype(*item);
}

GLSL::ArrayIndex AST_Generator::GetArrayIndex(std::shared_ptr<TypeSpecifier>& item)
{
	return GetArrayIndex(*item);
}

GLSL::AST_Datatype AST_Generator::GetDatatype(TypeSpecifier& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::ArrayIndex index = GetArrayIndex(item);

	switch (item.typeSpec.typeSpec->dataType)
	{
	case TypeSelector::basic_type:
		return GLSL::AST_Datatype(item.typeSpec.typeSpec->basicType, index);
	case TypeSelector::type_name:
		return GLSL::AST_Datatype(item.typeSpec.typeSpec->name, index);
	case TypeSelector::struct_specifier:
		{
			Ceng::StringUtf8 name = RegisterAnonymousStruct(item.typeSpec.typeSpec->structSpec);
			return GLSL::AST_Datatype(name, index);
		}
		break;
	}

	return GLSL::AST_Datatype();
}

GLSL::AST_Datatype AST_Generator::GetDatatype(const GLSL::VariableExpression& expression)
{
	GLSL::AST_Datatype previousType = GetDatatype(expression.chain[0].name);

	if (expression.chain[0].index.indexType != GLSL::ArrayIndexType::unused)
	{
		previousType = previousType.DiscardArray();
	}

	GLSL::AST_Datatype currentType;

	for (int k = 1; k < expression.chain.size(); k++)
	{
		currentType = GetMemberType(previousType, expression.chain[k].name);

		if (expression.chain[k].index.indexType != GLSL::ArrayIndexType::unused)
		{
			currentType = currentType.DiscardArray();
		}

		previousType = currentType;
	}

	return currentType;
}

GLSL::AST_Datatype AST_Generator::GetDatatype(const GLSL::Lvalue& lvalue)
{
	if (lvalue.valid == false)
	{
		return GLSL::AST_Datatype();
	}

	return GetDatatype(lvalue.expression);
}

GLSL::AST_Datatype AST_Generator::GetMemberType(const GLSL::AST_Datatype& baseType, const Ceng::StringUtf8& memberName)
{
	return GLSL::AST_Datatype();
}


GLSL::ArrayIndex AST_Generator::GetArrayIndex(TypeSpecifier& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.typeSpec.isArray)
	{
		if (item.typeSpec.elementExpression == nullptr)
		{
			return { true };
		}
		else
		{
			item.typeSpec.elementExpression->AcceptVisitor(*this);

			GLSL::Rvalue& out = returnValue.value;

			switch (out.valueType)
			{
			case GLSL::RvalueType::int_literal:
				return { std::get<Ceng::INT32>(out.value) };
			case GLSL::RvalueType::uint_literal:
				return { std::get<Ceng::UINT32>(out.value) };
			case GLSL::RvalueType::variable:
				return { std::get<GLSL::VariableExpression>(out.value)};
			default:

				//GLSL::VariableExpression expr{GLSL::FieldExpression(item.typeSpec.elementExpression->ToString(0))};

				return GLSL::VariableExpression();
			}			
		}
	}

	return { false };
}

GLSL::ArrayIndex AST_Generator::GetArrayIndex(std::shared_ptr<ParameterDeclarator>& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item->arraySize == nullptr)
	{
		return { false };
	}

	item->arraySize->AcceptVisitor(*this);

	GLSL::Rvalue& out = returnValue.value;

	switch (out.valueType)
	{
	case GLSL::RvalueType::int_literal:
		return { std::get<Ceng::INT32>(out.value) };
	case GLSL::RvalueType::uint_literal:
		return { std::get<Ceng::UINT32>(out.value) };
	case GLSL::RvalueType::variable:
		return { std::get<GLSL::VariableExpression>(out.value) };
	default:

		//GLSL::VariableExpression expr = { GLSL::FieldExpression(item->arraySize->ToString(0)) };

		return GLSL::VariableExpression();
	}
}

GLSL::AST_Datatype AST_Generator::GetReturnType(FunctionPrototype& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.GetParamCount() == 0)
	{
		return GetDatatype(item.decl->header->returnType);
	}
	
	return GetDatatype(item.decl->withParams->header->returnType);
}

Ceng::StringUtf8 AST_Generator::RegisterAnonymousStruct(std::shared_ptr<StructSpecifier>& structSpec)
{
	return "";
}

AST_Generator::return_type AST_Generator::V_FunctionPrototype(FunctionPrototype& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype returnType = GetReturnType(item);

	std::vector<GLSL::FunctionParameter> params;

	//printf("paramcount = %i\n", item.GetParamCount());

	for (int k = 0; k < item.GetParamCount(); k++)
	{
		//printf("param %i\n", k);

		//printf("typeonly = %i\n", item.GetParameter(k)->typeOnly);

		if (item.GetParameter(k)->typeOnly)
		{
			GLSL::AST_Datatype datatype = GetDatatype(item.GetParameter(k)->typeSpec);
			GLSL::ArrayIndex index = GetArrayIndex(item.GetParameter(k)->typeSpec);

			params.emplace_back(item.GetParameter(k)->IsConst(),
				item.GetParameter(k)->paramQ->qualifier,
				datatype
			);
		}
		else
		{
			GLSL::AST_Datatype datatype = GetDatatype(item.GetParameter(k)->decl->typeSpec);
			GLSL::ArrayIndex index = GetArrayIndex(item.GetParameter(k)->decl);
		
			params.emplace_back(item.GetParameter(k)->IsConst(),
				item.GetParameter(k)->paramQ->qualifier,
				datatype,
				item.GetParameter(k)->decl->name,
				index				
			);
		}
	}

	std::shared_ptr<GLSL::AST_FunctionPrototype> output;

	if (item.GetParamCount() > 0)
	{

		output = std::make_shared<GLSL::AST_FunctionPrototype>(
			returnType,
			item.GetName(),
			std::move(params)
			);


	}
	else
	{
		
		output = std::make_shared<GLSL::AST_FunctionPrototype>(
			returnType,
			item.GetName()
			);
			
	}

	CurrentContext().parent->children.push_back(output);

	return 0;
}

AST_Generator::return_type AST_Generator::V_FunctionDefinition(FunctionDefinition& item)
{
	printf(__FUNCTION__);
	printf("\n");

	item.prototype->AcceptVisitor(*this);

	NewestChildToContext();

	CurrentContext().parent->nodeType = GLSL::AST_NodeType::function_definition;

	item.body->AcceptVisitor(*this);

	PopContext();

	return 0;
}

AST_Generator::return_type AST_Generator::V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item)
{
	printf(__FUNCTION__);
	printf("\n");

	item.list->AcceptVisitor(*this);
	return 0;
}

AST_Generator::return_type AST_Generator::V_StatementList(StatementList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	for (auto& x : item.list)
	{
		x->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_Statement(Statement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.category)
	{
	case StatementCategory::compound:
		item.compoundStatement->AcceptVisitor(*this);
		break;
	case StatementCategory::simple:
		item.simpleStatement->AcceptVisitor(*this);
		break;
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_SimpleStatement(SimpleStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.statementType)
	{
	case StatementType::case_label:
		item.caseLabel->AcceptVisitor(*this);
		break;
	case StatementType::declaration:
		item.declaration->AcceptVisitor(*this);
		break;
	case StatementType::expression:
		item.expression->AcceptVisitor(*this);
		break;
	case StatementType::iteration:
		item.iteration->AcceptVisitor(*this);
		break;
	case StatementType::jump:
		item.jump->AcceptVisitor(*this);
		break;
	case StatementType::selection:
		item.selection->AcceptVisitor(*this);
		break;
	case StatementType::switch_statement:
		item.switchStatement->AcceptVisitor(*this);
		break;
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_DeclarationStatement(DeclarationStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	item.declaration->AcceptVisitor(*this);
	return 0;
}

AST_Generator::return_type AST_Generator::V_CaseLabel(CaseLabel& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	return 0;
}

AST_Generator::return_type AST_Generator::V_ExpressionStatement(ExpressionStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	item.ex->AcceptVisitor(*this);
	return 0;
}

AST_Generator::return_type AST_Generator::V_IterationStatement(IterationStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	return 0;
}

AST_Generator::return_type AST_Generator::V_JumpStatement(JumpStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	switch (item.jumpType)
	{
	case JumpType::returnStatement:
		item.returnExpression->AcceptVisitor(*this);

		GLSL::Rvalue result = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		// TODO: check against function return type

		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_ReturnStatement>(result)

		);

	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_SelectionStatement(SelectionStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	return 0;
}

AST_Generator::return_type AST_Generator::V_SwitchStatementList(SwitchStatementList& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	return 0;
}



AST_Generator::return_type AST_Generator::V_InitDeclaratorList(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	for (auto& entry : item.list)
	{
		std::vector<GLSL::LayoutData> layout;

		if (item.fullType->qualifier.layout != nullptr)
		{
			//printf("num layout = %i\n", item.fullType->qualifier.layout->list->list.size());

			for (auto& layoutItem : item.fullType->qualifier.layout->list->list)
			{
				layout.emplace_back(layoutItem->identifier, layoutItem->hasValue, layoutItem->value);
			}
		}	

		GLSL::AST_Datatype datatype{GetDatatype(item.fullType)};


		GLSL::Rvalue initializer;
		GLSL::AST_Datatype initializerType;

		if (entry.initializer != nullptr)
		{
			entry.initializer->AcceptVisitor(*this);

			initializer = returnValue.value;
			initializerType = returnValue.valueType;
		}

		std::shared_ptr<GLSL::AST_VariableDeclaration> output;

		if (entry.arraySizeExpression == nullptr)
		{
			if (entry.isArray)
			{
				output = std::make_shared<GLSL::AST_VariableDeclaration>(
					item.invariant,
					layout,
					item.fullType->qualifier.storage.qualifier,
					item.fullType->qualifier.interpolation.interpolation,
					item.fullType->typeSpec.precision.precision,
					datatype,
					entry.name,
					true,
					initializer
					);
			}
			else
			{
				output = std::make_shared<GLSL::AST_VariableDeclaration>(
					item.invariant,
					layout,
					item.fullType->qualifier.storage.qualifier,
					item.fullType->qualifier.interpolation.interpolation,
					item.fullType->typeSpec.precision.precision,
					datatype,
					entry.name,
					initializer
					);
			}
		}
		else
		{
			entry.arraySizeExpression->AcceptVisitor(*this);

			GLSL::Rvalue arraySize = returnValue.value;

			Ceng::UINT32 intSize = std::get<Ceng::UINT32>(arraySize.value);

			output = std::make_shared<GLSL::AST_VariableDeclaration>(
				item.invariant,
				layout,
				item.fullType->qualifier.storage.qualifier,
				item.fullType->qualifier.interpolation.interpolation,
				item.fullType->typeSpec.precision.precision,
				datatype,
				entry.name,
				intSize,
				initializer
				);
		}

		CurrentContext().parent->children.push_back(output);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_Initializer(Initializer& item)
{
	item.assignEx->AcceptVisitor(*this);
	return 0;
}

Context& AST_Generator::CurrentContext()
{
	return contextStack.back();
}

void AST_Generator::NewestChildToContext()
{
	contextStack.emplace_back(CurrentContext().parent->children.back().get());
}

void AST_Generator::StartContext(GLSL::IASTNode* parent)
{
	contextStack.emplace_back(parent);
}

void AST_Generator::PopContext()
{
	contextStack.pop_back();
}


