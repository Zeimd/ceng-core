#ifndef CENG_GLSL_AST_GENERATOR_H
#define CENG_GLSL_AST_GENERATOR_H

#include <ceng/GLSL/AbstractSyntaxTree.h>
#include <ceng/GLSL/AST_TranslationUnit.h>

#include "NonTerminalVisitor.h"

namespace Ceng
{
	class AST_Generator : public NonTerminalVisitor
	{
	public:

		GLSL::AST_TranslationUnit root;

	public:

		~AST_Generator() override;

		AST_Generator();

		static GLSL::AbstractSyntaxTree GenerateTree(std::shared_ptr<TranslationUnit>& unit);

		return_type V_TranslationUnit(TranslationUnit& item) override;

		return_type V_Declaration(Declaration& item) override;

		return_type V_FunctionDefinition(FunctionDefinition& item) override;

		
	};

}

#endif