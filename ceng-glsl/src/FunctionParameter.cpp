#include <ceng/GLSL/FunctionParameter.h>

using namespace Ceng::GLSL;

FunctionParameter::FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype,
	ArrayIndex& index)
	: isConst(isConst), qualifier(qualifier), datatype(datatype), index(index), name(name), anonymous(true)
{

}

FunctionParameter::FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype,
	ArrayIndex& index, Ceng::StringUtf8& name)
	: isConst(isConst), qualifier(qualifier), datatype(datatype), index(index), name(name), anonymous(false)
{

}

Ceng::StringUtf8 FunctionParameter::ToString() const
{
	Ceng::StringUtf8 out;

	if (isConst)
	{
		out += "const ";
	}

	out += ParameterQualifierType::ToString(qualifier);
	out += ' ';

	out += datatype.ToString();

	if (!anonymous)
	{
		out += ' ';
		out += name;
	}
	out += index.ToString(0);
	return out;
}