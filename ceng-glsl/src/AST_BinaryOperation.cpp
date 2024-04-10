#include <ceng/GLSL/AST_BinaryOperation.h>

using namespace Ceng::GLSL;

namespace Ceng::GLSL::BinaryOperator
{
	const char* ToString(BinaryOperator::value operation)
	{
		switch (operation)
		{
		case add:
			return " + ";
		case sub:
			return " - ";
		case mul:
			return " * ";
		case div:
			return " / ";
		case mod:
			return " % ";
		case left_shift:
			return " << ";
		case right_shift:
			return " >> ";
		case bitwise_and:
			return " & ";
		case bitwise_or:
			return " | ";
		case bitwise_xor:
			return " ^ ";
		case less:
			return " < ";
		case less_eq:
			return " <= ";
		case greater:
			return " > ";
		case greater_eq:
			return " >= ";
		case equal:
			return " == ";
		case not_equal:
			return " != ";
		case field_select:
			return ".";
		case logical_and:
			return " && ";
		case logical_or:
			return " || ";
		case logical_xor:
			return " ^^ ";
		default:
			return "<UNHANDLED AST BINARY OPERATOR TYPE>";
		}
	}
}

AST_BinaryOperation::AST_BinaryOperation(Ceng::StringUtf8& lhs, AST_Expression& a, BinaryOperator::value operation, AST_Expression& b)
	: IASTNode(AST_NodeType::binary_operation), lhs(lhs), a(a), operation(operation), b(b)
{

}

AST_BinaryOperation::~AST_BinaryOperation()
{

}

Ceng::StringUtf8 AST_BinaryOperation::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += lhs;
	out += " = ";
	out += a.ToString(indentLevel);
	out += BinaryOperator::ToString(operation);
	out += b.ToString(indentLevel);
	out += ';';

	return out;
}