#include "NonTerminalType.h"

namespace Ceng
{
	namespace NonTerminalType
	{
		const char* ToString(NonTerminalType::value type)
		{
			switch (type)
			{
			case variable_identifier:
				return "variable_identifier";
			case primary_expression:
				return "primary_expression";
			case postfix_expression:
				return "postfix_expression";
			case integer_expression:
				return "integer_expression";
			case constant_expression:
				return "constant_expression";

			case function_call:
				return "function_call";
			case function_call_or_method:
				return "function_call_or_method";
			case function_call_generic:
				return "function_call_generic";
			case function_call_header_with_parameters:
				return "function_call_header_with_parameters";
			case function_call_header_no_parameters:
				return "function_call_header_no_parameters";
			case function_call_header:
				return "function_call_header";
			case function_identifier:
				return "function_identifier";

			case expression:
				return "expression";
			case assignment_expression:
				return "assignment_expression";
			case unary_expression:
				return "unary_expression";
			case multiplicative_expression:
				return "multiplicative_expression";
			case additive_expression:
				return "additive_expression";
			case shift_expression:
				return "shift_expression";
			case relational_expression:
				return "relational_expression";
			case equality_expression:
				return "equality_expression";
			case and_expression:
				return "and_expression";
			case xor_expression:
				return "xor_expression";
			case or_expression:
				return "or_expression";
			case logical_and_expression:
				return "logical_and_expression";
			case logical_xor_expression:
				return "logical_xor_expression";
			case logical_or_expression:
				return "logical_or_expression";
			case conditional_expression:
				return "conditional_expression";

			case unary_operator:
				return "unary_operator";
			case assignment_operator:
				return "assignment_operator";

			case declaration:
				return "declaration";
			case function_prototype:
				return "function_prototype";
			case init_declarator_list:
				return "init_declarator_list";

			case precision_qualifier:
				return "precision_qualifier";
			case storage_qualifier:
				return "storage_qualifier";
			case type_qualifier:
				return "type_qualifier";
			case invariant_qualifier:
				return "invariant_qualifier";
			case interpolation_qualifier:
				return "interpolation_qualifier";

			case layout_qualifier:
				return "layout_qualifier";
			case layout_qualifier_id_list:
				return "layout_qualifier_id_list";
			case layout_qualifier_id:
				return "layout_qualifier_id";

			case type_specifier_nonarray:
				return "type_specifier_nonarray";
			case type_specifier_no_prec:
				return "type_specifier_no_prec";
			case type_specifier:
				return "type_specifier";
			case fully_specified_type:
				return "fully_specified_type";

			case function_declarator:
				return "function_declarator";
			case function_header:
				return "function_header";
			case function_header_with_parameters:
				return "function_header_with_parameters";
			case function_header_parameter_declaration:
				return "function_header_parameter_declaration";

			case parameter_declaration:
				return "parameter_declaration";
			case parameter_type_qualifier:
				return "parameter_type_qualifier";
			case parameter_qualifier:
				return "parameter_qualifier";
			case parameter_declarator:
				return "parameter_declarator";
			case parameter_type_specifier:
				return "parameter_type_specifier";

			case single_declaration:
				return "single_declaration";
			case initializer:
				return "initializer";

			case struct_specifier:
				return "struct_specifier";
			case struct_declaration_list:
				return "struct_declaration_list";
			case struct_declaration:
				return "struct_declaration";
			case struct_declarator_list:
				return "struct_declarator_list";
			case struct_declarator:
				return "struct_declarator";

			case declaration_statement:
				return "declaration_statement";

			case statement:
				return "statement";
			case compound_statement:
				return "compound_statement";
			case simple_statement:
				return "simple_statement";

			case expression_statement:
				return "expression_statement";
			case selection_statement:
				return "selection_statement";
			case switch_statement:
				return "switch_statement";
			case case_label:
				return "case_label";
			case iteration_statement:
				return "iteration_statement";
			case jump_statement:
				return "jump_statement";

			case statement_list:
				return "statement_list";
			case statement_no_new_scope:
				return "statement_no_new_scope";
			case compound_statement_no_new_scope:
				return "compound_statement_no_new_scope";

			case selection_rest_statement:
				return "selection_rest_statement";
			case condition:
				return "condition";
			case switch_statement_list:
				return "switch_statement_list";

			case for_init_statement:
				return "for_init_statement";
			case for_rest_statement:
				return "for_rest_statement";

			case conditionopt:
				return "conditionopt";

			case translation_unit:
				return "translation_unit";

			case external_declaration:
				return "external_declaration";

			case function_definition:
				return "function_definition";

			case unused:
				return "unused";
			default:
				return "<no name given>";
			};
		}
	}
	
}

