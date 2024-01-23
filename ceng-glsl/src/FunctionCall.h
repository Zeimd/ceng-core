#ifndef CENG_GLSL_FUNCTIONCALL_H
#define CENG_GLSL_FUNCTIONCALL_H

#include "INonTerminal.h"
#include "FunctionCallOrMethod.h"

namespace Ceng
{
	class FunctionCall : public INonTerminal
	{
	public:
		std::shared_ptr<FunctionCallOrMethod> call;

	public:

		void Release() override;

		FunctionCall(std::shared_ptr<FunctionCallOrMethod>& call);
	};
}

#endif