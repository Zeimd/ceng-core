#ifndef CENG_GLSL_ASSIGNMENT_OPERATOR_H
#define CENG_GLSL_ASSIGNMENT_OPERATOR_H

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"

namespace Ceng
{
	namespace AssignOpType
	{
		enum value
		{
			equal,
			add,
			sub,
			mul,
			div,
			mod,
			left,
			right,
			and_op,
			or_op,
			xor_op,
		};
	}

	class AssignmentOperator : public INonTerminal
	{
	public:

		AssignOpType::value operation;

	public:

		void Release() override;

		AssignmentOperator(const Token& token);

		AssignmentOperator(AssignOpType::value operation);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;

	};
}

#endif