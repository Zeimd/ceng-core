#ifndef CENG_GLSL_FUNC_CALL_HEADER_PARAMS_H
#define CENG_GLSL_FUNC_CALL_HEADER_PARAMS_H

#include <memory>
#include <vector>
#include "INonTerminal.h"
#include "AssignmentExpression.h"
#include "FunctionCallHeader.h"

namespace Ceng
{
	class FuncCallHeaderParams : public INonTerminal
	{
	public:
		std::shared_ptr<FunctionCallHeader> header;
		std::vector<std::shared_ptr<AssignmentExpression>> params;

	public:

		void Release() override;

		FuncCallHeaderParams(std::shared_ptr<FunctionCallHeader>& header, std::shared_ptr<AssignmentExpression>& param);

		void Append(std::shared_ptr<AssignmentExpression>& param);
	};
}

#endif