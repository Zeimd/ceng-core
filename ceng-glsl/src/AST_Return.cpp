#include <ceng/GLSL/AST_Return.h>

using namespace Ceng::GLSL;

AST_Return::AST_Return()
	: IASTNode(AST_NodeType::return_statement), empty(true)
{

}

AST_Return::AST_Return(AST_Expression& expression)
	: IASTNode(AST_NodeType::return_statement), empty(false), expression(expression)
{

}

AST_Return::~AST_Return()
{

}

Ceng::StringUtf8 AST_Return::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out = "return";

	if (!empty)
	{
		out += ' ';
		out += expression.ToString(indentLevel);
	}

	return ";\n";
}