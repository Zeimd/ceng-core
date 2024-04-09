#include "SymbolDatabase.h"

#include "Declaration.h"
#include "InitDeclaratorList.h"

using namespace Ceng;

SymbolDatabase::SymbolDatabase()
	: root(nullptr,0), top(nullptr)
{

}

Symbol& SymbolDatabase::StartScope()
{
	if (top == nullptr)
	{
		top = &root;
		return *top;
	}

	top->scope.emplace_back(top, top->scope.size());

	return top->scope.back();
}

Symbol& SymbolDatabase::EndScope()
{
	top = top->parent;

	if (top == nullptr)
	{
		top = &root;
	}

	return *top;
}

Symbol& SymbolDatabase::Top()
{
	return *top;
}

Symbol& SymbolDatabase::StartFunction(std::shared_ptr<FunctionDefinition>& functionDef)
{

}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<Declaration>& decl)
{
	Ceng::INT32 index = 0;

	switch (decl->declarationType)
	{
	case DeclarationType::function_prototype:
		top->scope.emplace_back(top, top->scope.size(),decl,0);
		return 0;
	case DeclarationType::init_list:
		
		for (auto& x : decl->declList->list)
		{
			top->scope.emplace_back(top, top->scope.size(), decl, index);
			++index;
		}
		return 0;
	case DeclarationType::global_interface_block:
		top->scope.emplace_back(top, top->scope.size(), decl,0);
		return 0;
	case DeclarationType::scoped_interface_block:
	case DeclarationType::scoped_interface_block_array:
		top->scope.emplace_back(top, top->scope.size(), decl, 0);
		top->scope.emplace_back(top, top->scope.size(), decl, 1);
		return 0;
	case DeclarationType::precision:
	case DeclarationType::type_qualifier:
		return 1;
	}

	return 0;
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<StructSpecifier>& structSpec)
{
	top->scope.emplace_back(top, top->scope.size(), structSpec);
	return 0;
}

Symbol* SymbolDatabase::Find(const Ceng::StringUtf8& name) const
{
	Symbol* current = top;
	Ceng::INT32 startIndex = current->scope.size()-1;

	while (current != nullptr)
	{
		if (startIndex > 0)
		{
			for (int k = startIndex; k >= 0; --k)
			{
				auto symbolName = current->scope[k].Name();

				if (symbolName == nullptr)
				{
					continue;
				}

				if (*current->scope[k].Name() == name)
				{
					return current;
				}
			}
		}
	
		startIndex = current->childIndex;
		current = current->parent;		
	}

	return nullptr;
}