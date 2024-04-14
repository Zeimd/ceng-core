#include <ceng/GLSL/AST_ConditionalOperation.h>

using namespace Ceng::GLSL;

AST_ConditionalOperation::AST_ConditionalOperation(Lvalue& lhs, Rvalue& a, Rvalue& b, Rvalue& c)
	: IASTNode(AST_NodeType::conditional_operation), lhs(lhs),a(a),b(b),c(c)
{

}

AST_ConditionalOperation::~AST_ConditionalOperation()
{

}

Ceng::StringUtf8 AST_ConditionalOperation::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += lhs.ToString(indentLevel);
	out += " = ";
	out += a.ToString(indentLevel);
	out += " ? ";
	out += b.ToString(indentLevel);
	out += " : ";
	out += c.ToString(indentLevel);
	out += ";\n";

	return out;		
}