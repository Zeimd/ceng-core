#ifndef CENG_GLSL_STORAGE_QUALIFIER_H 
#define CENG_GLSL_STORAGE_QUALIFIER_H 

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
		StorageQualifier(StorageQualifierType::value qualifier);
	};
}

#endif // !CENG_GLSL_STORAGE_QUALIFIER_H 
