#ifndef CENG_GLSL_AST_GENERATOR_H
#define CENG_GLSL_AST_GENERATOR_H

#include <vector>

#include <ceng/GLSL/AbstractSyntaxTree.h>
#include <ceng/GLSL/AST_TranslationUnit.h>

#include <ceng/GLSL/AST_Datatype.h>
#include <ceng/GLSL/AST_ReturnType.h>
#include <ceng/GLSL/ArrayIndex.h>

#include <ceng/GLSL/Lvalue.h>
#include <ceng/GLSL/Rvalue.h>
#include <ceng/GLSL/AST_BinaryOperation.h>

#include "NonTerminalVisitor.h"
#include "AssignmentOperator.h"

#include "SymbolDatabase.h"

namespace Ceng
{
	struct GeneratorReturn
	{
		GLSL::Lvalue lvalue;

		GLSL::AST_Datatype lvalueType;

		GLSL::Rvalue rvalue;

		GLSL::AST_Datatype rvalueType;
	};

	struct Context
	{
		GLSL::IASTNode* parent;
		Ceng::UINT32* tempCounter;
	};

	class AST_Generator : public NonTerminalVisitor
	{
	public:

		std::shared_ptr<SymbolDatabase>& symbolDatabase;

		GLSL::AST_TranslationUnit root;

		Context context;

		std::vector<Ceng::UINT32> tempCounter;

		GeneratorReturn returnValue;

	public:

		~AST_Generator() override;

		AST_Generator(std::shared_ptr<SymbolDatabase>& symbolDatabase);

		static GLSL::AbstractSyntaxTree GenerateTree(std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit);

		return_type V_Expression(Expression& item);
		return_type V_AssignmentExpression(AssignmentExpression& item);
		return_type V_ConditionalExpression(ConditionalExpression& item);
		return_type V_LogicalOrExpression(LogicalOrExpression& item);
		return_type V_LogicalXorExpression(LogicalXorExpression& item);
		return_type V_LogicalAndExpression(LogicalAndExpression& item);
		return_type V_OrExpression(OrExpression& item);
		return_type V_XorExpression(XorExpression& item);
		return_type V_AndExpression(AndExpression& item);
		return_type V_EqualityExpression(EqualityExpression& item);
		return_type V_RelationalExpression(RelationalExpression& item);
		return_type V_ShiftExpression(ShiftExpression& item);
		return_type V_AdditiveExpression(AdditiveExpression& item);
		return_type V_MultiplicativeExpression(MultiplicativeExpression& item);
		return_type V_UnaryExpression(UnaryExpression& item);
		return_type V_PostfixExpression(PostfixExpression& item);
		return_type V_PrimaryExpression(PrimaryExpression& item);

		return_type V_TranslationUnit(TranslationUnit& item) override;

		return_type V_Declaration(Declaration& item) override;

		return_type V_FunctionDefinition(FunctionDefinition& item) override;

		return_type V_FunctionPrototype(FunctionPrototype& item) override;

		return_type V_InitDeclaratorList(InitDeclaratorList& item) override;

		GLSL::AST_Datatype GetDatatype(const Ceng::StringUtf8& name);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<TypeSpecifier>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<TypeSpecifier>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<ParameterDeclarator>& item);

		GLSL::AST_Datatype GetDatatype(TypeSpecifier& item);

		GLSL::ArrayIndex GetArrayIndex(TypeSpecifier& item);

		GLSL::AST_Datatype GetReturnType(FunctionPrototype& item);

		GLSL::Lvalue GenerateTemporary(GLSL::AST_Datatype& type);

		GLSL::BinaryOperator::value ConvertAssignmentOperator(AssignOpType::value op);

		Ceng::StringUtf8 RegisterAnonymousStruct(std::shared_ptr<StructSpecifier>& structSpec);
	};

}

#endif