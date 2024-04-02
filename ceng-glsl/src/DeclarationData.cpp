#include "DeclarationData.h"
#include "Expression.h"
#include "Initializer.h"

using namespace Ceng;

// Empty
DeclarationData::DeclarationData()
	: empty(true)
{

}

// IDENTIFIER
DeclarationData::DeclarationData(const Ceng::StringUtf8& name)
	: empty(false), name(name), isArray(false), arraySizeExpression(nullptr), initializer(nullptr)
{

}

// IDENTIFIER EQUAL initializer
DeclarationData::DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer)
	: empty(false), name(name), isArray(false), arraySizeExpression(nullptr), initializer(initializer)
{

}

// IDENTIFIER LEFT_BRACKET RIGHT_BRACKET
DeclarationData::DeclarationData(const Ceng::StringUtf8& name, bool undefinedArray)
	: empty(false), name(name), isArray(true), arraySizeExpression(nullptr), initializer(nullptr)
{

}

// IDENTIFIER LEFT_BRACKET RIGHT_BRACKET EQUAL initializer
DeclarationData::DeclarationData(const Ceng::StringUtf8& name, bool undefinedArray, std::shared_ptr<Initializer>& initializer)
	: empty(false), name(name), isArray(true), arraySizeExpression(nullptr), initializer(initializer)
{

}

// IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET
DeclarationData::DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression)
	: empty(false), name(name), isArray(true), arraySizeExpression(arraySizeExpression), initializer(nullptr)
{

}

// IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET EQUAL initializer
DeclarationData::DeclarationData(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression,
	std::shared_ptr<Initializer>& initializer)
	: empty(false), name(name), isArray(true), arraySizeExpression(arraySizeExpression), initializer(initializer)
{

}

Ceng::StringUtf8 DeclarationData::ToString(unsigned int indentLevel) const
{
	if (empty)
	{
		return "";
	}

	Ceng::StringUtf8 out;

	//if (!empty)
	//{
		out += name;
	//}

	if (isArray)
	{
		out += '[';

		if (arraySizeExpression != nullptr)
		{
			out += arraySizeExpression->ToString(indentLevel);
		}

		out += ']';
	}

	if (initializer != nullptr)
	{
		out += " = ";
		out += initializer->ToString(indentLevel);
	}

	return out;
}