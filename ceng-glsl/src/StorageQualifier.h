#ifndef CENG_GLSL_STORAGE_QUALIFIER_H 
#define CENG_GLSL_STORAGE_QUALIFIER_H 

#include <ceng/GLSL/TokenType.h>

#include "INonTerminal.h"

#include <ceng/GLSL/StorageQualifierType.h>

namespace Ceng
{
	class StorageQualifier : public INonTerminal
	{
	public:

		GLSL::StorageQualifierType::value qualifier;

	protected:

	public:

		void Release() override;

		StorageQualifier();
		StorageQualifier(TokenType::value type);
		StorageQualifier(GLSL::StorageQualifierType::value qualifier);

		static GLSL::StorageQualifierType::value FromTokenType(TokenType::value type);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif // !CENG_GLSL_STORAGE_QUALIFIER_H 
