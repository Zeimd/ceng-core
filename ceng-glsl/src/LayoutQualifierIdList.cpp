#include "LayoutQualifierIdList.h"
#include "LayoutQualifierId.h"

using namespace Ceng;

LayoutQualifierIdList::~LayoutQualifierIdList()
{

}

void LayoutQualifierIdList::Release()
{
	delete this;
}

LayoutQualifierIdList::LayoutQualifierIdList(std::shared_ptr<LayoutQualifierId>& qualifier)
	: INonTerminal(NonTerminalType::layout_qualifier_id_list), list{qualifier}
{

}

void LayoutQualifierIdList::Append(std::shared_ptr<LayoutQualifierId>& qualifier)
{
	list.push_back(qualifier);
}

Ceng::StringUtf8 LayoutQualifierIdList::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	for(int k=0; k < list.size(); k++)
	{
		out += list[k]->ToString(indentLevel);

		if (k != list.size() - 1)
		{
			out += ", ";
		}
	}

	return out;
}