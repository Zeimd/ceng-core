#ifndef CENG_GLSL_FUNC_CALL_HEADER_NO_PARAMS_H
#define CENG_GLSL_FUNC_CALL_HEADER_NO_PARAMS_H

#include "INonTerminal.h"
#include "FunctionCallHeader.h"

namespace Ceng
{
	class FuncCallHeaderNoParams : public INonTerminal
	{
	public:
		std::shared_ptr<FunctionCallHeader> header;

	public:

		void Release() override;

		FuncCallHeaderNoParams(std::shared_ptr<FunctionCallHeader>& header);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

	};
}

#endif