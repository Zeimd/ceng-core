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
	: root(SymbolLink(&data, 0),nullptr,0), top(nullptr)
{
	// translation unit scope

	data.emplace_back();

	top = nullptr;
}

void SymbolDatabase::StartScope()
{
	//printf(__func__);
	//printf("\n");

	if (top == nullptr)
	{
		top = &root;



		//printf("top type = %s\n", SymbolTypeToString(top->symbolType));

		//return *top;
		return;
	}
	

	data.emplace_back();

	AddNode();

	//top->scope.emplace_back(top, top->scope.size());

	top = &top->scope.back();

	//return top;
}

void SymbolDatabase::EndScope()
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
	
	//return *top;
}

/*
Symbol& SymbolDatabase::Top()
{
	return *top;
}
*/

void SymbolDatabase::StartFunction(std::shared_ptr<FunctionPrototype>& prototype)
{
	/*
	printf(__func__);
	printf("\n");
	printf("top type = %s\n", SymbolTypeToString(top->symbolType));
	*/

	data.emplace_back(prototype);

	AddNode();

	SymbolNode& functionScope = top->scope.back();

	//printf("new type = %s\n", SymbolTypeToString(functionScope.symbolType));

	auto paramCount = prototype->GetParamCount();

	//printf("paramCount = %i\n", paramCount);

	top = &functionScope;

	for (Ceng::UINT32 k = 0; k < paramCount; k++)
	{
		//printf("add param : %s\n", prototype->GetParameterName(k)->ToCString());

		data.emplace_back(prototype->GetParameter(k));

		AddNode();

		//functionScope.scope.emplace_back(data.size()-1,functionScope, functionScope.scope.size());
			
	}
	
	

	//return *top;
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<Declaration>& decl)
{
	Ceng::INT32 index = 0;

	switch (decl->declarationType)
	{
	case DeclarationType::function_prototype:
		data.emplace_back(decl, 0);

		AddNode();
		return 0;
	case DeclarationType::init_list:		
		for (auto& x : decl->declList->list)
		{
			data.emplace_back(decl, index);

			AddNode();
			++index;
		}
		return 0;
	case DeclarationType::global_interface_block:
		data.emplace_back(decl, 0);
		AddNode();
		return 0;
	case DeclarationType::scoped_interface_block:
	case DeclarationType::scoped_interface_block_array:
		data.emplace_back(decl, 0);
		AddNode();
		data.emplace_back(decl, 1);
		AddNode();
		return 0;
	case DeclarationType::precision:
	case DeclarationType::type_qualifier:
		return 1;
	}

	return 0;
}

void SymbolDatabase::AddNode()
{
	top->scope.emplace_back(SymbolLink(&data, data.size() - 1), top, top->scope.size());
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<Condition>& condition)
{
	data.emplace_back(condition);
	AddNode();
	
	return 0;
}

Ceng::INT32 SymbolDatabase::Add(std::shared_ptr<StructSpecifier>& structSpec)
{
	data.emplace_back(structSpec);
	AddNode();
	return 0;
}

SymbolLink SymbolDatabase::Find(const Ceng::StringUtf8& name) const
{
	SymbolNode* current = top;
	Ceng::INT32 startIndex = current->scope.size()-1;

	while (current != nullptr)
	{
		Symbol& symbol = current->link.Get();

		const Ceng::StringUtf8* symbolName = symbolName = symbol.Name();

		if (symbolName != nullptr)
		{
			if (*symbolName == name)
			{
				return current->link;
			}

		}

		for (int k = startIndex; k >= 0; --k)
		{
			symbol = current->scope[k].link.Get();

			symbolName = symbol.Name();

			if (symbolName == nullptr)
			{
				continue;
			}

			if (*symbolName == name)
			{
				return current->scope[k].link;
			}
		}	
	
		startIndex = current->childIndex;
		current = current->parent;		
	}

	return SymbolLink();
}

bool SymbolDatabase::IsCustomType(const Ceng::StringUtf8& name) const
{
	SymbolLink result = Find(name);

	if (result.Valid())
	{
		return result.Get().IsTypeName();
	}

	return false;
}

Ceng::StringUtf8 SymbolDatabase::ToString() const
{
	return root.ToString(0);
}