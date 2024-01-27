#ifndef CENG_GLSL_STRUCT_DECLARATOR_H
#define CENG_GLSL_STRUCT_DECLARATOR_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class Expression;

	class StructDeclarator : public INonTerminal
	{
	public:
		Ceng::StringUtf8 name;

		bool isArray;
		std::shared_ptr<Expression> arraySize;


	public:

		void Release() override;

		Ceng::StringUtf8 ToString() const override;

		StructDeclarator(Ceng::StringUtf8& name);

		StructDeclarator(Ceng::StringUtf8& name, bool implicitArray);

		StructDeclarator(Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize);
	};
}

#endif // !CENG_GLSL_STRUCT_DECLARATOR_H