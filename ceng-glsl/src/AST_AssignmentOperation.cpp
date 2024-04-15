#include <ceng/GLSL/AST_AssignmentOperation.h>

using namespace Ceng::GLSL;

AST_AssignmentOperation::AST_AssignmentOperation(Lvalue& lhs, Rvalue& rhs)
	: IASTNode(AST_NodeType::assignment_operation), lhs(lhs), rhs(rhs)
{

}

AST_AssignmentOperation::~AST_AssignmentOperation()
{

}

Ceng::StringUtf8 AST_AssignmentOperation::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += lhs.ToString(indentLevel);
	out += " = ";
	out += RhsToString(indentLevel);
	
	out += ";\n";
	return out;
}

Ceng::StringUtf8 AST_AssignmentOperation::RhsToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += rhs.ToString(indentLevel);

	return out;
}
