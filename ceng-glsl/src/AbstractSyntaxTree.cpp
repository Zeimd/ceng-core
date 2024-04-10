#include <ceng/GLSL/AbstractSyntaxTree.h>

#include <ceng/GLSL/AST_TranslationUnit.h>

using namespace Ceng::GLSL;

AbstractSyntaxTree::AbstractSyntaxTree()
{

}

AbstractSyntaxTree::AbstractSyntaxTree(AST_TranslationUnit& root)
	: root(root)
{

}

Ceng::StringUtf8 AbstractSyntaxTree::ToString() const
{
	return root.ToString(0);
}