#ifndef CENG_GLSL_AST_GENERATOR_H
#define CENG_GLSL_AST_GENERATOR_H

#include <vector>

#include <ceng/GLSL/AbstractSyntaxTree.h>
#include <ceng/GLSL/AST_TranslationUnit.h>

#include <ceng/GLSL/AST_Datatype.h>

#include "NonTerminalVisitor.h"

namespace Ceng
{
	class AST_Generator : public NonTerminalVisitor
	{
	public:

		GLSL::AST_TranslationUnit root;

		GLSL::IASTNode* context;

		std::vector<Ceng::UINT32> tempCounter;

	public:

		~AST_Generator() override;

		AST_Generator();

		static GLSL::AbstractSyntaxTree GenerateTree(std::shared_ptr<TranslationUnit>& unit);

		return_type V_TranslationUnit(TranslationUnit& item) override;

		return_type V_Declaration(Declaration& item) override;

		return_type V_FunctionDefinition(FunctionDefinition& item) override;

		return_type V_FunctionPrototype(FunctionPrototype& item) override;

		return_type V_InitDeclaratorList(InitDeclaratorList& item) override;

		static GLSL::AST_Datatype GetDatatype(std::shared_ptr<FullySpecifiedType>& item);

		static Ceng::StringUtf8 RegisterAnonymousStruct(std::shared_ptr<StructSpecifier>& structSpec);
	};

}

#endif