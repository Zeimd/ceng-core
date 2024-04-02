#ifndef CENG_GLSL_INITIALIZER_H
#define CENG_GLSL_INITIALIZER_H

#include "INonTerminal.h"

#include "AssignmentExpression.h"

namespace Ceng
{
	class Initializer : public INonTerminal
	{
	public:

		std::shared_ptr<AssignmentExpression> assignEx;

	public:

		Initializer(std::shared_ptr<AssignmentExpression>& assignEx);
		
		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif