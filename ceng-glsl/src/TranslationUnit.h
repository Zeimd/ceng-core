#ifndef CENG_GLSL_TRANSLATION_UNIT_H
#define CENG_GLSL_TRANSLATION_UNIT_H

#include <vector>
#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class TranslationUnit : public INonTerminal
	{
	public:

		std::vector<std::shared_ptr<INonTerminal>> items;

	public:

		TranslationUnit();

		~TranslationUnit() override;

		void Release() override;

		void Append(std::shared_ptr<INonTerminal>& item);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif // !CENG_GLSL_TRANSLATION_UNIT_H
