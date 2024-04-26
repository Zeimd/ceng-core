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

				interface_variable,

				struct_declaration,

				type_precision,
				interface_block,
				named_interface_block,
				geometry_shader_input_layout,

				invariant_identifier,

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