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
#include <ceng/GLSL/AST_FunctionCall.h>
#include <ceng/GLSL/AST_Scope.h>
#include <ceng/GLSL/AST_IfBlock.h>
#include <ceng/GLSL/AST_SwitchBlock.h>
#include <ceng/GLSL/AST_CaseLabel.h>
#include <ceng/GLSL/AST_Break.h>
#include <ceng/GLSL/AST_WhileLoop.h>
#include <ceng/GLSL/AST_EmptyNode.h>
#include <ceng/GLSL/AST_NormalVariable.h>
#include <ceng/GLSL/AST_InvariantStatement.h>
#include <ceng/GLSL/AST_DefaultPrecision.h>

#include <ceng/GLSL/AST_GeometryShaderIn.h>
#include <ceng/GLSL/AST_GeometryShaderOut.h>

#include <ceng/GLSL/AST_VertexShaderIn.h>

#include "OperatorDatabase.h"

using namespace Ceng;


AST_Generator::~AST_Generator()
{

}

AST_Generator::AST_Generator(GLSL::ShaderType::value shader, std::shared_ptr<SymbolDatabase>& symbolDatabase)
	: shader(shader), symbolDatabase(symbolDatabase)
{
	contextStack.emplace_back(&root);
}

GLSL::AbstractSyntaxTree AST_Generator::GenerateTree(GLSL::ShaderType::value shader, std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit)
{
	AST_Generator generator{shader, symbolDatabase };

	unit->AcceptVisitor(generator);
	
	return GLSL::AbstractSyntaxTree(generator.root);
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

void AST_Generator::AddStatementContext(const StatementContext& statementContext)
{
	for (auto& x : statementContext.prefixOperations)
	{
		CurrentContext().parent->children.push_back(x);
	}

	for (auto& x : statementContext.normalOperations)
	{
		CurrentContext().parent->children.push_back(x);
	}

	for (auto& x : statementContext.postfixOperations)
	{
		CurrentContext().parent->children.push_back(x);
	}
}

void AST_Generator::AddParenthesisContext(StatementContext& statementContext, StatementContext& parenthesis)
{
	for (auto& x : parenthesis.prefixOperations)
	{
		statementContext.prefixOperations.push_back(x);
	}

	for (auto& x : parenthesis.normalOperations)
	{
		statementContext.prefixOperations.push_back(x);
	}

	for (auto& x : parenthesis.postfixOperations)
	{
		statementContext.postfixOperations.push_back(x);
	}
}

/*
GLSL::Lvalue AST_Generator::GenerateTemporary(GLSL::AST_Datatype& type)
{
	printf(__FUNCTION__);
	printf("\n");

	Ceng::StringUtf8 name = "@temp";
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
*/

GLSL::PrecisionQualifierType::value AST_Generator::GetDefaultPrecision(const GLSL::AST_Datatype& datatype)
{
	// TODO

	return GLSL::PrecisionQualifierType::unassigned;
}

GLSL::Lvalue AST_Generator::GenerateTemporary(StatementContext& statementContext, GLSL::AST_Datatype& type)
{
	printf(__FUNCTION__);
	printf("\n");

	Ceng::StringUtf8 name = "@temp";
	name += CurrentContext().tempCounter++;

	printf("variable = %s\n", name.ToCString());

	GLSL::PrecisionQualifierType::value precision = GetDefaultPrecision(type);

	GLSL::SimpleDeclaration decl
	{
		true,
		precision,
		type,
		name
	};

	return { decl };

	/*
	std::vector<GLSL::LayoutData> layout;

	statementContext.normalOperations.emplace_back(
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
	*/
}

GLSL::AST_Datatype AST_Generator::GetDatatype(const SymbolLink& link)
{
	if (link.Valid() == false)
	{
		return GLSL::AST_Datatype();
	}

	Symbol* symbol = link.Get();

	if (symbol->undefined)
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
		return GetDatatype(symbol->param->GetType());
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

GLSL::AST_Datatype AST_Generator::GetDatatype(const Ceng::StringUtf8& name)
{
	SymbolLink link = symbolDatabase->Find(name);

	if (!link.Valid())
	{
		return GLSL::AST_Datatype();
	}

	return GetDatatype(link);
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

	switch (item.arrayType.baseType->dataType)
	{
	case TypeSelector::basic_type:
		return GLSL::AST_Datatype(item.arrayType.baseType->basicType, index);
	case TypeSelector::type_name:
		return GLSL::AST_Datatype(*item.arrayType.baseType->link.Get()->Name(), index);
	case TypeSelector::struct_specifier:
	{
		Ceng::StringUtf8 name = RegisterAnonymousStruct(item.arrayType.baseType->structSpec);
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
	switch (lvalue.valueType)
	{
	case GLSL::LvalueType::invalid:
		return GLSL::AST_Datatype();
	case GLSL::LvalueType::expression:
		return GetDatatype(std::get<GLSL::VariableExpression>(lvalue.value));
	case GLSL::LvalueType::declaration:
		return std::get<GLSL::SimpleDeclaration>(lvalue.value).datatype;
	}	

	return GLSL::AST_Datatype();
}

GLSL::AST_Datatype AST_Generator::GetMemberType(const GLSL::AST_Datatype& baseType, const Ceng::StringUtf8& memberName)
{
	return GLSL::AST_Datatype();
}


GLSL::ArrayIndex AST_Generator::GetArrayIndex(TypeSpecifier& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.arrayType.isArray)
	{
		if (item.arrayType.elementExpression == nullptr)
		{
			return { true };
		}
		else
		{
			StatementContext statementContext;

			ExpressionReturn out = Handler_Expression(nullptr, statementContext, *item.arrayType.elementExpression);

			AddStatementContext(statementContext);

			GLSL::Rvalue& rvalue = out.value;

			switch (rvalue.valueType)
			{
			case GLSL::RvalueType::int_literal:
				return { std::get<Ceng::INT32>(rvalue.value) };
			case GLSL::RvalueType::uint_literal:
				return { std::get<Ceng::UINT32>(rvalue.value) };
			case GLSL::RvalueType::variable:
				return { std::get<GLSL::VariableExpression>(rvalue.value) };
			default:

				//GLSL::VariableExpression expr{GLSL::FieldExpression(item.typeSpec.elementExpression->ToString(0))};

				return GLSL::VariableExpression();
			}
		}
	}

	return { false };
}

GLSL::ArrayIndex AST_Generator::GetArrayIndex(DeclarationData& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.isArray)
	{
		if (item.arraySizeExpression == nullptr)
		{
			return { true };
		}

		StatementContext statementContext;

		ExpressionReturn out = Handler_Expression(nullptr, statementContext, *item.arraySizeExpression);

		AddStatementContext(statementContext);

		GLSL::Rvalue& rvalue = out.value;

		switch (rvalue.valueType)
		{
		case GLSL::RvalueType::int_literal:
			return { std::get<Ceng::INT32>(rvalue.value) };
		case GLSL::RvalueType::uint_literal:
			return { std::get<Ceng::UINT32>(rvalue.value) };
		case GLSL::RvalueType::variable:
			return { std::get<GLSL::VariableExpression>(rvalue.value) };
		default:

			//GLSL::VariableExpression expr{GLSL::FieldExpression(item.typeSpec.elementExpression->ToString(0))};

			return GLSL::VariableExpression();
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

	StatementContext statementContext;

	ExpressionReturn result = Handler_Expression(nullptr, statementContext , *item->arraySize);

	AddStatementContext(statementContext);

	//item->arraySize->AcceptVisitor(*this);

	GLSL::Rvalue& out = result.value;

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

ExpressionReturn AST_Generator::GetImplicitConversion(GLSL::Lvalue* destination, StatementContext& statementContext, GLSL::Rvalue& in, 
	GLSL::BasicType::value sourceType, GLSL::BasicType::value destType)
{
	printf(__FUNCTION__);
	printf("\n");

	ExpressionReturn ret;

	if (in.IsLiteral())
	{
		return ConstructFromLiteral(destination, statementContext, destType, in);
	}

	std::vector<GLSL::Rvalue> callParams;
	std::vector<GLSL::AST_Datatype> signatureTypes;

	callParams.push_back(in);
	signatureTypes.push_back(sourceType);

	SymbolLink link = symbolDatabase->FindFunction(GLSL::BasicType::ToString(destType));

	GLSL::AST_Datatype returnType = destType;

	if (destination == nullptr)
	{
		GLSL::Lvalue lhs = GenerateTemporary(statementContext, returnType);

		auto sharedLink = std::make_shared<SymbolLink>(link);

		statementContext.normalOperations.emplace_back(
			std::make_shared<GLSL::AST_FunctionCall>(lhs, sharedLink, std::move(callParams))
		);

		return { lhs, returnType };
	}
	else
	{
		auto sharedLink = std::make_shared<SymbolLink>(link);

		statementContext.normalOperations.emplace_back(
			std::make_shared<GLSL::AST_FunctionCall>(*destination, sharedLink, std::move(callParams))
		);

		return { *destination, returnType };
	}
}

ExpressionReturn AST_Generator::ConstructFromLiteral(GLSL::Lvalue* destination, StatementContext& statementContext, GLSL::BasicType::value destType, GLSL::Rvalue& in)
{
	switch (destType)
	{
	case GLSL::BasicType::ts_bool:
		return { in.ToBool() };
	case GLSL::BasicType::ts_int:		
		return { in.ToInt() };
	case GLSL::BasicType::ts_uint:
		return { in.ToUint() };
	case GLSL::BasicType::ts_float:
		return { in.ToFloat() };
	}

	return ExpressionReturn();
}

ExpressionReturn AST_Generator::Handler_Expression(GLSL::Lvalue* destination, StatementContext& statementContext, Expression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	return Handler_AssignmentExpression(destination, statementContext, *item.assignEx[0]);
}

ExpressionReturn AST_Generator::Handler_Assignment(StatementContext& statementContext, GLSL::Lvalue& lhs, ExpressionReturn& rhs)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype& destType = std::get<GLSL::SimpleDeclaration>(lhs.value).datatype;

	GLSL::OperationInfo info = GLSL::operatorDatabase.CheckAssignment(destType.basicType, rhs.valueType.basicType);

	switch (info.status)
	{
	case GLSL::OperationValidity::invalid:
		break;
	case GLSL::OperationValidity::valid:
		statementContext.normalOperations.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
			lhs, rhs.value
			));
		break;
	case GLSL::OperationValidity::right_promotion:

		ExpressionReturn c = GetImplicitConversion(&lhs, statementContext, rhs.value, rhs.valueType.basicType, destType.basicType);

		if (lhs != c.value)
		{
			statementContext.normalOperations.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
				lhs, c.value
				));
		}

		break;
	}

	return { lhs, destType };
}

ExpressionReturn AST_Generator::Handler_AssignmentExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AssignmentExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		ExpressionReturn a = Handler_UnaryExpression(nullptr, statementContext, *item.unaryEx);

		GLSL::Lvalue lhs = a.value.ToLvalue();

		if (IsAssignable(lhs) == false)
		{
			// TODO
		}

		ExpressionReturn b = Handler_AssignmentExpression(&lhs, statementContext , *item.assignEx);

		std::shared_ptr<GLSL::AST_BinaryOperation> output;

		switch (item.op->operation)
		{
		case AssignOpType::equal:

			if (lhs != b.value)
			{
				GLSL::OperationInfo info = GLSL::operatorDatabase.CheckAssignment(a.valueType.basicType, b.valueType.basicType);

				switch (info.status)
				{
				case GLSL::OperationValidity::invalid:
					break;
				case GLSL::OperationValidity::valid:
					statementContext.normalOperations.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
						lhs, b.value
						));
					break;
				case GLSL::OperationValidity::right_promotion:

					ExpressionReturn c = GetImplicitConversion(&lhs, statementContext, b.value, b.valueType.basicType, a.valueType.basicType);

					if (lhs != c.value)
					{
						statementContext.normalOperations.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
							lhs, c.value
							));
					}
					
					break;
				}
			}
			return { lhs, GetDatatype(lhs) };
		default:

			GLSL::BinaryOperator::value op = ConvertAssignmentOperator(item.op->operation);

			statementContext.normalOperations.push_back(std::make_shared< GLSL::AST_BinaryOperation>(
				lhs, a.value, op, b.value
				));

			return { lhs, GetDatatype(lhs) };
		}
	}

	return Handler_ConditionalExpression(destination, statementContext, *item.cond);
}

ExpressionReturn AST_Generator::Handler_ConditionalExpression(GLSL::Lvalue* destination, StatementContext& statementContext, ConditionalExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		ExpressionReturn a = Handler_LogicalOrExpression(nullptr, statementContext , *item.a);
			
		ExpressionReturn b = Handler_Expression(nullptr, statementContext , *item.b);
		
		ExpressionReturn c = Handler_AssignmentExpression(nullptr, statementContext, *item.c);

		if (destination == nullptr)
		{
			GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_ConditionalOperation>
				(
					lhs,
					a.value,
					b.value,
					c.value
					)
			);

			return { lhs, a.valueType };
		}
		else
		{
			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_ConditionalOperation>
				(
					*destination,
					a.value,
					b.value,
					c.value
					)
			);

			return { *destination, a.valueType };
		}
	}
	
	return Handler_LogicalOrExpression(destination, statementContext , *item.a);
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

ExpressionReturn AST_Generator::Handler_LogicalOrExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalOrExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype resultType = GLSL::BasicType::ts_bool;

	if (item.full)
	{
		ExpressionReturn a = Handler_LogicalOrExpression(nullptr, statementContext ,*item.lhs);
		
		ExpressionReturn b = Handler_LogicalXorExpression(nullptr, statementContext , *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::logical_or, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, resultType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::logical_or,
						b.value
						)
				);

				return { lhs, resultType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::logical_or,
						b.value
						)
				);

				return { *destination, resultType };
			}
		}
	}
	
	return Handler_LogicalXorExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_LogicalXorExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalXorExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype resultType = GLSL::BasicType::ts_bool;

	if (item.full)
	{
		ExpressionReturn a = Handler_LogicalXorExpression(nullptr, statementContext, *item.lhs);

		ExpressionReturn b = Handler_LogicalAndExpression(nullptr, statementContext, *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::logical_xor, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, resultType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::logical_xor,
						b.value
						)
				);

				return { lhs, resultType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::logical_xor,
						b.value
						)
				);

				return { *destination, resultType };
			}
		}
	}

	return Handler_LogicalAndExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_LogicalAndExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalAndExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype resultType = GLSL::BasicType::ts_bool;

	if (item.full)
	{
		ExpressionReturn a = Handler_LogicalAndExpression(nullptr, statementContext, *item.lhs);

		ExpressionReturn b = Handler_OrExpression(nullptr, statementContext, *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::logical_and, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, resultType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::logical_and,
						b.value
						)
				);

				return { lhs, resultType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::logical_and,
						b.value
						)
				);

				return { *destination, resultType };
			}
		}
	}

	return Handler_OrExpression(destination, statementContext , *item.rhs);

}

ExpressionReturn AST_Generator::Handler_OrExpression(GLSL::Lvalue* destination, StatementContext& statementContext, OrExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		ExpressionReturn a = Handler_OrExpression(nullptr, statementContext, *item.lhs);

		ExpressionReturn b = Handler_XorExpression(nullptr, statementContext, *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::bitwise_or, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::bitwise_or,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::bitwise_or,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}
		
	return Handler_XorExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_XorExpression(GLSL::Lvalue* destination, StatementContext& statementContext, XorExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		ExpressionReturn a = Handler_XorExpression(nullptr, statementContext, *item.lhs);

		ExpressionReturn b = Handler_AndExpression(nullptr, statementContext , *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::bitwise_xor, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::bitwise_xor,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::bitwise_xor,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}
	
	return Handler_AndExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_AndExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AndExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.full)
	{
		ExpressionReturn a = Handler_AndExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_EqualityExpression(nullptr, statementContext , *item.rhs);

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, GLSL::BinaryOperator::bitwise_and, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						GLSL::BinaryOperator::bitwise_and,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						GLSL::BinaryOperator::bitwise_and,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}
	
	return Handler_EqualityExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_EqualityExpression(GLSL::Lvalue* destination, StatementContext& statementContext, EqualityExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype resultType = GLSL::BasicType::ts_bool;

	if (item.operation != EqualityOp::unassigned)
	{
		ExpressionReturn a = Handler_EqualityExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_RelationalExpression(nullptr, statementContext , *item.rhs);

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

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, binaryOp, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, resultType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { lhs, resultType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { *destination, resultType };
			}
		}
	}
	
	return Handler_RelationalExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_RelationalExpression(GLSL::Lvalue* destination, StatementContext& statementContext, RelationalExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	GLSL::AST_Datatype resultType = GLSL::BasicType::ts_bool;

	if (item.operation != RelativeOp::unassigned)
	{
		ExpressionReturn a = Handler_RelationalExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_ShiftExpression(nullptr, statementContext , *item.rhs);

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

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, binaryOp, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, resultType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { lhs, resultType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { *destination, resultType };
			}
		}
	}

	return Handler_ShiftExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_ShiftExpression(GLSL::Lvalue* destination, StatementContext& statementContext, ShiftExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != ShiftOp::unassigned)
	{
		ExpressionReturn a = Handler_ShiftExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_AdditiveExpression(nullptr, statementContext , *item.rhs);

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

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, binaryOp, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}

	return Handler_AdditiveExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_AdditiveExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AdditiveExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != AdditiveOp::unassigned)
	{
		ExpressionReturn a = Handler_AdditiveExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_MultiplicativeExpression(nullptr, statementContext , *item.rhs);

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

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, binaryOp, b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}

	return Handler_MultiplicativeExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_MultiplicativeExpression(GLSL::Lvalue* destination, StatementContext& statementContext, MultiplicativeExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.operation != MultiplicativeOp::unassigned)
	{
		ExpressionReturn a = Handler_MultiplicativeExpression(nullptr, statementContext , *item.lhs);

		ExpressionReturn b = Handler_UnaryExpression(nullptr, statementContext , *item.rhs);

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

		if (a.value.IsLiteral() && b.value.IsLiteral())
		{
			return LiteralBinaryOp(a.value, binaryOp,b.value);
		}
		else
		{
			if (destination == nullptr)
			{
				GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						lhs,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { lhs, a.valueType };
			}
			else
			{
				statementContext.normalOperations.emplace_back(
					std::make_shared<GLSL::AST_BinaryOperation>
					(
						*destination,
						a.value,
						binaryOp,
						b.value
						)
				);

				return { *destination, a.valueType };
			}
		}
	}
	
	return Handler_UnaryExpression(destination, statementContext , *item.rhs);
}

ExpressionReturn AST_Generator::Handler_UnaryExpression(GLSL::Lvalue* destination, StatementContext& statementContext, UnaryExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.unaryType != UnaryExpressionType::postfix_expression)
	{
		ExpressionReturn a = Handler_UnaryExpression(nullptr, statementContext , *item.unaryExpression);

		GLSL::UnaryOperation::value op;

		switch (item.unaryType)
		{
		case UnaryExpressionType::inc_op:

			if (a.value.IsLiteral())
			{
				a.value.PreIncr();

				return a;
			}
			else
			{
				GLSL::Lvalue lhs = a.value.ToLvalue();

				statementContext.prefixOperations.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs, false
						)
				);

				return { lhs, a.valueType };
			}		
		case UnaryExpressionType::dec_op:

			if (a.value.IsLiteral())
			{
				a.value.PreDec();

				return a;
			}
			else
			{
				GLSL::Lvalue lhs = a.value.ToLvalue();

				statementContext.prefixOperations.emplace_back(
					std::make_shared<GLSL::AST_IncDecOperation>(
						lhs, true
						)
				);

				return { lhs, a.valueType };
			}
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

		if (a.value.IsLiteral())
		{
			a.value.UnaryOp(op);

			return a;
		}
		else
		{
			GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_UnaryOperation>(
					lhs, op, a.value
					)
			);

			return { lhs, a.valueType };
		}

	}

	return Handler_PostfixExpression(destination, statementContext , *item.postfixExpression);
}

ExpressionReturn AST_Generator::Handler_PostfixExpression(GLSL::Lvalue* destination, StatementContext& statementContext, PostfixExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.postfixType)
	{
	case PostfixType::primary_expression:
		return Handler_PrimaryExpression(destination, statementContext , *item.primaryExpression);
	case PostfixType::array_index:
		return ExpressionReturn();
	case PostfixType::field_select:
		return ExpressionReturn();
	case PostfixType::function_call:
		return Handler_FunctionCall(destination, statementContext , *item.functionCall);
	case PostfixType::dec_op:
		{
			ExpressionReturn a = Handler_PostfixExpression(nullptr, statementContext , *item.postfixExpression);

			
			GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_AssignmentOperation>(
					lhs, a.value
					)
			);
			

			GLSL::Lvalue inputLhs = a.value.ToLvalue();

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_IncDecOperation>(
					inputLhs, true
					)
			);

			return { lhs, a.valueType };
		}	
	case PostfixType::inc_op:
		{
			ExpressionReturn a = Handler_PostfixExpression(nullptr, statementContext , *item.postfixExpression);

			
			GLSL::Lvalue lhs = GenerateTemporary(statementContext, a.valueType);

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_AssignmentOperation>(
					lhs, a.value
					)
			);
			

			GLSL::Lvalue inputLhs = a.value.ToLvalue();

			statementContext.normalOperations.emplace_back(
				std::make_shared<GLSL::AST_IncDecOperation>(
					inputLhs, false
					)
			);

			return { lhs, a.valueType };
		}
	}

	return ExpressionReturn();
}

ExpressionReturn AST_Generator::Handler_PrimaryExpression(GLSL::Lvalue* destination, StatementContext& statementContext, PrimaryExpression& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.valuetype)
	{
	case ExpressionType::identifier:
		printf("identifier: %s\n", item.identifier.Get()->Name()->ToCString());
		return { GLSL::Rvalue(*item.identifier.Get()->Name()) , GetDatatype(item.identifier) };
	case ExpressionType::bool_const:
		return { item.boolValue , GLSL::AST_Datatype(GLSL::BasicType::ts_bool) };
	case ExpressionType::int_const:
		return { item.intValue , GLSL::AST_Datatype(GLSL::BasicType::ts_int) };
	case ExpressionType::uint_const:
		return { item.uintValue, GLSL::AST_Datatype(GLSL::BasicType::ts_uint) };
	case ExpressionType::float_const:
		return { item.floatValue, GLSL::AST_Datatype(GLSL::BasicType::ts_float) };
	case ExpressionType::expression:
		{
			StatementContext parenthesis;

			ExpressionReturn result = Handler_Expression(destination, parenthesis, *item.expression);

			AddParenthesisContext(statementContext, parenthesis);

			return result;
		}
		
	}

	return ExpressionReturn();
}

ExpressionReturn AST_Generator::LiteralBinaryOp(GLSL::Rvalue& a, GLSL::BinaryOperator::value op, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralAdd(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralSub(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralMul(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralDiv(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralMod(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralLeftShift(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralRightShift(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralBitwiseAnd(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

ExpressionReturn AST_Generator::LiteralBitwiseOr(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

ExpressionReturn AST_Generator::LiteralBitwiseXor(GLSL::Rvalue& a, GLSL::Rvalue& b)
{
	return { GLSL::Rvalue(),GLSL::AST_Datatype() };
}

ExpressionReturn AST_Generator::LiteralLogicalAnd(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralLogicalOr(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralLogicalXor(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralLess(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralLessEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralGreater(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralGreaterEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::LiteralNotEqual(GLSL::Rvalue& a, GLSL::Rvalue& b)
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

ExpressionReturn AST_Generator::Handler_Initializer(GLSL::Lvalue* destination, StatementContext& statementContext, Initializer& item)
{
	return Handler_AssignmentExpression(destination, statementContext , *item.assignEx);
}

ExpressionReturn AST_Generator::Handler_FunctionCall(GLSL::Lvalue* destination, StatementContext& statementContext, FunctionCall& item)
{
	printf(__FUNCTION__);
	printf("\n");

	std::vector<GLSL::Rvalue> callParams;
	std::vector<GLSL::AST_Datatype> signatureTypes;

	for (size_t k = 0; k < item.call->GetParamCount(); k++)
	{
		auto param = item.call->GetParameter(k);

		ExpressionReturn a = Handler_AssignmentExpression(nullptr, statementContext , *param);

		callParams.push_back(a.value);
		signatureTypes.push_back(a.valueType);
	}

	SymbolLink link = MatchFunctionSignature(item.functions, signatureTypes);

	GLSL::AST_Datatype returnType = GetDatatype(link);

	if (destination == nullptr)
	{
		GLSL::Lvalue lhs = GenerateTemporary(statementContext, returnType);

		auto sharedLink = std::make_shared<SymbolLink>(link);

		statementContext.normalOperations.emplace_back(
			std::make_shared<GLSL::AST_FunctionCall>(lhs, sharedLink, std::move(callParams))
		);

		return { lhs, returnType };
	}
	else
	{
		auto sharedLink = std::make_shared<SymbolLink>(link);

		statementContext.normalOperations.emplace_back(
			std::make_shared<GLSL::AST_FunctionCall>(*destination, sharedLink, std::move(callParams))
		);

		return { *destination, returnType };
	}
}

SymbolLink AST_Generator::MatchFunctionSignature(const std::vector<SymbolLink>& functions,
	std::vector<GLSL::AST_Datatype>& signatureTypes)
{
	for (auto& func : functions)
	{
		auto prototype = func.Get()->GetPrototype();

		if (prototype->GetParamCount() != signatureTypes.size())
		{
			continue;
		}

		for (size_t k = 0; k < prototype->GetParamCount(); k++)
		{
			auto param = prototype->GetParameter(k);

			GLSL::AST_Datatype paramType = GetDatatype(param->GetType());

			if (paramType != signatureTypes[k])
			{
				continue;
			}
		}

		return func;
	}

	return SymbolLink();
}

/*
SymbolLink AST_Generator::MatchFunctionSignature(GLSL::BasicType::value destType, std::vector<GLSL::AST_Datatype>& signatureTypes)
{
	auto functions = symbolDatabase->FindFunctions(GLSL::BasicType::ToString(destType));

	for (auto& func : functions)
	{
		auto prototype = func.Get()->GetPrototype();

		if (prototype->GetParamCount() != signatureTypes.size())
		{
			continue;
		}

		for (size_t k = 0; k < prototype->GetParamCount(); k++)
		{
			auto param = prototype->GetParameter(k);

			GLSL::AST_Datatype paramType = GetDatatype(param->GetType());

			if (paramType != signatureTypes[k])
			{
				continue;
			}
		}

		return func;
	}
	
	return SymbolLink();
	
}
*/

bool AST_Generator::IsAssignable(const GLSL::Lvalue& lvalue)
{
	switch (lvalue.valueType)
	{
	case GLSL::LvalueType::invalid:
		return false;
	case GLSL::LvalueType::declaration:
		return true;
	case GLSL::LvalueType::expression:

		return IsConstant(std::get<GLSL::VariableExpression>(lvalue.value)) == false;
	}

	return false;
}

bool AST_Generator::IsConstant(const GLSL::VariableExpression& expression)
{
	// TODO: check from symbol database

	return true;
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
		return Handler_GeometryShaderLayout(decl);
	case DeclarationType::global_interface_block:
		break;
	case DeclarationType::scoped_interface_block:
		break;
	case DeclarationType::scoped_interface_block_array:
		break;
	case DeclarationType::precision:
		return Handler_DefaultPrecision(decl);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::Handler_GeometryShaderLayout(Declaration& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (shader != GLSL::ShaderType::geometry)
	{
		// TODO: error
		return 0;
	}

	if (item.typeQ->layout == nullptr)
	{
		// TODO: error
		return 0;
	}

	if (item.typeQ->interpolation.interpolation != GLSL::InterpolationQualifierType::unused)
	{
		// TODO: error
		return 0;
	}

	if (item.typeQ->storage.qualifier == GLSL::StorageQualifierType::sq_in)
	{
		auto& layoutItems = item.typeQ->layout->list->list;

		if (layoutItems.size() != 1)
		{
			// TODO: error
			return 0;
		}

		if (layoutItems[0]->hasValue)
		{
			// TODO: error
			return 0;
		}

		Ceng::StringUtf8& name = layoutItems[0]->identifier;

		GLSL::GeometryShaderInputLayout layout;

		if (name == "points")
		{
			layout = GLSL::GeometryShaderInputLayout::points;
		}
		else if (name == "lines")
		{
			layout = GLSL::GeometryShaderInputLayout::lines;
		}
		else if (name == "lines_adjacency")
		{
			layout = GLSL::GeometryShaderInputLayout::lines_adjacency;
		}
		else if (name == "triangles")
		{
			layout = GLSL::GeometryShaderInputLayout::triangles;
		}
		else if (name == "triangles_adjacency")
		{
			layout = GLSL::GeometryShaderInputLayout::triangles_adjacency;
		}
		else
		{
			// TODO: error
			return 0;
		}

		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_GeometryShaderIn>(layout)

		);
		

	}
	else if (item.typeQ->storage.qualifier == GLSL::StorageQualifierType::sq_out)
	{
		bool definedPrimitive = false;
		bool definedVertices = false;

		GLSL::GeometryShaderOutputPrimitive primitive;
		Ceng::UINT32 maxVertices;

		Ceng::UINT32 counter = 0;

		for (auto& item : item.typeQ->layout->list->list)
		{
			++counter;

			if (counter > 2)
			{
				// TODO: error (too many values)
				break;
			}

			if (item->identifier == "points")
			{
				if (definedPrimitive)
				{
					// TODO: error (duplicate)
					continue;
				}

				if (item->hasValue)
				{
					// TODO: error
					continue;
				}

				definedPrimitive = true;
				primitive = GLSL::GeometryShaderOutputPrimitive::points;

			}
			else if (item->identifier == "line_strip")
			{
				if (item->hasValue)
				{
					// TODO: error
					continue;
				}

				definedPrimitive = true;
				primitive = GLSL::GeometryShaderOutputPrimitive::line_strip;
			}
			else if (item->identifier == "triangle_strip")
			{
				if (item->hasValue)
				{
					// TODO: error
					continue;
				}

				definedPrimitive = true;
				primitive = GLSL::GeometryShaderOutputPrimitive::triangle_strip;
			}
			else if (item->identifier == "max_vertices")
			{
				if (definedVertices)
				{
					// TODO: error (duplicate)
					continue;
				}

				if (item->hasValue == false)
				{
					// TODO: error
					continue;
				}

				if (item->value < 0)
				{
					// TODO: error
					continue;
				}

				definedVertices = true;
				maxVertices = item->value;
			}
			else
			{
				// TODO: error
			}
		}

		if (!definedPrimitive && !definedVertices)
		{
			// TODO: error (no inputs)
			return 0;
		}

		if (definedPrimitive)
		{
			if (definedVertices)
			{
				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_GeometryShaderOut>(primitive, maxVertices)
				);
			}
			else
			{
				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_GeometryShaderOut>(primitive)
				);
			}
			
		}
		else
		{
			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_GeometryShaderOut>(maxVertices)
			);
		}
	}

	return 0;
}

AST_Generator::return_type AST_Generator::Handler_DefaultPrecision(Declaration& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.spec->baseType->dataType != TypeSelector::basic_type)
	{
		// TODO: error
		return 0;
	}

	GLSL::PrecisionTarget target;

	switch (item.spec->baseType->basicType)
	{
	case GLSL::BasicType::ts_int:
		target = GLSL::PrecisionTarget::integer;
		break;
	case GLSL::BasicType::ts_float:
		target = GLSL::PrecisionTarget::floating;
		break;
	default:
		// TODO: error
		return 0;
	}

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_DefaultPrecision>(item.precision->precision, target)
	);

	return 0;
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

	if (CurrentContext().parent->children.size() == 0)
	{
		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_EmptyNode>()
		);
	}

	PopContext();

	return 0;
}

AST_Generator::return_type AST_Generator::V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.list == nullptr)
	{
		return 0;
	}

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

AST_Generator::return_type AST_Generator::V_CompoundStatement(CompoundStatement& item)
{
	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_Scope>()
	);

	NewestChildToContext();

	item.list->AcceptVisitor(*this);

	PopContext();

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

AST_Generator::return_type AST_Generator::V_ExpressionStatement(ExpressionStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	StatementContext statementContext;

	ExpressionReturn a = Handler_Expression(nullptr, statementContext, *item.ex);

	AddStatementContext(statementContext);
	return 0;
}

AST_Generator::return_type AST_Generator::V_IterationStatement(IterationStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.iterationType)
	{
	case IterationType::whileLoop:
		return WhileLoop(item);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::WhileLoop(IterationStatement& item)
{
	/*
	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_Scope>()

	);

	NewestChildToContext();

	item.whileCondition->AcceptVisitor(*this);

	GLSL::Rvalue condition = returnValue.value;

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_WhileLoop>(condition)

	);

	PopContext();
	*/

	return 0;
}

AST_Generator::return_type AST_Generator::V_JumpStatement(JumpStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	switch (item.jumpType)
	{
	case JumpType::breakStatement:
		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_Break>()
		);
		break;
	case JumpType::returnStatement:
		{
			StatementContext context;
			ExpressionReturn a = Handler_Expression(nullptr, context , *item.returnExpression);

			AddStatementContext(context);

			// TODO: check against function return type

			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_ReturnStatement>(a.value)
			);
		}
		break;		
	default:
		printf("<UNIMPLEMENTED JUMP STATEMENT CASE>");
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_SelectionStatement(SelectionStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");
	printf("<unimplemented>\n");

	StatementContext statementContext;

	ExpressionReturn a = Handler_Expression(nullptr, statementContext , *item.condition);

	AddStatementContext(statementContext);

	// TODO: convert to bool if necessary

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_IfBlock>(a.value)
	);

	NewestChildToContext();

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_Scope>()
	);

	NewestChildToContext();

	item.rest->main->AcceptVisitor(*this);

	PopContext();

	if (item.rest->elseBlock != nullptr)
	{
		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_Scope>()
		);

		NewestChildToContext();

		item.rest->elseBlock->AcceptVisitor(*this);

		PopContext();
	}

	PopContext();


	return 0;
}

AST_Generator::return_type AST_Generator::V_SwitchStatement(SwitchStatement& item)
{
	printf(__FUNCTION__);
	printf("\n");

	StatementContext statementContext;

	ExpressionReturn a = Handler_Expression(nullptr, statementContext , *item.expression);

	AddStatementContext(statementContext);
	
	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_SwitchBlock>(a.value)

	);

	NewestChildToContext();

	item.list->AcceptVisitor(*this);

	if (CurrentContext().parent->nodeType == GLSL::AST_NodeType::case_label)
	{
		PopContext();
	}

	PopContext();

	return 0;
}

AST_Generator::return_type AST_Generator::V_SwitchStatementList(SwitchStatementList& item)
{
	printf(__FUNCTION__);
	printf("\n");
	
	item.list->AcceptVisitor(*this);

	return 0;
}

AST_Generator::return_type AST_Generator::V_CaseLabel(CaseLabel& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (CurrentContext().parent->nodeType == GLSL::AST_NodeType::case_label)
	{
		PopContext();
	}

	if (item.defaultCase)
	{
		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_CaseLabel>()
		);
	}
	else
	{
		StatementContext statementContext;

		ExpressionReturn a = Handler_Expression(nullptr, statementContext , *item.expression);

		AddStatementContext(statementContext);

		CurrentContext().parent->children.emplace_back(
			std::make_shared<GLSL::AST_CaseLabel>(a.value)
		);

	}

	NewestChildToContext();

	return 0;
}




AST_Generator::return_type AST_Generator::V_InitDeclaratorList(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.invariant)
	{
		Handler_InvariantStatement(item);
		return 0;
	}

	bool normal = true;

	if (item.fullType->qualifier.layout != nullptr)
	{
		normal = false;
	}

	if (item.fullType->qualifier.interpolation.interpolation != GLSL::InterpolationQualifierType::unused)
	{
		normal = false;
	}

	switch (item.fullType->qualifier.storage.qualifier)
	{
	case GLSL::StorageQualifierType::unused:
	case GLSL::StorageQualifierType::sq_const:
		break;
	default:
		normal = false;
	}

	if (normal)
	{
		Handler_NormalDeclaration(item);
		return 0;
	}

	Handler_InterfaceVariable(item);

	return 0;
}

AST_Generator::return_type AST_Generator::Handler_InterfaceVariable(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	std::vector<GLSL::LayoutData> layout;

	switch (shader)
	{
	case GLSL::ShaderType::vertex:
		return Handler_VertexShaderInterfaceVariable(item);
	case GLSL::ShaderType::fragment:
		return Handler_FragmentShaderInterfaceVariable(item);
		break;
	case GLSL::ShaderType::geometry:
		return 0;
		break;
	}

	return 0;
}

AST_Generator::return_type AST_Generator::Handler_VertexShaderInterfaceVariable(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	if (item.fullType->qualifier.storage.qualifier == GLSL::StorageQualifierType::sq_in)
	{
		if (item.fullType->typeSpec.arrayType.baseType->dataType != Ceng::TypeSelector::basic_type)
		{
			// TODO: error (only basic types allowed)
			return 0;
		}

		switch (item.fullType->typeSpec.arrayType.baseType->basicType)
		{
		case GLSL::BasicType::ts_int:
		case GLSL::BasicType::ts_uint:
		case GLSL::BasicType::ts_float:
		case GLSL::BasicType::vec2:
		case GLSL::BasicType::vec3:
		case GLSL::BasicType::vec4:
		case GLSL::BasicType::ivec2:
		case GLSL::BasicType::ivec3:
		case GLSL::BasicType::ivec4:
		case GLSL::BasicType::uvec2:
		case GLSL::BasicType::uvec3:
		case GLSL::BasicType::uvec4:
		case GLSL::BasicType::mat2:
		case GLSL::BasicType::mat2x2:
		case GLSL::BasicType::mat2x3:
		case GLSL::BasicType::mat2x4:
		case GLSL::BasicType::mat3:
		case GLSL::BasicType::mat3x2:
		case GLSL::BasicType::mat3x3:
		case GLSL::BasicType::mat3x4:
		case GLSL::BasicType::mat4:
		case GLSL::BasicType::mat4x2:
		case GLSL::BasicType::mat4x3:
		case GLSL::BasicType::mat4x4:
			break;
		default:

			// TODO: error (illegal vertex shader input type)
			return 0;
		}

		if (item.fullType->qualifier.interpolation.interpolation != GLSL::InterpolationQualifierType::unused)
		{
			// TODO: error (interpolation qualifier not allowed for vertex shader input)
			return 0;
		}

		bool hasLocation = false;
		Ceng::UINT32 location = 0;

		if (item.fullType->qualifier.layout != nullptr)
		{
			auto& layout = item.fullType->qualifier.layout->list->list;

			if (layout.size() > 1)
			{
				// TODO: error (too many layout items)
				return 0;
			}

			if (layout.size() == 1)
			{
				if (layout[0]->identifier != "location")
				{
					// TODO: error (layout item not allowed)
					return 0;
				}
				
				if (layout[0]->hasValue == false)
				{
					// TODO: error (location not allowed without value)
					return 0;
				}

				if (layout[0]->value < 0)
				{
					// TODO: value must be >= 0
					return 0;
				}

				hasLocation = true;
				location = layout[0]->value;
			}
		}

		GLSL::AST_Datatype datatype = GetDatatype(item.fullType);

		if (datatype.category != GLSL::TypenameCategory::basic_type)
		{
			// TODO: error: interface must be basic type
			return 0;
		}

		if (datatype.basicType == GLSL::BasicType::ts_void)
		{
			// TODO: error: void not allowed
			return 0;
		}

		GLSL::BasicTypeInfo info = GLSL::GetTypeInfo(datatype.basicType);

		for (auto& x : item.list)
		{
			Ceng::UINT32 arraySize = 1;

			GLSL::ArrayIndex index = GetArrayIndex(x);

			ResolveDeclarationArrayIndex(datatype, index);

			if (datatype.index.HasSize())
			{
				if (datatype.index.indexType == GLSL::ArrayIndexType::uint_literal)
				{
					arraySize = datatype.index.GetInt();
				}
			}

			if (hasLocation)
			{
				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_VertexShaderIn>(location, datatype, x.name)
				);
			}
			else
			{
				CurrentContext().parent->children.emplace_back(
					std::make_shared<GLSL::AST_VertexShaderIn>(datatype, x.name)
				);

			}

			location += info.layoutVectorSlots * arraySize;
		}

		return 0;
	}

	if (item.fullType->qualifier.storage.qualifier == GLSL::StorageQualifierType::sq_out ||
		item.fullType->qualifier.storage.qualifier == GLSL::StorageQualifierType::sq_centroid_out)
	{
		if (item.fullType->qualifier.layout != nullptr)
		{
			// TODO: error (layout not allowed in vertex shader output)
			return 0;
		}

		switch (item.fullType->typeSpec.arrayType.baseType->dataType)
		{
		case Ceng::TypeSelector::basic_type:
			switch (item.fullType->typeSpec.arrayType.baseType->basicType)
			{
			case GLSL::BasicType::ts_int:
			case GLSL::BasicType::ivec2:
			case GLSL::BasicType::ivec3:
			case GLSL::BasicType::ivec4:
			case GLSL::BasicType::uvec2:
			case GLSL::BasicType::uvec3:
			case GLSL::BasicType::uvec4:

				if (item.fullType->qualifier.interpolation.interpolation != GLSL::InterpolationQualifierType::flat)
				{
					// TODO: error (integer types must have flat interpolation)
					return 0;
				}

				break;
			case GLSL::BasicType::ts_uint:
			case GLSL::BasicType::ts_float:
			case GLSL::BasicType::vec2:
			case GLSL::BasicType::vec3:
			case GLSL::BasicType::vec4:
			case GLSL::BasicType::mat2:
			case GLSL::BasicType::mat2x2:
			case GLSL::BasicType::mat2x3:
			case GLSL::BasicType::mat2x4:
			case GLSL::BasicType::mat3:
			case GLSL::BasicType::mat3x2:
			case GLSL::BasicType::mat3x3:
			case GLSL::BasicType::mat3x4:
			case GLSL::BasicType::mat4:
			case GLSL::BasicType::mat4x2:
			case GLSL::BasicType::mat4x3:
			case GLSL::BasicType::mat4x4:
				break;
			default:

				// TODO: error (illegal vertex shader input type)
				return 0;
			}
			break;
		case Ceng::TypeSelector::type_name:

			if (CheckShaderInterfaceStruct(item.fullType->typeSpec.arrayType.baseType->link) == false)
			{
				// TODO: error (illegal type in struct)
				return 0;
			}

			break;
		case Ceng::TypeSelector::struct_specifier:

			if (CheckShaderInterfaceStruct(*item.fullType->typeSpec.arrayType.baseType->structSpec) == false)
			{
				// TODO: error (illegal type in struct)
				return 0;
			}

			break;
		}


	}

	// TODO: error (invalid storage qualifier)

	return 0;
}

bool AST_Generator::CheckShaderInterfaceStruct(const SymbolLink& link)
{
	printf(__FUNCTION__);
	printf("\n");

	return true;
}

bool AST_Generator::CheckShaderInterfaceStruct(const StructSpecifier& structSpec)
{
	printf(__FUNCTION__);
	printf("\n");

	return true;
}

AST_Generator::return_type AST_Generator::Handler_FragmentShaderInterfaceVariable(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	return 0;
}

AST_Generator::return_type AST_Generator::Handler_InvariantStatement(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	std::vector<Ceng::StringUtf8> names;

	for (auto& entry : item.list)
	{
		names.push_back(entry.name);
	}

	CurrentContext().parent->children.emplace_back(
		std::make_shared<GLSL::AST_InvariantStatement>(std::move(names))
	);

	return 0;
}

/*
AST_Generator::return_type AST_Generator::Handler_ComplexDeclaration(InitDeclaratorList& item)
{
	


	

}
*/

void AST_Generator::ResolveDeclarationArrayIndex(GLSL::AST_Datatype& datatype, GLSL::ArrayIndex& index)
{
	if (datatype.index.IsArray() == true &&
		index.IsArray() == true)
	{
		// TODO: error (type and identifier can't both have array)
		datatype.index = GLSL::ArrayIndex();
	}

	if (index.IsArray())
	{
		datatype.index = index;
	}

	if (datatype.index.HasSize())
	{
		if (datatype.index.indexType == GLSL::ArrayIndexType::variable)
		{
			if (IsConstant(*datatype.index.GetVariable()) == false)
			{
				// TODO: error (array size not constant)

				datatype.index = GLSL::ArrayIndex();
				return;
			}
		}
	}

	return;
}

AST_Generator::return_type AST_Generator::Handler_NormalDeclaration(InitDeclaratorList& item)
{
	printf(__FUNCTION__);
	printf("\n");

	for (auto& entry : item.list)
	{

		GLSL::AST_Datatype datatype{ GetDatatype(item.fullType) };

		GLSL::ArrayIndex index = GetArrayIndex(entry);

		ResolveDeclarationArrayIndex(datatype, index);

		GLSL::SimpleDeclaration decl
		{
			item.fullType->qualifier.storage.qualifier == GLSL::StorageQualifierType::sq_const,
			item.fullType->typeSpec.precision.precision,
			datatype,
			entry.name
		};

		if (entry.initializer != nullptr)
		{
			GLSL::Lvalue dest{ decl };

			StatementContext statementContext;

			ExpressionReturn a = Handler_Initializer(&dest, statementContext, *entry.initializer);

			if (dest != a.value)
			{
				Handler_Assignment(statementContext, dest, a);
			}

			AddStatementContext(statementContext);
		}
		else
		{
			CurrentContext().parent->children.emplace_back(
				std::make_shared<GLSL::AST_NormalVariable>(decl)
			);
		}


	}

	

	return 0;
}



