#ifndef CENG_GLSL_SINGLE_DECLARATION_H
#define CENG_GLSL_SINGLE_DECLARATION_H

#include "INonTerminal.h"
#include "FullySpecifiedType.h"
#include "ConstantExpression.h"
#include "Initializer.h"

namespace Ceng
{
	class SingleDeclaration : public INonTerminal
	{
	public:
		FullySpecifiedType fullType;

		bool hasName;
		Ceng::StringUtf8 name;

		std::shared_ptr<ConstantExpression> arraySizeExpression;

		bool invariant;

		std::shared_ptr<Initializer> initializer;

	public:

		void Release() override;

		// fully_specified_type
		SingleDeclaration(const FullySpecifiedType& fullType);

		// fully_specified_type IDENTIFIER
		SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name);

		// fully_specified_type IDENTIFIER EQUAL initializer
		SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer);

		// fully_specified_type IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET
		SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<ConstantExpression>& arraySizeExpression);

		// fully_specified_type IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET EQUAL initializer
		SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name, std::shared_ptr<ConstantExpression>& arraySizeExpression,
			std::shared_ptr<Initializer>& initializer);

		// INVARIANT IDENTIFIER
		SingleDeclaration(const Ceng::StringUtf8& name);
	};
}

#endif