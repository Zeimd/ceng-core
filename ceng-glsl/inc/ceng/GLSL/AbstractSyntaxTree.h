#ifndef CENG_GLSL_ABSTRACT_SYNTAX_TREE_H
#define CENG_GLSL_ABSTRACT_SYNTAX_TREE_H

#include "IASTNode.h"

#include "AST_TranslationUnit.h"

namespace Ceng
{
	namespace GLSL
	{
		class AbstractSyntaxTree
		{
		public:
			AST_TranslationUnit root;
		public:

			AbstractSyntaxTree();

			AbstractSyntaxTree(AST_TranslationUnit& root);
			
			Ceng::StringUtf8 ToString() const;
		};
	}
}

#endif
