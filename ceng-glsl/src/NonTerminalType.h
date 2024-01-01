#ifndef CENG_GLSL_NONTERMINALTYPE_H
#define CENG_GLSL_NONTERMINALTYPE_H

namespace Ceng
{
	namespace NonTerminalType
	{
		enum value
		{
			variable_identifier,
			primary_expression,
			postfix_expression,
			integer_expression,
			constant_expression,

			function_call,
			function_call_or_method,
			function_call_generic,
			function_call_header_with_parameters,
			function_call_header_no_parameters,
			function_call_header,
			function_identifier,

			expression,
			assignment_expression,
			unary_expression,
			multiplicative_expression,
			additive_expression,
			shift_expression,
			relational_expression,
			equality_expression,
			and_expression,
			xor_expression,
			or_expression,
			logical_and_expression,
			logical_xor_expression,
			logical_or_expression,
			conditional_expression,

			unary_operator,
			assignment_operator,

			declaration,
			function_prototype,
			init_declarator_list,

			precision_qualifier,
			storage_qualifier,
			type_qualifier,
			invariant_qualifier,
			interpolation_qualifier,

			layout_qualifier,
			layout_qualifier_id_list,
			layout_qualifier_id,

			type_specifier_nonarray,
			type_specifier_no_prec,
			type_specifier,
			fully_specified_type,

			function_declarator,
			function_header,
			function_header_with_parameters,
			function_header_parameter_declaration,

			parameter_declaration,
			parameter_type_qualifier,
			parameter_qualifier,
			parameter_declarator,
			parameter_type_specifier,

			single_declaration,			
			initializer,
			
			struct_specifier,
			struct_declaration_list,
			struct_declaration,
			struct_declarator_list,
			struct_declarator,

			declaration_statement,

			statement,
			compound_statement,
			simple_statement,

			expression_statement,
			selection_statement,
			switch_statement,
			case_label,
			iteration_statement,
			jump_statement,

			statement_list,
			statement_no_new_scope,
			compound_statement_no_new_scope,

			selection_rest_statement,
			condition,
			switch_statement_list,

			for_init_statement,
			for_rest_statement,

			conditionopt,

			translation_unit,
			
			external_declaration,

			function_definition,

			unused,
		};
	}
}

#endif