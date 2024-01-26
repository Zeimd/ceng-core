#ifndef CENG_GLSL_STORAGE_QUALIFIER_H 
#define CENG_GLSL_STORAGE_QUALIFIER_H 

#include <ceng/GLSL/TokenType.h>

#include "INonTerminal.h"

#include "StorageQualifierType.h"

namespace Ceng
{
	class StorageQualifier : public INonTerminal
	{
	public:

		StorageQualifierType::value qualifier;

	protected:

	public:

		void Release() override;

		StorageQualifier();
		StorageQualifier(TokenType::value type);
		StorageQualifier(StorageQualifierType::value qualifier);

		static StorageQualifierType::value FromTokenType(TokenType::value type);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif // !CENG_GLSL_STORAGE_QUALIFIER_H 
