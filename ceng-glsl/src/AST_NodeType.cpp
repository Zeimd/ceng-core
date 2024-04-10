#include <ceng/GLSL/AST_NodeType.h>

using namespace Ceng::GLSL;

const char* AST_NodeType::ToString(AST_NodeType::value type)
{
	switch (type)
	{
	case translation_unit:
		return "translation_unit";
	case scope:
		return "scope";
	case function_definition:
		return "function_definition";
	case function_prototype:
		return "function_prototype";
	case variable_declaration:
		return "variable_declaration";
	case struct_declaration:
		return "struct_declaration";
	case type_precision:
		return "type_precision";
	case interface_block:
		return "interface_block";
	case named_interface_block:
		return "named_interface_block";
	case geometry_shader_input_layout:
		return "geometry_shader_input_layout";
	case invariant_identifier:
		return "invariant_identifier";
	case simple_assignment:
		return "simple_assignment";
	case unary_operation:
		return "unary_operation";
	case binary_operation:
		return "binary_operation";
	case conditional_operation:
		return "conditional_operation";
	case function_call:
		return "function_call";
	case if_block:
		return "if_block";
	case else_block:
		return "else_block";
	case while_block:
		return "while_block";
	case do_block:
		return "do_block";
	case do_while:
		return "do_while";
	default:
		return "<UNHANDLED AST NODE TYPE>";
	}
}

