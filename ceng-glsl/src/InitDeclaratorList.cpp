#include "InitDeclaratorList.h"

#include "AST_Visitor.h"

using namespace Ceng;

InitDeclaratorList::InitDeclaratorList(std::shared_ptr<SingleDeclaration>& decl)
	: INonTerminal(NonTerminalType::init_declarator_list), invariant(decl->invariant), fullType(decl->fullType)
{
	list.push_back(decl->data);
}

void InitDeclaratorList::Append(DeclarationData& decl)
{
	list.push_back(decl);
}

void InitDeclaratorList::Release()
{
	delete this;
}

Ceng::StringUtf8 InitDeclaratorList::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (invariant)
	{
		out += "invariant ";
	}
	else
	{
		out += fullType->ToString(indentLevel);

		if (list.size() > 1 || !list[0].empty)
		{
			out += ' ';
		}
	}

	for (size_t k=0; k < list.size(); k++)
	{
		out += list[k].ToString(indentLevel);

		if (k < list.size() - 1)
		{
			out += ", ";
		}
	}

	return out;
}

void InitDeclaratorList::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_InitDeclaratorList(*this);
}