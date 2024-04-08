#ifndef CENG_GLSL_PARAMETER_DECLARATOR_H
#define CENG_GLSL_PARAMETER_DECLARATOR_H

#include "INonTerminal.h"

namespace Ceng
{
	class TypeSpecifier;
	class Expression;

	class ParameterDeclarator : public INonTerminal
	{
	public:

		std::shared_ptr<TypeSpecifier> typeSpec;

		Ceng::StringUtf8 name;
		
		std::shared_ptr<Expression> arraySize;

	public:

		~ParameterDeclarator() override;

		void Release() override;

		ParameterDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec, const Ceng::StringUtf8& name);

		ParameterDeclarator(std::shared_ptr<TypeSpecifier>& typeSpec, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif