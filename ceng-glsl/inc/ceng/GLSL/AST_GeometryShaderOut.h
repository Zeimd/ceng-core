#ifndef CENG_GLSL_AST_GEOMETRY_SHADER_OUT_H
#define CENG_GLSL_AST_GEOMETRY_SHADER_OUT_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		enum class GeometryShaderOutputPrimitive
		{
			points,
			line_strip,
			triangle_strip,
		};

		class AST_GeometryShaderOut : public IASTNode
		{
		public:

			bool definedPrimitive;
			GeometryShaderOutputPrimitive primitive;

			bool definedMax;
			Ceng::UINT32 maxVertices;

		public:

			AST_GeometryShaderOut(GeometryShaderOutputPrimitive primitive);

			AST_GeometryShaderOut(Ceng::UINT32 maxVertices);

			AST_GeometryShaderOut(GeometryShaderOutputPrimitive primitive, Ceng::UINT32 maxVertices);

			~AST_GeometryShaderOut();

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif