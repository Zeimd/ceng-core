#include "Declaration.h"
#include "FunctionPrototype.h"
#include "InitDeclaratorList.h"
#include "StructDeclarationList.h"
#include "Expression.h"
#include "TypeQualifier.h"
#include "TypeSpecifierNoPrecision.h"
#include "PrecisionQualifier.h"

#include "FunctionDeclarator.h"
#include "FunctionHeader.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

Declaration::~Declaration()
{

}

void Declaration::Release()
{
	delete this;
}

Declaration::Declaration(std::shared_ptr<InitDeclaratorList>& declList)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::init_list),declList(declList),prototype(nullptr),
	arraySize(nullptr), implicitArray(false)
{

}

Declaration::Declaration(std::shared_ptr<FunctionPrototype>& prototype)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::function_prototype), declList(nullptr), prototype(prototype)
{

}

Declaration::Declaration(std::shared_ptr<PrecisionQualifier>& precision, std::shared_ptr<TypeSpecifierNoPrec>& spec)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::precision), precision(precision), spec(spec)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::global_interface_block), typeQ(typeQ),
	interfaceName(interfaceName), list(list)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::scoped_interface_block), typeQ(typeQ),
	interfaceName(interfaceName), list(list), variableName(variableName)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName, bool implicitArray)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::scoped_interface_block_array), typeQ(typeQ),
	interfaceName(interfaceName), list(list), variableName(variableName), implicitArray(true)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
	const Ceng::StringUtf8& variableName, std::shared_ptr<Expression>& arraySize)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::scoped_interface_block_array), typeQ(typeQ),
	interfaceName(interfaceName), list(list), variableName(variableName),
	implicitArray(false), arraySize(arraySize)
{

}

Declaration::Declaration(std::shared_ptr<TypeQualifier>& typeQ)
	: INonTerminal(NonTerminalType::declaration), declarationType(DeclarationType::type_qualifier), typeQ(typeQ)
{

}


Ceng::StringUtf8 Declaration::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (declarationType)
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
	case DeclarationType::type_qualifier:
		out += typeQ->ToString(indentLevel);
		break;
	default:
		return "<UNHANDLED DECLARATION TYPE>";
	}
	
	out += ';';

	return out;
}

void Declaration::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_Declaration(*this);
}

size_t Declaration::NumSymbols() const
{
	switch (declarationType)
	{
	case DeclarationType::function_prototype:
		return 1;
	case DeclarationType::init_list:
		return declList->list.size();		
		break;
	case DeclarationType::precision:
		return 0;
	case DeclarationType::global_interface_block:
		return 1;
	case DeclarationType::scoped_interface_block:
		return 2;
	case DeclarationType::scoped_interface_block_array:
		return 2;
	default:
		return 0;
	}
}

const Ceng::StringUtf8* Declaration::GetSymbolName(size_t n) const
{
	switch (declarationType)
	{
	case DeclarationType::function_prototype:
		return &prototype->decl->header->name;
	case DeclarationType::init_list:
		return &declList->list[n].name;
		break;
	case DeclarationType::precision:
		return nullptr;
	case DeclarationType::global_interface_block:
		return &interfaceName;
	case DeclarationType::scoped_interface_block:
		if (n == 0)
		{
			return &interfaceName;
		}
		else if (n == 1)
		{
			return &variableName;
		}
		else
		{
			return nullptr;
		}
	case DeclarationType::scoped_interface_block_array:
		if (n == 0)
		{
			return &interfaceName;
		}
		else if (n == 1)
		{
			return &variableName;
		}
		else
		{
			return nullptr;
		}
	default:
		return nullptr;
	}
}

bool Declaration::IsConst() const
{
	switch (declarationType)
	{
	case DeclarationType::init_list:
		if (declList->invariant)
		{
			return false;
		}

		return declList->fullType->qualifier.storage.qualifier == GLSL::StorageQualifierType::sq_const;
	default:
		return false;
	}
}

bool Declaration::IsInteger() const
{
	switch (declarationType)
	{
	case DeclarationType::init_list:
		if (declList->invariant)
		{
			return false;
		}

		return declList->fullType->typeSpec.arrayType.baseType->IsIntegerType();
	default:
		return false;
	}
}