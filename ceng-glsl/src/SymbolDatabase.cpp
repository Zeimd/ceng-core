#include "SymbolDatabase.h"

#include "Declaration.h"
#include "InitDeclaratorList.h"

#include "FunctionDefinition.h"
#include "FunctionDeclarator.h"
#include "FunctionPrototype.h"
#include "FunctionHeader.h"
#include "ParameterDeclaration.h"
#include "FunctionHeaderWithParams.h"

using namespace Ceng;

SymbolDatabase::SymbolDatabase()
	: root(nullptr,0), top(nullptr)
{

}

Symbol& SymbolDatabase::StartScope()
{
	//printf(__func__);
	//printf("\n");

	if (top == nullptr)
	{
		top = &root;

		//printf("top type = %s\n", SymbolTypeToString(top->symbolType));

		return *top;
	}

	top->scope.emplace_back(top, top->scope.size());

	top = &top->scope.back();

	return *top;
}

Symbol& SymbolDatabase::EndScope()
{
	/*
	printf(__func__);
	printf("\n");
	printf("top type = %s\n", SymbolTypeToString(top->symbolType));
	*/
	//top->ToString(0);

	top = top->parent;

	if (top == nullptr)
	{
		top = &root;
	}

	//printf("top type = %s\n", SymbolTypeToString(top->symbolType));
	//top->ToString(0);
	
	return *top;
}

Symbol& SymbolDatabase::Top()
{
	return *top;
}

Symbol& SymbolDatabase::StartFunction(std::shared_ptr<FunctionPrototype>& prototype)
{
	/*
	printf(__func__);
	printf("\n");
	printf("top type = %s\n", SymbolTypeToString(top->symbolType));
	*/

	top->scope.emplace_back(top, top->scope.size(), prototype);

	Symbol& functionScope = top->scope.back();

	//printf("new type = %s\n", SymbolTypeToString(functionScope.symbolType));

	auto paramCount = prototype->GetParamCount();

	//printf("paramCount = %i\n", paramCount);

	for (Ceng::UINT32 k = 0; k < paramCount; k++)
	{
		//printf("add param : %s\n", prototype->GetParameterName(k)->ToCString());

		functionScope.scope.emplace_back(&functionScope, functionScope.scope.size(),
			prototype->GetParameter(k));
			
	}
	
	top = &functionScope;

	return *top;
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<Declaration>& decl)
{
	printf(__func__);
	printf("\n");

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

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<Condition>& condition)
{
	top->scope.emplace_back(top, top->scope.size(), condition);
	return 0;
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<StructSpecifier>& structSpec)
{
	top->scope.emplace_back(top, top->scope.size(), structSpec);
	return 0;
}

Symbol* SymbolDatabase::Find(const Ceng::StringUtf8& name) const
{
	printf(__func__);
	printf("\n");

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

bool SymbolDatabase::IsCustomType(const Ceng::StringUtf8& name) const
{
	Symbol* result = Find(name);

	if (result == nullptr)
	{
		return false;
	}

	return result->IsTypeName();
}

Ceng::StringUtf8 SymbolDatabase::ToString() const
{
	return root.ToString(0);
}