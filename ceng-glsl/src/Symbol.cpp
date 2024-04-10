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

using namespace Ceng;

namespace Ceng
{
	const char* SymbolTypeToString(SymbolType::value type)
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


Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex)
	: symbolType(SymbolType::scope), parent(parent), childIndex(childIndex)
{

}

Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<Declaration>& decl, Ceng::UINT32 index)
	: parent(parent), childIndex(childIndex)
{
	isInteger = false;
	isConst = false;

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

Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<StructSpecifier>& structSpec)
	: parent(parent), childIndex(childIndex), symbolType(SymbolType::struct_declaration), structSpec(structSpec)
{
	
}

Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<FunctionPrototype>& prototype)
	: parent(parent), childIndex(childIndex), symbolType(SymbolType::function), prototype(prototype)
{

}

Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<ParameterDeclaration> param)
	: parent(parent), childIndex(childIndex), symbolType(SymbolType::function_parameter), param(param)
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
		return &decl->prototype->decl->header->name;
	case SymbolType::variable:
		return decl->GetSymbolName(declIndex);
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

	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	out += SymbolTypeToString(symbolType);

	const Ceng::StringUtf8* name = Name();

	if (name != nullptr)
	{
		out += ' ';
		out += *name;
	}

	out += '\n';	

	for (auto& x : scope)
	{
		out += x.ToString(indentLevel + 1);
	}

	return out;
}