#ifndef CENG_GLSL_IAST_NODE_H
#define CENG_GLSL_IAST_NODE_H

#include <ceng/datatypes/ce-string.h>

#include "AST_NodeType.h"

namespace Ceng
{
	class IASTNode
	{
	public:

		AST_NodeType::value nodeType;

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



#endif