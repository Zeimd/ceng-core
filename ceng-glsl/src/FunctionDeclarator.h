#ifndef CENG_GLSL_FUNCTION_DECLARATOR_H
#define CENG_GLSL_FUNCTION_DECLARATOR_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class FunctionHeader;
	class FunctionHeaderWithParams;

	class FunctionDeclarator : public INonTerminal
	{
	public:

		bool params;

		std::shared_ptr<FunctionHeader> header;

		std::shared_ptr<FunctionHeaderWithParams> withParams;
	public:

		~FunctionDeclarator() override;

		void Release() override;

		FunctionDeclarator(std::shared_ptr<FunctionHeader>& header);

		FunctionDeclarator(std::shared_ptr<FunctionHeaderWithParams>& withParams);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif