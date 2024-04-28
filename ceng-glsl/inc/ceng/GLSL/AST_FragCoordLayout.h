#ifndef CENG_GLSL_AST_FRAG_COORD_LAYOUT_H
#define CENG_GLSL_AST_FRAG_COORD_LAYOUT_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_FragCoordLayout : public IASTNode
		{
		public:

			bool originUpperLeft;
			bool pixelCenterInt;

		public:

			AST_FragCoordLayout(bool originUpperLeft, bool pixelCenterInt);

			~AST_FragCoordLayout() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif