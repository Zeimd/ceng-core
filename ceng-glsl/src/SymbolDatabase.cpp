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



	Ceng::StringUtf8 funcName;

	//*************************************************
	// genType functions

	std::vector<GLSL::BasicType::value> variants;

	variants = { GLSL::BasicType::ts_float,GLSL::BasicType::vec2,GLSL::BasicType::vec3,GLSL::BasicType::vec4 };

	funcName = "radians";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "degrees";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "sin";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "cos";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "tan";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "asin";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "acos";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "atan";
	AddSimpleFunction(funcName, variants, 1);

	// atan2(y,x)
	funcName = "atan";
	AddSimpleFunction(funcName, variants, 2);

	funcName = "sinh";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "cosh";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "tanh";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "asinh";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "acosh";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "atanh";
	AddSimpleFunction(funcName, variants, 1);

	// pow(x,y)
	funcName = "pow";
	AddSimpleFunction(funcName, variants, 2);

	funcName = "exp";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "log";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "exp2";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "log2";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "sqrt";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "inversesqrt";
	AddSimpleFunction(funcName, variants, 1);

	// abs(genType)
	funcName = "abs";
	AddSimpleFunction(funcName, variants, 1);

	// sign(genType)
	funcName = "sign";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "floor";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "ceil";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "trunc";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "round";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "roundEven";
	AddSimpleFunction(funcName, variants, 1);

	funcName = "fract";
	AddSimpleFunction(funcName, variants, 1);

	// genType mod(genType,float)

	// genType mod(genType,genType)
	funcName = "mod";
	AddSimpleFunction(funcName, variants, 2);

	// genType modf(genType, out genType)

	// genType min(genType, genType)
	funcName = "min";
	AddSimpleFunction(funcName, variants, 2);

	// genType min(genType, float)

	// genType max(genType, genType)
	funcName = "max";
	AddSimpleFunction(funcName, variants, 2);

	// genType max(genType, float)

	// genType clamp(genType, genType, genType)
	funcName = "clamp";
	AddSimpleFunction(funcName, variants, 3);

	// genType clamp(genType, float, float)

	// genType mix(genType, genType, genType)
	funcName = "mix";
	AddSimpleFunction(funcName, variants, 3);

	// genType clamp(genType, genType, float)

	// genType clamp(genType, genType, genBType)

	// genType step(genType, genType)
	funcName = "step";
	AddSimpleFunction(funcName, variants, 2);

	// genType step(float, genType)

	// genType smoothstep(genType, genType, genType)
	funcName = "smoothstep";
	AddSimpleFunction(funcName, variants, 3);

	// genType smoothstep(float, float, genType)

	// genBType isnan(genType)

	// genBType isinf(genType)

	// genIType floatBitsToInt(gentype)

	// genUType floatBitsToUint(gentype)

	// genType intBitsToFloat(genIType)

	// genType uintBitsToFloat(genUType)	

	// float length(genType)

	// float distance(genType, genType)

	// float dot(genType, genType)

	// vec3 cross(vec3,vec3)
	funcName = "cross";
	AddSimpleFunction(funcName, {GLSL::BasicType::vec3}, 2);

	// genType normalize(genType)
	funcName = "normalize";
	AddSimpleFunction(funcName, variants, 1);

	// vec4 ftransform()

	// genType faceforward(genType, genType, genType)
	funcName = "faceforward";
	AddSimpleFunction(funcName, variants, 3);

	// genType reflect(genType, genType)
	funcName = "reflect";
	AddSimpleFunction(funcName, variants, 2);

	// genType refract(genType,genType,float)

	// mat matrixCompMult(mat,mat)
	funcName = "matrixCompMult";
	AddSimpleFunction(funcName, 
		{
			GLSL::BasicType::mat2,
			GLSL::BasicType::mat2x2,
			GLSL::BasicType::mat2x3,
			GLSL::BasicType::mat2x4,
			GLSL::BasicType::mat3,
			GLSL::BasicType::mat3x2,
			GLSL::BasicType::mat3x3,
			GLSL::BasicType::mat3x4,
			GLSL::BasicType::mat4,
			GLSL::BasicType::mat4x2,
			GLSL::BasicType::mat4x3,
			GLSL::BasicType::mat4x4,
		}
		, 2);

	// mat2 outerProduct(vec2 c, vec2 r)
	// mat3 outerProduct(vec3 c, vec3 r)
	// mat4 outerProduct(vec4 c, vec4 r)
	// mat2x3 outerProduct(vec3 c, vec2 r)
	// mat3x2 outerProduct(vec2 c, vec3 r)
	// mat2x4 outerProduct(vec4 c, vec2 r)
	// mat4x2 outerProduct(vec2 c, vec4 r)
	// mat3x4 outerProduct(vec4 c, vec3 r)
	// mat4x3 outerProduct(vec3 c, vec4 r)
	
	// mat transpose(mat)
	funcName = "transpose";
	AddSimpleFunction(funcName,
		{
			GLSL::BasicType::mat2,
			GLSL::BasicType::mat2x2,
			GLSL::BasicType::mat2x3,
			GLSL::BasicType::mat2x4,
			GLSL::BasicType::mat3,
			GLSL::BasicType::mat3x2,
			GLSL::BasicType::mat3x3,
			GLSL::BasicType::mat3x4,
			GLSL::BasicType::mat4,
			GLSL::BasicType::mat4x2,
			GLSL::BasicType::mat4x3,
			GLSL::BasicType::mat4x4,
		}
	, 1);

	// float determinant(mat)
	funcName = "determinant";
	AddSimpleFunction_Ret_Common(funcName, GLSL::BasicType::ts_float,
		{
			GLSL::BasicType::mat2,
			GLSL::BasicType::mat2x2,
			GLSL::BasicType::mat3,
			GLSL::BasicType::mat3x3,
			GLSL::BasicType::mat4,
			GLSL::BasicType::mat4x4,
		}
	, 1);

	// mat inverse(mat)
	funcName = "inverse";
	AddSimpleFunction(funcName,
		{
			GLSL::BasicType::mat2,
			GLSL::BasicType::mat2x2,
			GLSL::BasicType::mat3,
			GLSL::BasicType::mat3x3,
			GLSL::BasicType::mat4,
			GLSL::BasicType::mat4x4,
		}
	, 1);
	


	//*************************************************
	// genIType functions

	//*************************************************
	// genUType functions


}

void SymbolDatabase::AddSimpleFunction_Ret_Common(const Ceng::StringUtf8& name, GLSL::BasicType::value returnType,
	std::vector<GLSL::BasicType::value> variants, Ceng::UINT32 numParams)
{
	std::shared_ptr<FullySpecifiedType> returnSpec = FullySpecifiedType::GetBasicType(returnType);

	std::vector< std::shared_ptr<ParameterDeclaration>> params;

	std::shared_ptr<ParameterDeclaration> paramDecl;

	std::shared_ptr<FunctionHeader> header;

	std::shared_ptr<FunctionHeaderWithParams> headerWithParams;

	std::shared_ptr<FunctionDeclarator> funcDecl;

	std::shared_ptr<ParameterQualifier> paramQ = std::make_shared<ParameterQualifier>(GLSL::ParameterQualifierType::empty);

	std::shared_ptr<TypeSpecifier> typeSpec;

	std::shared_ptr<FunctionPrototype> prototype;

	std::shared_ptr<Declaration> declaration;

	for (auto& x : variants)
	{
		typeSpec = TypeSpecifier::GetBasicType(x);

		header = std::make_shared<FunctionHeader>(returnSpec, name);

		params.clear();

		for (Ceng::UINT32 k = 0; k < numParams; k++)
		{
			params.emplace_back(std::make_shared<ParameterDeclaration>(paramQ, typeSpec)
			);

		}

		headerWithParams = std::make_shared<FunctionHeaderWithParams>(header, params);

		funcDecl = std::make_shared<FunctionDeclarator>(headerWithParams);

		prototype = std::make_shared<FunctionPrototype>(funcDecl);

		declaration = std::make_shared<Declaration>(prototype);

		builtIns.emplace_back(declaration, 0);
	}
}

void SymbolDatabase::AddSimpleFunction(const Ceng::StringUtf8& name, std::vector<GLSL::BasicType::value> variants, Ceng::UINT32 numParams)
{
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

	for (auto& x : variants)
	{
		typeSpec = TypeSpecifier::GetBasicType(x);

		returnType = std::make_shared<FullySpecifiedType>(*typeSpec);

		header = std::make_shared<FunctionHeader>(returnType, name);

		params.clear();

		for (Ceng::UINT32 k = 0; k < numParams; k++)
		{
			params.emplace_back(std::make_shared<ParameterDeclaration>(paramQ, typeSpec)
			);

		}

		headerWithParams = std::make_shared<FunctionHeaderWithParams>(header, params);

		funcDecl = std::make_shared<FunctionDeclarator>(headerWithParams);

		prototype = std::make_shared<FunctionPrototype>(funcDecl);

		declaration = std::make_shared<Declaration>(prototype);

		builtIns.emplace_back(declaration, 0);
	}
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