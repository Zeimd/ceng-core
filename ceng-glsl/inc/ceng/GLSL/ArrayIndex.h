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
			implicit,
			uint_literal,
			variable,
			invalid_value,
		};

		class ArrayIndex
		{
		public:
			ArrayIndexType indexType;

			ArrayIndexContent value;

			ArrayIndex(bool implicit);

			ArrayIndex(Ceng::INT32 value);
			ArrayIndex(Ceng::UINT32 value);
			ArrayIndex(Ceng::StringUtf8 variable);
			ArrayIndex(Ceng::StringUtf8 variable, bool invalid);

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;
		};
	}
}

#endif