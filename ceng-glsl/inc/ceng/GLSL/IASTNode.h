#ifndef CENG_GLSL_IAST_NODE_H
#define CENG_GLSL_IAST_NODE_H

#include <vector>
#include <memory>

#include <ceng/datatypes/ce-string.h>

#include "AST_NodeType.h"

namespace Ceng
{
	namespace GLSL
	{
		class IASTNode
		{
		public:

			AST_NodeType::value nodeType;

			std::vector<std::shared_ptr<IASTNode>> children;

		public:

			IASTNode(AST_NodeType::value nodeType)
				: nodeType(nodeType)
			{

			}

			virtual ~IASTNode()
			{

			}

			virtual Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const = 0;

		};
	}	
}



#endif