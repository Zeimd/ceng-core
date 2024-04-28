#ifndef CENG_GLSL_ARRAY_INDEX_H
#define CENG_GLSL_ARRAY_INDEX_H

#include <memory>
#include <variant>

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	namespace GLSL
	{
		class VariableExpression;

		using ArrayIndexContent = std::variant<Ceng::UINT32, std::shared_ptr<VariableExpression>>;

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

			//ArrayIndex(const ArrayIndex& source);

			ArrayIndex();

			ArrayIndex(bool implicit);

			ArrayIndex(Ceng::INT32 value);
			ArrayIndex(Ceng::UINT32 value);
			ArrayIndex(const VariableExpression& expression);

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;

			bool operator == (const ArrayIndex& other) const;

			// Array with explicit size?
			bool HasSize() const;

			// Is this considered an array?
			bool IsArray() const;

			Ceng::UINT32 GetInt() const;

			const std::shared_ptr<VariableExpression>& GetVariable() const;
		};
	}
}

#endif