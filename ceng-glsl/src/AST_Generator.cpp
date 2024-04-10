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

AST_Generator::return_type AST_Generator::V_InitDeclaratorList(InitDeclaratorList& item)
{
	for (auto& entry : item.list)
	{
		std::vector<GLSL::LayoutData> layout;

		for (auto& layoutItem : item.fullType->qualifier.layout->list->list)
		{
			layout.emplace_back(layoutItem->identifier, layoutItem->hasValue, layoutItem->value);
		}

		// TODO: take array size info and 

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
					item.fullType->typeSpec.typeSpec.typeSpec->datatype,
					&item.fullType->typeSpec.typeSpec.typeSpec->name,
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
					item.fullType->typeSpec.typeSpec.typeSpec->datatype,
					&item.fullType->typeSpec.typeSpec.typeSpec->name,
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
				item.fullType->typeSpec.typeSpec.typeSpec->datatype,
				&item.fullType->typeSpec.typeSpec.typeSpec->name,
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
