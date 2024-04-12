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
				translation_unit,
				scope,

				function_definition,

				function_prototype,

				variable_declaration,

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

				// else {}
				else_block,

				// while(a) {}
				while_block,

				// do {}
				do_block,

				// while(a)
				do_while,

				return_statement,
			};

			const char* ToString(AST_NodeType::value type);
		}
	}	
}

#endif