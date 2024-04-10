#ifndef CENG_GLSL_PARAMETER_DECLARATION_H
#define CENG_GLSL_PARAMETER_DECLARATION_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class ParameterTypeQualifier;
	class ParameterQualifier;
	class TypeSpecifier;
	class ParameterDeclarator;

	class ParameterDeclaration : public INonTerminal
	{
	public:

		std::shared_ptr<ParameterTypeQualifier> typeQ;
		std::shared_ptr<ParameterQualifier> paramQ;

		bool typeOnly;

		std::shared_ptr<ParameterDeclarator> decl;
		std::shared_ptr<TypeSpecifier> typeSpec;

	public:

		~ParameterDeclaration() override;

		void Release() override;

		ParameterDeclaration(std::shared_ptr<ParameterTypeQualifier>& typeQ, std::shared_ptr<ParameterQualifier>& paramQ,
			std::shared_ptr<ParameterDeclarator>& decl);

		ParameterDeclaration(std::shared_ptr<ParameterQualifier>& paramQ,std::shared_ptr<ParameterDeclarator>& decl);

		ParameterDeclaration(std::shared_ptr<ParameterTypeQualifier>& typeQ, std::shared_ptr<ParameterQualifier>& paramQ,
			std::shared_ptr<TypeSpecifier>& typeSpec);

		ParameterDeclaration(std::shared_ptr<ParameterQualifier>& paramQ, std::shared_ptr<TypeSpecifier>& typeSpec);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif