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

using namespace Ceng;


AST_Generator::~AST_Generator()
{

}

AST_Generator::AST_Generator()
{
	context = &root;
}

GLSL::AbstractSyntaxTree AST_Generator::GenerateTree(std::shared_ptr<TranslationUnit>& unit)
{
	AST_Generator generator;

	unit->AcceptVisitor(generator);
	
	return GLSL::AbstractSyntaxTree(generator.root);
}

AST_Generator::return_type AST_Generator::V_AssignmentExpression(AssignmentExpression& item)
{
	if (item.full)
	{
		item.unaryEx->AcceptVisitor(*this);
		GLSL::Lvalue lhs = returnValue.lvalue;
		GLSL::Rvalue a = returnValue.rvalue;

		item.assignEx->AcceptVisitor(*this);
		GLSL::Rvalue b = returnValue.rvalue;

		std::shared_ptr<GLSL::AST_BinaryOperation> output;

		switch (item.op->operation)
		{
		case AssignOpType::equal:
			context->children.push_back(std::make_shared< GLSL::AST_AssignmentOperation>(
				lhs, b
				));
			return 0;
		default:

			GLSL::BinaryOperator::value op = ConvertAssignmentOperator(item.op->operation);
			context->children.push_back(std::make_shared< GLSL::AST_BinaryOperation>(
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
		return GLSL::AST_Datatype(RegisterAnonymousStruct(item.typeSpec.typeSpec->structSpec), index);
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

			GLSL::Rvalue& out = returnValue.rvalue;

			switch (out.valueType)
			{
			case GLSL::RvalueType::int_literal:
				return { std::get<Ceng::INT32>(out.value) };
			case GLSL::RvalueType::uint_literal:
				return { std::get<Ceng::UINT32>(out.value) };
			case GLSL::RvalueType::identifier:
				return { std::get<Ceng::StringUtf8>(out.value) };
			default:
				return { item.typeSpec.elementExpression->ToString(0), true };
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

	GLSL::Rvalue& out = returnValue.rvalue;

	switch (out.valueType)
	{
	case GLSL::RvalueType::int_literal:
		return { std::get<Ceng::INT32>(out.value) };
	case GLSL::RvalueType::uint_literal:
		return { std::get<Ceng::UINT32>(out.value) };
	case GLSL::RvalueType::identifier:
		return { std::get<Ceng::StringUtf8>(out.value) };
	default:
		return { item->arraySize->ToString(0), true };
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


	context->children.push_back(output);

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

		context->children.push_back(output);
	}

	return 0;
}

AST_Generator::return_type AST_Generator::V_FunctionDefinition(FunctionDefinition& item)
{
	return 0;
}
