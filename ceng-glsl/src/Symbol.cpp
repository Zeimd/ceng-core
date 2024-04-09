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

using namespace Ceng;

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

		isConst = decl->typeQ->storage.qualifier == StorageQualifierType::sq_const;

		isInteger = decl->spec->typeSpec->IsIntegerType();

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

Symbol::Symbol(Symbol* parent, Ceng::UINT32 childIndex, std::shared_ptr<FunctionDefinition>& functionDef)
	: parent(parent), childIndex(childIndex), symbolType(SymbolType::function), functionDef(functionDef)
{

}

const Ceng::StringUtf8* Symbol::Name() const
{
	switch (symbolType)
	{
	case SymbolType::function:
		return decl->GetSymbolName(0);;
	case SymbolType::function_parameter:
		return functionDef->prototype->GetParameterName(declIndex);
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
