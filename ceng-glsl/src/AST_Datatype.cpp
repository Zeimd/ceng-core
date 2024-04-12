#include <ceng/GLSL/AST_Datatype.h>

using namespace Ceng::GLSL;

AST_Datatype::AST_Datatype()
	: category(TypenameCategory::invalid)
{

}

AST_Datatype::AST_Datatype(BasicType::value basicType)
	: category(TypenameCategory::basic_type), basicType(basicType)
{

}

AST_Datatype::AST_Datatype(const Ceng::StringUtf8& customTypeName)
	: category(TypenameCategory::custom_type), customTypeName(customTypeName)
{

}

Ceng::StringUtf8 AST_Datatype::ToString() const
{
	switch (category)
	{
	case TypenameCategory::basic_type:
		return BasicType::ToString(basicType);
	case TypenameCategory::custom_type:
		return customTypeName;
	}

	return "<UNHANDLED TYPENAME CATEGORY>";
}