#ifndef CENG_GLSL_FUNCTION_PROTOTYPE_H
#define CENG_GLSL_FUNCTION_PROTOTYPE_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class FunctionDeclarator;
	class ParameterDeclaration;

	class FunctionPrototype : public INonTerminal
	{
	public:

		std::shared_ptr<FunctionDeclarator> decl;

	public:

		~FunctionPrototype() override;

		void Release() override;

		FunctionPrototype(std::shared_ptr<FunctionDeclarator>& decl);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

		size_t GetParamCount() const;

		const Ceng::StringUtf8& GetName() const;

		const Ceng::StringUtf8* GetParameterName(size_t index) const;

		std::shared_ptr<ParameterDeclaration> GetParameter(size_t index);
	};
}

#endif