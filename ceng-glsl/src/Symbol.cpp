#include "Symbol.h"

#include "Declaration.h"
#include "InitDeclaratorList.h"
#include "StorageQualifier.h"
#include "TypeSpecifier.h"
#include "TypeSpecifierNoArray.h"
#include "TypeSpecifierNoPrecision.h"
#include "FunctionDefinition.h"
#include "FunctionPrototype.h"
#include "FunctionDeclarator.h"
#include "FunctionHeader.h"
#include "FunctionHeaderWithParams.h"
#include "ParameterDeclaration.h"
#include "ParameterDeclarator.h"
#include "FullySpecifiedType.h"
#include "Condition.h"

using namespace Ceng;

namespace Ceng
{
	namespace SymbolType
	{
		const char* ToString(SymbolType::value type)
		{
			switch (type)
			{
			case SymbolType::function:
				return "function";
			case SymbolType::function_parameter:
				return "parameter";
			case SymbolType::function_prototype:
				return "function prototype";
			case SymbolType::interface_block:
				return "interface block";
			case SymbolType::interface_block_instance:
				return "interface block instance";
			case SymbolType::scope:
				return "scope";
			case SymbolType::struct_declaration:
				return "struct";
			case SymbolType::variable:
				return "variable";
			}

			return "<UNHANDLED SYMBOL TYPE>";
		}
	}
	

}

Symbol::Symbol()
	: symbolType(SymbolType::scope)
{

}

Symbol::Symbol(std::shared_ptr<Declaration>& decl, Ceng::UINT32 index)
{
	isInteger = false;
	isConst = false;
	variableIsCondition = false;

	switch (decl->declarationType)
	{
	case DeclarationType::function_prototype:
		symbolType = SymbolType::function_prototype;

		this->decl = decl;

		break;
	case DeclarationType::init_list:
		
		symbolType = SymbolType::variable;

		declIndex = index;

		isConst = decl->IsConst();
		isInteger = decl->IsInteger();

		this->decl = decl;

		break;
	case DeclarationType::global_interface_block:

		symbolType = SymbolType::interface_block;

		this->decl = decl;
		break;
	case DeclarationType::scoped_interface_block:
	case DeclarationType::scoped_interface_block_array:

		symbolType = SymbolType::interface_block_instance;

		this->decl = decl;
		break;
	default:
		break;
	}
}

Symbol::Symbol(std::shared_ptr<StructSpecifier>& structSpec)
	: symbolType(SymbolType::struct_declaration), structSpec(structSpec)
{
	
}

Symbol::Symbol(std::shared_ptr<FunctionPrototype>& prototype)
	: symbolType(SymbolType::function), prototype(prototype)
{

}

Symbol::Symbol(std::shared_ptr<ParameterDeclaration> param)
	: symbolType(SymbolType::function_parameter), param(param)
{

}

Symbol::Symbol(std::shared_ptr<Condition>& condition)
	: symbolType(SymbolType::variable), condition(condition),
	variableIsCondition(true)
{

}

const Ceng::StringUtf8* Symbol::Name() const
{
	/*
	printf(__func__);
	printf("\n");
	printf("symbol type = %s\n", SymbolTypeToString(symbolType));
	*/

	switch (symbolType)
	{
	case SymbolType::function:
		return &prototype->GetName();
	case SymbolType::function_parameter:
		return &param->decl->name;
	case SymbolType::function_prototype:
		return &decl->prototype->GetName();
	case SymbolType::variable:
		if (variableIsCondition)
		{
			return &condition->identifier;
		}
		else
		{
			return decl->GetSymbolName(declIndex);
		}
	case SymbolType::interface_block:
		return decl->GetSymbolName(0);
	case SymbolType::interface_block_instance:
		return decl->GetSymbolName(1);
	case SymbolType::struct_declaration:
		return &structSpec->name;		
	}

	return nullptr;
}

bool Symbol::IsTypeName() const
{
	return symbolType == SymbolType::struct_declaration;
}

Ceng::StringUtf8 Symbol::ToString(Ceng::UINT32 indentLevel) const
{
	/*
	printf(__func__);
	printf("\n");
	printf("symbol type = %s\n", SymbolTypeToString(symbolType));
	*/

	return "";
}