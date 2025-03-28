#ifndef CENG_GLSL_FUNCTION_HEADER_H
#define CENG_GLSL_FUNCTION_HEADER_H

#include <memory>

#include <ceng/datatypes/ce-string.h>

#include "INonTerminal.h"

namespace Ceng
{
	class FullySpecifiedType;

	class FunctionHeader : public INonTerminal
	{
	public:

		std::shared_ptr<FullySpecifiedType> returnType;

		Ceng::StringUtf8 name;

	public:

		~FunctionHeader() override;

		void Release() override;

		FunctionHeader(std::shared_ptr<FullySpecifiedType>& returnType, const Ceng::StringUtf8& name);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif