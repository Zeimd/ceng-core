#ifndef CENG_GLSL_AST_VERTEX_OUT_FRAGMENT_IN_H
#define CENG_GLSL_AST_VERTEX_OUT_FRAGMENT_IN_H

#include <ceng/datatypes/ce-string.h>

#include "IASTNode.h"

#include "InterpolationQualifierType.h"
#include "StorageQualifierType.h"
#include "AST_Datatype.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_VertexOutFragmentIn : public IASTNode
		{
		public:

			bool invariant;

			InterpolationQualifierType::value interpolation;

			// Valid values: 
			// in, centroid in
			// out, centroid out
			StorageQualifierType::value storage;

			AST_Datatype datatype;

			Ceng::StringUtf8 name;

		public:

			AST_VertexOutFragmentIn(bool invariant, InterpolationQualifierType::value interpolation,
				StorageQualifierType::value storage, const AST_Datatype& datatype, const Ceng::StringUtf8& name);

			~AST_VertexOutFragmentIn() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif