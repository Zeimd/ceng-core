#ifndef CENG_GLSL_FUNCTION_CALL_GENERIC_H
#define CENG_GLSL_FUNCTION_CALL_GENERIC_H

#include <memory>

#include "INonTerminal.h"
#include "FuncCallHeaderNoParams.h"
#include "FuncCallHeaderParams.h"

namespace Ceng
{
	class FunctionCallGeneric : public INonTerminal
	{
	public:
		
		std::shared_ptr<FuncCallHeaderParams> withParams;
		std::shared_ptr<FuncCallHeaderNoParams> noParams;

	public:

		void Release() override;

		FunctionCallGeneric(std::shared_ptr<FuncCallHeaderParams>& withParams);

		FunctionCallGeneric(std::shared_ptr<FuncCallHeaderNoParams>& noParams);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};

}

#endif