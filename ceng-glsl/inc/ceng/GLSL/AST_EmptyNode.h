#ifndef CENG_GLSL_AST_EMPTY_NODE_H
#define CENG_GLSL_AST_EMPTY_NODE_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_EmptyNode : public IASTNode
		{
		public:

			AST_EmptyNode()
				: IASTNode(AST_NodeType::empty)
			{

			}

			~AST_EmptyNode() override
			{

			}

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override
			{
				return "";
			}

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override
			{
				return "";
			}
		};
	}
}

#endif