#ifndef CENG_GLSL_FUNCTION_HEADER_WITH_PARAMS_H
#define CENG_GLSL_FUNCTION_HEADER_WITH_PARAMS_H

#include <memory>
#include <vector>

#include "INonTerminal.h"

namespace Ceng
{
	class FunctionHeader;
	class ParameterDeclaration;

	class FunctionHeaderWithParams : public INonTerminal
	{
	public:
		std::shared_ptr<FunctionHeader> header;

		std::vector < std::shared_ptr<ParameterDeclaration>> params;

	public:

		~FunctionHeaderWithParams() override;

		void Release() override;

		FunctionHeaderWithParams(std::shared_ptr<FunctionHeader>& header, std::shared_ptr<ParameterDeclaration>& decl);

		FunctionHeaderWithParams(std::shared_ptr<FunctionHeader>& header, std::vector<std::shared_ptr<ParameterDeclaration>>& params);

		void Append(std::shared_ptr<ParameterDeclaration>& decl);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif