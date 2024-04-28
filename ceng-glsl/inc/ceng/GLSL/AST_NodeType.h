#ifndef CENG_GLSL_AST_NODE_TYPE_H
#define CENG_GLSL_AST_NODE_TYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace AST_NodeType
		{
			enum value
			{
				// Used when a node is necessary but there isn't a proper node to place,
				// such as empty function body
				empty,

				translation_unit,

				scope,

				function_definition,

				function_prototype,

				normal_variable,

				interface_variable,

				struct_declaration,

				// precision precision_qualifier typename
				default_precision,

				interface_block,
				named_interface_block,

				vertex_shader_input_variable,

				frag_coord_layout,

				// For both vertex shader out and
				// fragment shader in
				vertex_fragment_interface_variable,

				geometry_shader_input_layout,

				geometry_shader_output_layout,

				// used for invariant type_name {, type_name...}
				invariant_statement,

				// Either ++ or --
				inc_dec,

				// a = b
				assignment_operation,

				// a = {unary_op} b
				unary_operation,

				// a = b {binary_op} c
				binary_operation,

				// a = b ? c : d
				conditional_operation,

				// a = f(...)
				function_call,

				// if (a) {}
				if_block,

				// while(a) {}
				while_block,

				// while(a)
				do_while,

				switch_block,

				case_label,

				break_statement,

				return_statement,
			};

			const char* ToString(AST_NodeType::value type);
		}
	}	
}

#endif