#ifndef CENG_GLSL_AST_DEFAULT_PRECISION_H
#define CENG_GLSL_AST_DEFAULT_PRECISION_H

#include "IASTNode.h"

#include "PrecisionQualifierType.h"

namespace Ceng
{
	namespace GLSL
	{
		enum class PrecisionTarget
		{
			integer,
			floating,
		};

		class AST_DefaultPrecision : public IASTNode
		{
		public:

			PrecisionQualifierType::value precision;

			PrecisionTarget target;

		public:

			AST_DefaultPrecision(PrecisionQualifierType::value precision, PrecisionTarget target);

			~AST_DefaultPrecision() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}


#endif