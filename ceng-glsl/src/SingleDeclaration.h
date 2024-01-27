#ifndef CENG_GLSL_SINGLE_DECLARATION_H
#define CENG_GLSL_SINGLE_DECLARATION_H

#include "INonTerminal.h"
#include "FullySpecifiedType.h"
#include "ConstantExpression.h"
#include "Initializer.h"

#include "DeclarationData.h"

namespace Ceng
{
	class SingleDeclaration : public INonTerminal
	{
	public:
		std::shared_ptr<FullySpecifiedType> fullType;
		bool invariant;
		
		DeclarationData data;

	public:

		void Release() override;

		// fully_specified_type
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType);

		// fully_specified_type IDENTIFIER
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name);

		// fully_specified_type IDENTIFIER EQUAL initializer
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Initializer>& initializer);

		// fully_specified_type IDENTIFIER LEFT_BRACKET RIGHT_BRACKET
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, bool undefinedArray);

		// fully_specified_type IDENTIFIER LEFT_BRACKET RIGHT_BRACKET EQUAL initializer
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, bool undefinedArray, std::shared_ptr<Initializer>& initializer);

		// fully_specified_type IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression);

		// fully_specified_type IDENTIFIER LEFT_BRACKET {constant_expression} RIGHT_BRACKET EQUAL initializer
		SingleDeclaration(std::shared_ptr<FullySpecifiedType>& fullType, const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySizeExpression,
			std::shared_ptr<Initializer>& initializer);

		// INVARIANT IDENTIFIER
		SingleDeclaration(const Ceng::StringUtf8& name);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif