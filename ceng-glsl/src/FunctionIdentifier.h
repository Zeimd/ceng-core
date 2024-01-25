#ifndef CENG_GLSL_FUNCTION_IDENTIFIER_H
#define CENG_GLSL_FUNCTION_IDENTIFIER_H

#include "INonTerminal.h"
#include "TypeSpecifier.h"

namespace Ceng
{
	namespace FunctionType
	{
		enum value
		{
			constructor,
			normal,
			member,
		};
	}


	class FunctionIdentifier : public INonTerminal
	{
	public:
		std::shared_ptr<TypeSpecifier> typeSpec;

		Ceng::StringUtf8 name;

		FunctionType::value funcType;

	public:
		void Release() override;

		FunctionIdentifier(std::shared_ptr<TypeSpecifier>& typeSpec);

		FunctionIdentifier(const Ceng::StringUtf8& name);
	};
}

#endif