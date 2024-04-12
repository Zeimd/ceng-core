#include <ceng/GLSL/AST_ReturnStatement.h>

using namespace Ceng::GLSL;

AST_ReturnStatement::AST_ReturnStatement()
	: IASTNode(AST_NodeType::return_statement), empty(true)
{

}

AST_ReturnStatement::AST_ReturnStatement(Rvalue& expression)
	: IASTNode(AST_NodeType::return_statement), empty(false), expression(expression)
{

}

AST_ReturnStatement::~AST_ReturnStatement()
{

}

Ceng::StringUtf8 AST_ReturnStatement::ToString(Ceng::UINT32 indentLevel) const
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