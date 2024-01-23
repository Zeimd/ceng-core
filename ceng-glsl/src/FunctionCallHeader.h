#ifndef CENG_GLSL_FUNCTION_CALL_HEADER_H
#define CENG_GLSL_FUNCTION_CALL_HEADER_H

#include "INonTerminal.h"
#include "FunctionIdentifier.h"

namespace Ceng
{
	class FunctionCallHeader : public INonTerminal
	{
	public:
		std::shared_ptr<FunctionIdentifier> identifier;

	public:

		void Release() override;

		FunctionCallHeader(std::shared_ptr<FunctionIdentifier>& identifier);
	};
}

#endif