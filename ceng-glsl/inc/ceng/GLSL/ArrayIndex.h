#ifndef CENG_GLSL_ARRAY_INDEX_H
#define CENG_GLSL_ARRAY_INDEX_H

#include <variant>

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	namespace GLSL
	{
		using ArrayIndexContent = std::variant<Ceng::UINT32, Ceng::StringUtf8>;

		enum class ArrayIndexType
		{
			unused,
			uint_literal,
			variable,
		};

		class ArrayIndex
		{
		public:
			ArrayIndexType indexType;

			ArrayIndexContent value;

			ArrayIndex();

			ArrayIndex(Ceng::UINT32 value);
			ArrayIndex(Ceng::StringUtf8 variable);

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;
		};
	}
}

#endif