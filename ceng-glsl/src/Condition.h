#ifndef CENG_GLSL_CONDITION_H
#define CENG_GLSL_CONDITION_H

#include "INonTerminal.h"

namespace Ceng
{
	namespace ConditionType
	{
		enum value
		{
			expression,
			declare,
		};
	}

	class Expression;
	class FullySpecifiedType;
	class Initializer;

	class Condition : public INonTerminal
	{
	public:

		ConditionType::value conditionType;

		std::shared_ptr<Expression> expression;

		std::shared_ptr<FullySpecifiedType> fullSpec;

		Ceng::StringUtf8 identifier;

		std::shared_ptr<Initializer> initializer;

	public:

		~Condition() override;

		void Release() override;

		Condition(std::shared_ptr<Expression>& expression);

		Condition(std::shared_ptr<FullySpecifiedType>& fullSpec, const Ceng::StringUtf8& identifier, std::shared_ptr<Initializer>& initializer);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}


#endif