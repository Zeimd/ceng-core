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
	case struct_declaration:
		return "struct_declaration";
	case default_precision:
		return "default_precision";
	case interface_block:
		return "interface_block";
	case named_interface_block:
		return "named_interface_block";
	case geometry_shader_input_layout:
		return "geometry_shader_input_layout";
	case invariant_statement:
		return "invariant_statement";
	case assignment_operation:
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
	case switch_block:
		return "switch_block";
	case case_label:
		return "case_label";
	case break_statement:
		return "break_statement";
	case do_while:
		return "do_while";
	case return_statement:
		return "return_statement";
	default:
		return "<UNHANDLED AST NODE TYPE>";
	}
}

