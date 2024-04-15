#include <ceng/GLSL/AST_UnaryOperation.h>

using namespace Ceng::GLSL;

namespace Ceng::GLSL::UnaryOperation
{
	const char* ToString(UnaryOperation::value operation)
	{
		switch (operation)
		{
		case UnaryOperation::bitwise_not:
			return "~";
		case UnaryOperation::logical_not:
			return "!";
		case UnaryOperation::negation:
			return "-";
		default:
			return "<UNHANDLED UNARY OPERATION TYPE>";
		}

	}
}

AST_UnaryOperation::AST_UnaryOperation(Lvalue& lhs, UnaryOperation::value operation, Rvalue& input)
	: IASTNode(AST_NodeType::unary_operation), lhs(lhs), operation(operation), input(input)
{

}

AST_UnaryOperation::~AST_UnaryOperation()
{

}

Ceng::StringUtf8 AST_UnaryOperation::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out = lhs.ToString(indentLevel);
	out += " = ";
	out += RhsToString(indentLevel);
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_UnaryOperation::RhsToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += UnaryOperation::ToString(operation);
	out += input.ToString(indentLevel);
	
	return out;
}