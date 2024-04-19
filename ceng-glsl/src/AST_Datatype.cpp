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

AST_Datatype::AST_Datatype(const Ceng::StringUtf8& customTypeName)
	: category(TypenameCategory::custom_type), customTypeName(customTypeName), index(false)
{

}


AST_Datatype::AST_Datatype(const Ceng::StringUtf8& customTypeName, ArrayIndex& index)
	: category(TypenameCategory::custom_type), customTypeName(customTypeName), index(index)
{

}

AST_Datatype AST_Datatype::DiscardArray() const
{
	switch (category)
	{
	case TypenameCategory::basic_type:
		return { basicType };
	case TypenameCategory::custom_type:
		return { customTypeName };
	}

	return AST_Datatype();
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

bool AST_Datatype::operator == (const AST_Datatype& other) const
{
	if (category != other.category)
	{
		return false;
	}

	bool typeMatch = false;

	switch (category)
	{
	case TypenameCategory::basic_type:
		typeMatch = basicType == other.basicType;
		break;
	case TypenameCategory::custom_type:
		typeMatch = customTypeName == other.customTypeName;
		break;
	}

	if (typeMatch == false)
	{
		return false;
	}

	return index == other.index;
}

bool AST_Datatype::operator != (const AST_Datatype& other) const
{
	return !(*this == other);
}