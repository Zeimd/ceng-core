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

#include <ceng/GLSL/SimpleDeclaration.h>

#include <ceng/GLSL/ShaderType.h>

#include "NonTerminalVisitor.h"
#include "AssignmentOperator.h"

#include "SymbolDatabase.h"

#include "DeclarationData.h"

namespace Ceng
{
	struct ExpressionReturn
	{
		GLSL::Rvalue value;

		GLSL::AST_Datatype valueType;		
	};

	struct StatementContext
	{
		std::vector<std::shared_ptr<GLSL::IASTNode>> prefixOperations;

		std::vector<std::shared_ptr<GLSL::IASTNode>> normalOperations;

		std::vector<std::shared_ptr<GLSL::IASTNode>> postfixOperations;
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

		GLSL::ShaderType::value shader;

		std::shared_ptr<SymbolDatabase>& symbolDatabase;

		GLSL::AST_TranslationUnit root;

		//Context context;

		//std::vector<Ceng::UINT32> tempCounter;

		std::vector<Context> contextStack;

	public:

		~AST_Generator() override;

		AST_Generator(GLSL::ShaderType::value shader, std::shared_ptr<SymbolDatabase>& symbolDatabase);

		static GLSL::AbstractSyntaxTree GenerateTree(GLSL::ShaderType::value shader, 
			std::shared_ptr<SymbolDatabase>& symbolDatabase, std::shared_ptr<TranslationUnit>& unit);

		Context& CurrentContext();

		void NewestChildToContext();

		void StartContext(GLSL::IASTNode* parent);

		void PopContext();

		void AddStatementContext(const StatementContext& statementContext);

		static void AddParenthesisContext(StatementContext& statementContext, StatementContext& parenthesis);

		GLSL::AST_Datatype GetDatatype(const Ceng::StringUtf8& name);

		GLSL::AST_Datatype GetDatatype(const SymbolLink& link);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<FullySpecifiedType>& item);

		GLSL::ArrayIndex GetArrayIndex(TypeSpecifier& item);

		GLSL::ArrayIndex GetArrayIndex(DeclarationData& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<TypeSpecifier>& item);

		GLSL::ArrayIndex GetArrayIndex(std::shared_ptr<ParameterDeclarator>& item);

		GLSL::AST_Datatype GetDatatype(std::shared_ptr<TypeSpecifier>& item);

		GLSL::AST_Datatype GetDatatype(TypeSpecifier& item);

		GLSL::AST_Datatype GetMemberType(const GLSL::AST_Datatype& baseType, const Ceng::StringUtf8& memberName);

		GLSL::AST_Datatype GetDatatype(const GLSL::Lvalue& lvalue);

		GLSL::AST_Datatype GetDatatype(const GLSL::VariableExpression& expression);

		GLSL::AST_Datatype GetReturnType(FunctionPrototype& item);

		void ResolveDeclarationArrayIndex(GLSL::AST_Datatype& datatype, GLSL::ArrayIndex& index);

		//GLSL::Lvalue GenerateTemporary(GLSL::AST_Datatype& type);

		GLSL::Lvalue GenerateTemporary(StatementContext& statementContext, GLSL::AST_Datatype& type);

		Ceng::StringUtf8 RegisterAnonymousStruct(std::shared_ptr<StructSpecifier>& structSpec);

		SymbolLink MatchFunctionSignature(const std::vector<SymbolLink>& functions, std::vector<GLSL::AST_Datatype>& signatureTypes);

		SymbolLink MatchFunctionSignature(GLSL::BasicType::value destType, std::vector<GLSL::AST_Datatype>& signatureTypes);

		bool IsAssignable(const GLSL::Lvalue& lvalue);

		bool IsConstant(const GLSL::VariableExpression& expression);

		GLSL::PrecisionQualifierType::value GetDefaultPrecision(const GLSL::AST_Datatype& datatype);

		ExpressionReturn GetImplicitConversion(GLSL::Lvalue* destination, StatementContext& statementContext, GLSL::Rvalue& in, 
			GLSL::BasicType::value sourceType, GLSL::BasicType::value destType);

		ExpressionReturn ConstructFromLiteral(GLSL::Lvalue* destination, StatementContext& statementContext, GLSL::BasicType::value destType, GLSL::Rvalue& in);

		ExpressionReturn Handler_Expression(GLSL::Lvalue* destination, StatementContext& statementContext, Expression& item);

		ExpressionReturn Handler_Assignment(StatementContext& statementContext, GLSL::Lvalue& lhs, ExpressionReturn& right);

		ExpressionReturn Handler_AssignmentExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AssignmentExpression& item);
		ExpressionReturn Handler_ConditionalExpression(GLSL::Lvalue* destination, StatementContext& statementContext, ConditionalExpression& item);
		ExpressionReturn Handler_LogicalOrExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalOrExpression& item);
		ExpressionReturn Handler_LogicalXorExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalXorExpression& item);
		ExpressionReturn Handler_LogicalAndExpression(GLSL::Lvalue* destination, StatementContext& statementContext, LogicalAndExpression& item);
		ExpressionReturn Handler_OrExpression(GLSL::Lvalue* destination, StatementContext& statementContext, OrExpression& item);
		ExpressionReturn Handler_XorExpression(GLSL::Lvalue* destination, StatementContext& statementContext, XorExpression& item);
		ExpressionReturn Handler_AndExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AndExpression& item);
		ExpressionReturn Handler_EqualityExpression(GLSL::Lvalue* destination, StatementContext& statementContext, EqualityExpression& item);
		ExpressionReturn Handler_RelationalExpression(GLSL::Lvalue* destination, StatementContext& statementContext, RelationalExpression& item);
		ExpressionReturn Handler_ShiftExpression(GLSL::Lvalue* destination, StatementContext& statementContext, ShiftExpression& item);
		ExpressionReturn Handler_AdditiveExpression(GLSL::Lvalue* destination, StatementContext& statementContext, AdditiveExpression& item);
		ExpressionReturn Handler_MultiplicativeExpression(GLSL::Lvalue* destination, StatementContext& statementContext, MultiplicativeExpression& item);
		ExpressionReturn Handler_UnaryExpression(GLSL::Lvalue* destination, StatementContext& statementContext, UnaryExpression& item);
		ExpressionReturn Handler_PostfixExpression(GLSL::Lvalue* destination, StatementContext& statementContext, PostfixExpression& item);
		ExpressionReturn Handler_PrimaryExpression(GLSL::Lvalue* destination, StatementContext& statementContext, PrimaryExpression& item);

		ExpressionReturn Handler_Initializer(GLSL::Lvalue* destination, StatementContext& statementContext, Initializer& item);

		ExpressionReturn Handler_FunctionCall(GLSL::Lvalue* destination, StatementContext& statementContext, FunctionCall& item);

		return_type V_TranslationUnit(TranslationUnit& item) override;

		return_type V_FunctionDefinition(FunctionDefinition& item) override;

		return_type V_FunctionPrototype(FunctionPrototype& item) override;

		return_type V_CompoundStatementNoNewScope(CompoundStatementNoNewScope& item) override;

		return_type V_Statement(Statement& item);

		return_type V_CompoundStatement(CompoundStatement& item) override;

		return_type V_StatementList(StatementList& item);

		return_type V_SimpleStatement(SimpleStatement& item);

		return_type V_DeclarationStatement(DeclarationStatement& item);
		return_type V_ExpressionStatement(ExpressionStatement& item);
		
		return_type V_IterationStatement(IterationStatement& item);

		return_type WhileLoop(IterationStatement& item);


		return_type V_JumpStatement(JumpStatement& item);
		return_type V_SelectionStatement(SelectionStatement& item);

		return_type V_SwitchStatement(SwitchStatement& item);
		return_type V_SwitchStatementList(SwitchStatementList& item);
		return_type V_CaseLabel(CaseLabel& item);

		return_type V_Declaration(Declaration& item) override;

		return_type V_InitDeclaratorList(InitDeclaratorList& item) override;

		return_type Handler_VertexShaderInterfaceVariable(InitDeclaratorList& item);

		bool CheckShaderInterfaceStruct(const SymbolLink& link);

		bool CheckShaderInterfaceStruct(const StructSpecifier& structSpec);

		return_type Handler_FragmentShaderInterfaceVariable(InitDeclaratorList& item);

		return_type Handler_VertexOutFragmentIn(InitDeclaratorList& item);

		return_type Handler_FragCoordLayout(InitDeclaratorList& item);

		return_type Handler_GeometryShaderLayout(Declaration& item);

		return_type Handler_NormalDeclaration(InitDeclaratorList& item);

		return_type Handler_InterfaceVariable(InitDeclaratorList& item);

		return_type Handler_InvariantStatement(InitDeclaratorList& item);

		return_type Handler_DefaultPrecision(Declaration& item);

		//return_type Handler_ComplexDeclaration(InitDeclaratorList& item, DeclarationData& entry);

		GLSL::BinaryOperator::value ConvertAssignmentOperator(AssignOpType::value op);

		static ExpressionReturn LiteralBinaryOp(GLSL::Rvalue& a, GLSL::BinaryOperator::value op, GLSL::Rvalue& b);

		static ExpressionReturn LiteralAdd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralSub(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralMul(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralDiv(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralMod(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLeftShift(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralRightShift(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLogicalAnd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLogicalOr(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLogicalXor(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralBitwiseAnd(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralBitwiseOr(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralBitwiseXor(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLess(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralLessEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralGreater(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralGreaterEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static ExpressionReturn LiteralNotEqual(GLSL::Rvalue& a, GLSL::Rvalue& b);

		static bool LogicalXor(bool a, bool b);
	};

}

#endif