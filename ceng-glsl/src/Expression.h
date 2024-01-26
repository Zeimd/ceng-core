#ifndef CENG_GLSL_EXPRESSION_H
#define CENG_GLSL_EXPRESSION_H

#include <memory>
#include <vector>

#include "INonTerminal.h"

namespace Ceng
{
	class AssignmentExpression;

	class Expression : public INonTerminal
	{
	public:

		std::vector<std::shared_ptr<AssignmentExpression>> assignEx;

	public:

		~Expression() override;

		void Release() override;

		Expression(std::shared_ptr<AssignmentExpression>& ex);

		void Append(std::shared_ptr<AssignmentExpression>& ex);

		Ceng::StringUtf8 ToString() const override;

	};
}

#endif