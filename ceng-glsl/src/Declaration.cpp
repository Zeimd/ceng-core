#include "Declaration.h"
#include "FunctionPrototype.h"
#include "InitDeclaratorList.h"
#include "StructDeclarationList.h"
#include "Expression.h"
#include "TypeQualifier.h"
#include "TypeSpecifierNoPrecision.h"
#include "PrecisionQualifier.h"

#include "AST_Visitor.h"

using namespace Ceng;

Declaration::~Declaration()
{

}

void Declaration::Release()
{
	delete this;
}

Declaration::Declaration(std::shared_ptr<InitDeclaratorList>& declList)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::init_list),declList(declList),prototype(nullptr),
	arraySize(nullptr), implicitArray(false)
{

}

Declaration::Declaration(std::shared_ptr<FunctionPrototype>& prototype)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::function_prototype), declList(nullptr), prototype(prototype)
{

}

Declaration::Declaration(std::shared_ptr<PrecisionQualifier>& precision, std::shared_ptr<TypeSpecifierNoPrec>& spec)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::precision), precision(precision), spec(spec)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::global_interface_block), typeQ(typeQ), 
	interfaceName(interfaceName), list(list)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::scoped_interface_block), typeQ(typeQ), 
	interfaceName(interfaceName), list(list), variableName(variableName)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName, bool implicitArray)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::scoped_interface_block_array), typeQ(typeQ), 
	interfaceName(interfaceName), list(list), variableName(variableName), implicitArray(true)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName, std::shared_ptr<Expression>& arraySize)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::scoped_interface_block_array), typeQ(typeQ), 
	interfaceName(interfaceName), list(list), variableName(variableName),
	implicitArray(false), arraySize(arraySize)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::type_qualifier), typeQ(typeQ)
{

}


Ceng::StringUtf8 Declaration::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (type)
	{
	case DeclarationType::function_prototype:
		out = prototype->ToString(indentLevel);
		break;
	case DeclarationType::init_list:
		out = declList->ToString(indentLevel);
		break;
	case DeclarationType::precision:
		out += "precision ";
		out += precision->ToString(indentLevel);
		out += ' ';
		out += spec->ToString(indentLevel);
		break;
	case DeclarationType::global_interface_block:
		out += typeQ->ToString(indentLevel);
		out += ' ';
		out += interfaceName;
		out += '\n';
		out += GetIndent(indentLevel);
		out += "{\n";
		out += list->ToString(indentLevel+1);

		out += GetIndent(indentLevel);
		out += "}";
		break;
	case DeclarationType::scoped_interface_block:
		out += typeQ->ToString(indentLevel);
		out += ' ';
		out += interfaceName;
		out += '\n';
		out += GetIndent(indentLevel);
		out += "{\n";
		out += list->ToString(indentLevel + 1);

		out += GetIndent(indentLevel);
		out += "} ";
		out += variableName;
		break;
	case DeclarationType::scoped_interface_block_array:
		out += typeQ->ToString(indentLevel);
		out += ' ';
		out += interfaceName;
		out += '\n';
		out += GetIndent(indentLevel);
		out += "{\n";
		out += list->ToString(indentLevel + 1);

		out += GetIndent(indentLevel);
		out += "} ";
		out += variableName;
		out += '[';

		if (implicitArray == false)
		{
			out += arraySize->ToString(indentLevel);
		}

		out += ']';
		break;
	default:
		return "<UNHANDLED DECLARATION TYPE>";
	}
	
	out += ';';

	return out;
}

void Declaration::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_Declaration(*this);
}