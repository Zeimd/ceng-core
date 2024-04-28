#ifndef CENG_GLSL_AST_FRAGMENT_SHADER_OUT_H
#define CENG_GLSL_AST_FRAGMENT_SHADER_OUT_H

#include <ceng/datatypes/ce-string.h>

#include "IASTNode.h"

#include "AST_Datatype.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_FragmentShaderOut : public IASTNode
		{
		public:

			bool explicitLocation;
			Ceng::UINT32 location;

			bool explicitIndex;
			Ceng::UINT32 index;

			AST_Datatype datatype;

			Ceng::StringUtf8 name;

		public:

			AST_FragmentShaderOut(bool explicitLocation, Ceng::UINT32 location,
				bool explicitIndex, Ceng::UINT32 index, 
				const AST_Datatype& datatype, const Ceng::StringUtf8& name);

			~AST_FragmentShaderOut() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif