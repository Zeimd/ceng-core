#include "TranslationUnit.h"

#include "AST_Visitor.h"

using namespace Ceng;

TranslationUnit::TranslationUnit()
	: INonTerminal(NonTerminalType::translation_unit)
{

}

TranslationUnit::~TranslationUnit()
{

}

void TranslationUnit::Release()
{
	delete this;
}

void TranslationUnit::Append(std::shared_ptr<INonTerminal>& item)
{
	items.push_back(item);
}

Ceng::StringUtf8 TranslationUnit::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += '\n';

	for (auto& x : items)
	{
		out += x->ToString(indentLevel);
		out += '\n';
	}

	out += '\n';

	return out;
}

void TranslationUnit::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_TranslationUnit(*this);
}