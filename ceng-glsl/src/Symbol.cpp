#include "Symbol.h"

#include "Declaration.h"
#include "InitDeclaratorList.h"
#include "StorageQualifier.h"
#include "TypeSpecifier.h"
#include "TypeSpecifierNoArray.h"
#include "TypeSpecifierNoPrecision.h"

using namespace Ceng;

Symbol::Symbol()
	: symbolType(SymbolType::scope)
{

}

Symbol::Symbol(std::shared_ptr<Declaration>& decl, Ceng::UINT32 index)
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

Symbol::Symbol(std::shared_ptr<StructSpecifier>& structSpec)
	: symbolType(SymbolType::struct_declaration), structSpec(structSpec)
{
	
}

bool Symbol::IsTypeName() const
{
	return symbolType == SymbolType::struct_declaration;
}
