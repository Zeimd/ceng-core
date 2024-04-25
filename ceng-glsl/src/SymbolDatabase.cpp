#include "SymbolDatabase.h"

#include "Declaration.h"
#include "InitDeclaratorList.h"

#include "FunctionDefinition.h"
#include "FunctionDeclarator.h"
#include "FunctionPrototype.h"
#include "FunctionHeader.h"
#include "ParameterDeclaration.h"
#include "FunctionHeaderWithParams.h"
#include "FunctionCallOrMethod.h"

#include <ceng/GLSL/StorageQualifierType.h>

#include <ceng/GLSL/ParameterQualifierType.h>
#include "ParameterTypeQualifier.h"
#include "ParameterQualifier.h"

using namespace Ceng;

SymbolDatabase::SymbolDatabase()
	: root(SymbolLink(&data, 0),nullptr,0), top(nullptr)
{
	// translation unit scope

	data.emplace_back();

	top = nullptr;

	InitBuiltIns();
}

void SymbolDatabase::InitBuiltIns()
{
	/*
	StorageQualifier in_sq{GLSL::StorageQualifierType::sq_in};
	StorageQualifier out_sq{ GLSL::StorageQualifierType::sq_out };

	auto noArr = std::make_shared<TypeSpecifierNoArray>(GLSL::BasicType::ts_int);

	TypeSpecifierNoPrec noPrec{ noArr };

	TypeQualifier typeQ{ in_sq };
	TypeSpecifier typeSpec{noPrec};

	auto fullSpec = std::make_shared<FullySpecifiedType>(typeQ, typeSpec);

	auto single = std::make_shared<SingleDeclaration>(fullSpec, "gl_VertexID");

	auto declList = std::make_shared<InitDeclaratorList>(single);

	auto decl = std::make_shared<Declaration>(declList);

	builtIns.emplace_back(decl, 0);

	single = std::make_shared<SingleDeclaration>(fullSpec, "gl_InstanceID");

	declList = std::make_shared<InitDeclaratorList>(single);

	decl = std::make_shared<Declaration>(declList);

	builtIns.emplace_back(decl, 0);
	*/

	//std::shared_ptr<TypeSpecifierNoArray> 

	std::shared_ptr<FullySpecifiedType> returnType;

	std::vector< std::shared_ptr<ParameterDeclaration>> params;

	std::shared_ptr<ParameterDeclaration> paramDecl;

	std::shared_ptr<FunctionHeader> header;

	std::shared_ptr<FunctionHeaderWithParams> headerWithParams;

	std::shared_ptr<FunctionDeclarator> funcDecl;

	std::shared_ptr<ParameterQualifier> paramQ = std::make_shared<ParameterQualifier>(GLSL::ParameterQualifierType::empty);
	
	std::shared_ptr<TypeSpecifier> typeSpec;

	std::shared_ptr<FunctionPrototype> prototype;

	std::shared_ptr<Declaration> declaration;

	typeSpec = TypeSpecifier::GetBasicType(GLSL::BasicType::ts_float);

	returnType = std::make_shared<FullySpecifiedType>(*typeSpec);

	header = std::make_shared<FunctionHeader>(returnType, "radians");

	params.clear();

	params.emplace_back(std::make_shared<ParameterDeclaration>(paramQ, typeSpec)
	);

	headerWithParams = std::make_shared<FunctionHeaderWithParams>(header, params);

	funcDecl = std::make_shared<FunctionDeclarator>(headerWithParams);

	prototype = std::make_shared<FunctionPrototype>(funcDecl);

	declaration = std::make_shared<Declaration>(prototype);

	builtIns.emplace_back(declaration,0);

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

SymbolLink SymbolDatabase::AddUndefined(SymbolType::value type, const Ceng::StringUtf8& name)
{
	data.emplace_back(type, name);
	AddNode();

	return SymbolLink(&data, data.size() - 1);
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
		Symbol* symbol = current->link.Get();

		const Ceng::StringUtf8* symbolName = symbolName = symbol->Name();

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

			symbolName = symbol->Name();

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

std::vector<SymbolLink> SymbolDatabase::FindFunctions(const Ceng::StringUtf8& name)
{
	SymbolNode* current = top;
	Ceng::INT32 startIndex = current->scope.size() - 1;

	std::vector<SymbolLink> output;

	while (current != nullptr)
	{
		Symbol* symbol = current->link.Get();

		if (symbol->symbolType == SymbolType::function || 
			symbol->symbolType == SymbolType::function_prototype)
		{
			if (*symbol->Name() == name)
			{
				output.push_back(current->link);
			}

		}
		else
		{
			for (int k = startIndex; k >= 0; --k)
			{
				symbol = current->scope[k].link.Get();

				if (symbol->symbolType == SymbolType::function ||
					symbol->symbolType == SymbolType::function_prototype)
				{
					if (*symbol->Name() == name)
					{
						output.push_back(current->scope[k].link);
					}
				}
			}
		}	

		startIndex = current->childIndex;
		current = current->parent;
	}

	for (size_t k=0; k < builtIns.size(); k++)
	{
		Symbol& symbol = builtIns[k];

		if (symbol.symbolType == SymbolType::function_prototype)
		{
			if (*symbol.Name() == name)
			{
				output.emplace_back(&builtIns, k);
			}
		}
	}

	return output;
}

bool SymbolDatabase::IsCustomType(const Ceng::StringUtf8& name) const
{
	SymbolLink result = Find(name);

	if (result.Valid())
	{
		return result.Get()->IsTypeName();
	}

	return false;
}

Ceng::StringUtf8 SymbolDatabase::ToString() const
{
	return root.ToString(0);
}