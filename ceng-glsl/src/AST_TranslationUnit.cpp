#include <ceng/GLSL/AST_TranslationUnit.h>

using namespace Ceng::GLSL; 

AST_TranslationUnit::AST_TranslationUnit()
	: IASTNode(AST_NodeType::translation_unit)
{

}

AST_TranslationUnit::~AST_TranslationUnit()
{

}

Ceng::StringUtf8 AST_TranslationUnit::ToString(Ceng::UINT32 indentLevel) const
{
	printf(__FUNCTION__);

	Ceng::StringUtf8 out;

	for (auto& x : children)
	{
		out += x->ToString(indentLevel);
	}

	return out;
}