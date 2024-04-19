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

#include <ceng/GLSL/Lvalue.h>

#include "NonTerminalVisitor.h"
#include "AssignmentOperator.h"

#include "SymbolDatabase.h"

namespace Ceng
{
	struct GeneratorReturn
	{
		GLSL::Rvalue value;

		GLSL::AST_Datatype valueType;		
	};

	struct Context
	{
		GLSL::IASTNode* parent;
		Ceng::UINT32 tempCounter;

		Context(GLSL::IASTNode* parent)
			: parent(parent), tempCounter(0)
		{

		}
	};

	class AST_Generator : public NonTerminalVisitor
	{
	public:

		std::shared_ptr<SymbolDatabase>& symbolDatabase;

		GLSL::AST_TranslationUnit root;

		//Context context;

		//std::vector<Ceng::UINT32> tempCounter;

		GeneratorReturn returnValue;

		std::vector<Context> contextStack;

	public:

		~AST_Generator() override;

		AST_Generator(std::shared_ptr<SymbolDatabase>& symbolDatabase);

		static GLSL::AbstractSyntaxTree GenerateTree(std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit);

		Context& CurrentContext();

		void NewestChildToContext();

		void StartContext(GLSL::IASTNode* parent);

		void PopContext();

		GLSL::AST_Datatype GetDatatype(const Ceng::StringUtf8& name);

		GLSL::AST_Datatype GetDatatype(const SymbolLink& link);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<TypeSpecifier>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<TypeSpecifier>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<ParameterDeclarator>& item);

		GLSL::AST_Datatype GetDatatype(TypeSpecifier& item);

		GLSL::AST_Datatype GetMemberType(const GLSL::AST_Datatype& baseType, const Ceng::StringUtf8& memberName);

		GLSL::AST_Datatype GetDatatype(const GLSL::Lvalue& lvalue);

		GLSL::AST_Datatype GetDatatype(const GLSL::VariableExpression& expression);

		GLSL::ArrayIndex GetArrayIndex(TypeSpecifier& item);

		GLSL::AST_Datatype GetReturnType(FunctionPrototype& item);

		GLSL::Lvalue GenerateTemporary(GLSL::AST_Datatype& type);

		Ceng::StringUtf8 RegisterAnonymousStruct(std::shared_ptr<StructSpecifier>& structSpec);

		SymbolLink MatchFunctionSignature(const std::vector<SymbolLink>& functions, std::vector<GLSL::AST_Datatype>& signatureTypes);

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

		return_type V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item) override;

		return_type V_Statement(Statement& item);

		return_type V_CompoundStatement(CompoundStatement& item) override;

		return_type V_StatementList(StatementList& item);

		return_type V_SimpleStatement(SimpleStatement& item);

		return_type V_CaseLabel(CaseLabel& item);
		return_type V_DeclarationStatement(DeclarationStatement& item);
		return_type V_ExpressionStatement(ExpressionStatement& item);
		return_type V_IterationStatement(IterationStatement& item);
		return_type V_JumpStatement(JumpStatement& item);
		return_type V_SelectionStatement(SelectionStatement& item);
		return_type V_SwitchStatementList(SwitchStatementList& item);

		return_type V_InitDeclaratorList(InitDeclaratorList& item) override;

		return_type V_Initializer(Initializer& item);

		return_type V_FunctionCall(FunctionCall& item) override;

		GLSL::BinaryOperator::value ConvertAssignmentOperator(AssignOpType::value op);

		static GeneratorReturn LiteralBinaryOp(GLSL::Rvalue& a, GLSL::BinaryOperator::value op, GLSL::Rvalue& b);

		static GeneratorReturn LiteralAdd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralSub(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralMul(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralDiv(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralMod(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLeftShift(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralRightShift(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLogicalAnd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLogicalOr(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLogicalXor(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralBitwiseAnd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralBitwiseOr(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralBitwiseXor(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLess(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralLessEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralGreater(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralGreaterEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static GeneratorReturn LiteralNotEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static bool LogicalXor(bool a, bool b);
	};

}

#endif