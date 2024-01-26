#include "TranslationUnit.h"

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