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

		~StructDeclarator() override;

		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		StructDeclarator(const Ceng::StringUtf8& name);

		StructDeclarator(const Ceng::StringUtf8& name, bool implicitArray);

		StructDeclarator(const Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize);

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif // !CENG_GLSL_STRUCT_DECLARATOR_H
