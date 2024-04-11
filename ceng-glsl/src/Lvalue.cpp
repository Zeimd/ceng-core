#include <ceng/GLSL/Lvalue.h>

using namespace Ceng::GLSL;

Lvalue::Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& variableIndex,
	bool memberAccess, const Ceng::StringUtf8& memberName,ArrayIndex& memberIndex)
	: variable(variable), variableIndex(variableIndex), memberAccess(memberAccess), memberName(memberName), memberIndex(memberIndex)
{

}

Ceng::StringUtf8 Lvalue::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += variable;
	out += variableIndex.ToString(indentLevel);

	if (memberAccess)
	{
		out += memberName;
		out += memberIndex.ToString(indentLevel);
	}

	return out;	
}