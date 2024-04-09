#ifndef CENG_GLSL_PRIMARY_EXPRESSION_H
#define CENG_GLSL_PRIMARY_EXPRESSION_H

#include <memory>
#include <ceng/datatypes/ce-string.h>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "Expression.h"

namespace Ceng
{
	namespace ExpressionType
	{
		enum value
		{
			identifier,
			int_const,
			uint_const,
			float_const,
			bool_const,
			expression,
		};
	}

	class PrimaryExpression : public INonTerminal
	{
	public:

	

		Ceng::StringUtf8 name;
		std::shared_ptr<Expression> expression;
		bool boolValue;
		Ceng::INT32 intValue;
		Ceng::UINT32 uintValue;
		Ceng::FLOAT32 floatValue;

		ExpressionType::value type;

	public:

		void Release() override;

		PrimaryExpression(const Token& token);

		PrimaryExpression(bool value);
		PrimaryExpression(const Ceng::INT32 value);
		PrimaryExpression(const Ceng::UINT32 value);
		PrimaryExpression(const Ceng::FLOAT32 value);

		PrimaryExpression(const Ceng::StringUtf8& identifier);
		PrimaryExpression(std::shared_ptr<Expression>& expression);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif