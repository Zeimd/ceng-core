#include <ceng/GLSL/AST_ReturnType.h>

using namespace Ceng::GLSL;

AST_ReturnType::AST_ReturnType()
	: datatype(AST_Datatype(BasicType::ts_void)), index(false)
{

}

AST_ReturnType::AST_ReturnType(AST_Datatype& datatype)
	: datatype(datatype), index(false)
{

}

AST_ReturnType::AST_ReturnType(AST_Datatype& datatype, ArrayIndex& index)
	: datatype(datatype), index(index)
{

}

Ceng::StringUtf8 AST_ReturnType::ToString() const
{
	Ceng::StringUtf8 out;

	out += datatype.ToString();

	if (datatype.category == TypenameCategory::basic_type &&
		datatype.basicType != BasicType::ts_void)
	{
		out += index.ToString(0);
	}	

	return out;
}
