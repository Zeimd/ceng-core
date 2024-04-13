#include <ceng/GLSL/AST_Datatype.h>

using namespace Ceng::GLSL;

AST_Datatype::AST_Datatype()
	: category(TypenameCategory::invalid), index(false)
{

}

AST_Datatype::AST_Datatype(BasicType::value basicType)
	: category(TypenameCategory::basic_type), basicType(basicType), index(false)
{

}

AST_Datatype::AST_Datatype(BasicType::value basicType, ArrayIndex& index)
	: category(TypenameCategory::basic_type), basicType(basicType),index(index)
{

}

AST_Datatype::AST_Datatype(Ceng::StringUtf8& customTypeName)
	: category(TypenameCategory::custom_type), customTypeName(customTypeName), index(false)
{

}


AST_Datatype::AST_Datatype(Ceng::StringUtf8& customTypeName, ArrayIndex& index)
	: category(TypenameCategory::custom_type), customTypeName(customTypeName), index(index)
{

}

Ceng::StringUtf8 AST_Datatype::ToString() const
{
	Ceng::StringUtf8 out;

	switch (category)
	{
	case TypenameCategory::basic_type:
		out += BasicType::ToString(basicType);
		break;
	case TypenameCategory::custom_type:
		out += customTypeName;
		break;
	default:
		out += "<UNHANDLED TYPENAME CATEGORY>";
		break;
	}

	out += index.ToString(0);

	return out;
}