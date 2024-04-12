#include <ceng/GLSL/AST_Datatype.h>

using namespace Ceng::GLSL;

AST_Datatype::AST_Datatype()
	: category(TypenameCategory::invalid), index(false)
{

}

AST_Datatype::AST_Datatype(BasicType::value basicType, ArrayIndex& index)
	: category(TypenameCategory::basic_type), basicType(basicType),index(index)
{

}

AST_Datatype::AST_Datatype(const Ceng::StringUtf8& customTypeName, ArrayIndex& index)
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
	case TypenameCategory::custom_type:
		out += customTypeName;
	default:
		out += "<UNHANDLED TYPENAME CATEGORY>";
	}

	out += index.ToString(0);

	return out;
}