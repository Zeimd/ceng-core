#ifndef CENG_GLSL_AST_VERTEX_SHADER_IN_H
#define CENG_GLSL_AST_VERTEX_SHADER_IN_H

#include "IASTNode.h"

#include "AST_Datatype.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_VertexShaderIn : public IASTNode
		{
		public:
			
			bool hasLocation;

			Ceng::UINT32 location;

			AST_Datatype dataType;

			Ceng::StringUtf8 name;

		public:

			AST_VertexShaderIn(const AST_Datatype& dataType, const Ceng::StringUtf8& name);

			AST_VertexShaderIn(Ceng::UINT32 location, const AST_Datatype& dataType, const Ceng::StringUtf8& name);

			~AST_VertexShaderIn() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif