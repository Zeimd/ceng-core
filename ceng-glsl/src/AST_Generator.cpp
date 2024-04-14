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

using namespace Ceng;


AST_Generator::~AST_Generator()
{

}

AST_Generator::AST_Generator(std::shared_ptr<SymbolDatabase>& symbolDatabase)
	: symbolDatabase(symbolDatabase)
{
	context.parent = &root;

	tempCounter.push_back(0);

	context.tempCounter = &tempCounter.back();
}

GLSL::AbstractSyntaxTree AST_Generator::GenerateTree(std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit)
{
	AST_Generator generator{ symbolDatabase };

	unit->AcceptVisitor(generator);
	
	return GLSL::AbstractSyntaxTree(generator.root);
}

AST_Generator::return_type AST_Generator::V_Expression(Expression& item)
{
	item.assignEx[0]->AcceptVisitor(*this);
	return 0;
}

AST_Generator::return_type AST_Generator::V_AssignmentExpression(AssignmentExpression& item)
{
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
			context.parent->children.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
				lhs, b
				));
			return 0;
		default:

			GLSL::BinaryOperator::value op = ConvertAssignmentOperator(item.op->operation);
			context.parent->children.push_back(std::make_shared< GLSL::AST_BinaryOperation>(
				lhs, a, op, b
				));
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
	Ceng::StringUtf8 name = "_temp";
	name += (*context.tempCounter)++;

	std::vector<GLSL::LayoutData> layout;

	context.parent->children.emplace_back(
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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_ConditionalOperation>
			(
				lhs,
				a,
				b,
				c
			)
		);
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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::logical_or,
				b
				)
		);
		
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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::logical_xor,
				b
				)
		);

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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::logical_and,
				b
				)
		);

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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::bitwise_or,
				b
				)
		);

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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::bitwise_xor,
				b
				)
		);

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
	if (item.full)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				GLSL::BinaryOperator::bitwise_and,
				b
				)
		);

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
	if (item.operation != EqualityOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				binaryOp,
				b
				)
		);

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
	if (item.operation != RelativeOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				binaryOp,
				b
				)
		);

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
	if (item.operation != ShiftOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				binaryOp,
				b
				)
		);

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
	if (item.operation != AdditiveOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				binaryOp,
				b
				)
		);

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
	if (item.operation != MultiplicativeOp::unassigned)
	{
		item.lhs->AcceptVisitor(*this);
		GLSL::Rvalue a = returnValue.value;
		GLSL::AST_Datatype resultType = returnValue.valueType;

		item.rhs->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.value;

		GLSL::Lvalue lhs = GenerateTemporary(resultType);

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

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_BinaryOperation>
			(
				lhs,
				a,
				binaryOp,
				b
				)
		);

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
			}
			else
			{
				GLSL::Lvalue lhs = a.ToLvalue();

				context.parent->children.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs,false
						)
				);
			}

			break;
		case UnaryExpressionType::dec_op:

			if (a.IsLiteral())
			{
				a.PreDec();
			}
			else
			{
				GLSL::Lvalue lhs = a.ToLvalue();

				context.parent->children.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs, true
						)
				);
			}

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
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(resultType);

			context.parent->children.emplace_back(
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

	switch (item.postfixType)
	{
	case PostfixType::primary_expression:
		item.primaryExpression->AcceptVisitor(*this);
		return 0;
	case PostfixType::array_index:
		return 0;
	case PostfixType::function_call:
		item.functionCall->AcceptVisitor(*this);
		return 0;
	case PostfixType::dec_op:

		item.postfixExpression->AcceptVisitor(*this);

		GLSL::Rvalue input = returnValue.value;
		GLSL::AST_Datatype inputType = returnValue.valueType;

		GLSL::Lvalue lhs = GenerateTemporary(inputType);

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_AssignmentOperation>(
				lhs, input
				)
		);

		lhs = input.ToLvalue();

		context.parent->children.emplace_back(
			std::make_shared<GLSL::AST_IncDecOperation>(
				lhs, true
				)
		);

		returnValue.value = lhs;
		returnValue.valueType = inputType;

		return 0;

	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_PrimaryExpression(PrimaryExpression& item)
{
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


AST_Generator::return_type AST_Generator::V_TranslationUnit(TranslationUnit& item)
{
	for (auto& x : item.items)
	{
		x->AcceptVisitor(*this);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_Declaration(Declaration& decl)
{
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


GLSL::ArrayIndex AST_Generator::GetArrayIndex(TypeSpecifier& item)
{
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

	GLSL::AST_Datatype returnType = GetReturnType(item);

	std::vector<GLSL::FunctionParameter> params;

	for (int k = 0; k < item.GetParamCount(); k++)
	{
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

	context.parent->children.push_back(output);

	return 0;
}


AST_Generator::return_type AST_Generator::V_InitDeclaratorList(InitDeclaratorList& item)
{
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
					true
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
					entry.name
					);
			}
		}
		else
		{
			// TODO: evaluate array size expression

			Ceng::UINT32 arraySize = 0;

			output = std::make_shared<GLSL::AST_VariableDeclaration>(
				item.invariant,
				layout,
				item.fullType->qualifier.storage.qualifier,
				item.fullType->qualifier.interpolation.interpolation,
				item.fullType->typeSpec.precision.precision,
				datatype,
				entry.name,
				arraySize
				);
		}

		context.parent->children.push_back(output);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_FunctionDefinition(FunctionDefinition& item)
{
	return 0;
}
