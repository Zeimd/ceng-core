#ifndef CENG_GLSL_AST_TRANSLATION_UNIT_H
#define CENG_GLSL_AST_TRANSLATION_UNIT_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_TranslationUnit : public IASTNode
		{
		public:

		public:

			AST_TranslationUnit();

			~AST_TranslationUnit() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif