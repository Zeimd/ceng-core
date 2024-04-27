#ifndef CENG_GLSL_AST_GEOMETRY_SHADER_IN_H
#define CENG_GLSL_AST_GEOMETRY_SHADER_IN_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		enum class GeometryShaderInputLayout
		{
			points,
			lines,
			lines_adjacency,
			triangles,
			triangles_adjacency,
		};

		class AST_GeometryShaderIn : public IASTNode
		{
		public:
			GeometryShaderInputLayout layout;

		public:

			AST_GeometryShaderIn(GeometryShaderInputLayout layout);

			~AST_GeometryShaderIn() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif