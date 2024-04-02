#ifndef CENG_GLSL_DECLARATION_DATA_H
#define CENG_GLSL_DECLARATION_DATA_H

#include <memory>

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	class Expression;
	class Initializer;

	class DeclarationData
	{
	public:
		bool empty;

		Ceng::StringUtf8 name;

		// Indicates an empty array when *arraySizeExpression* is NULL.
		bool isArray;

		std::shared_ptr<Expression> arraySizeExpression;

		std::shared_ptr<Initializer> initializer;

	public:

		// Empty
		DeclarationData();

		// IDENTIFIER
		DeclarationData(const Ceng::StringUtf8& name);

		// IDENTIFIER EQUAL initializer
		DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer);

		// IDENTIFIER LEFT_BRACKET RIGHT_BRACKET
		DeclarationData(const Ceng::StringUtf8& name, bool undefinedArray);

		// IDENTIFIER LEFT_BRACKET RIGHT_BRACKET EQUAL initializer
		DeclarationData(const Ceng::StringUtf8& name, bool undefinedArray, std::shared_ptr<Initializer>& initializer);

		// IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET
		DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression);

		// IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET EQUAL initializer
		DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression,
			std::shared_ptr<Initializer>& initializer);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const;
	};
}

#endif // !CENG_GLSL_DECLARATION_DATA_H
