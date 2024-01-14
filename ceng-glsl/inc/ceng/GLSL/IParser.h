#ifndef CENG_GLSL_IPARSER_H
#define CENG_GLSL_IPARSER_H

#include <ceng/datatypes/ce-string.h>
#include <ceng/datatypes/return-val.h>

#include "Token.h"
#include "AbstractSyntaxTree.h"
#include "Log.h"

namespace Ceng
{
	namespace GLSL
	{
		class IParser
		{
		protected:
			IParser()
			{

			}

			virtual ~IParser()
			{

			}
		public:
			virtual void Release() = 0;

			virtual const Log& GetLog() const = 0;

			virtual CRESULT Parse(const std::vector<Token>& in_tokens, AbstractSyntaxTree& output) = 0;
		};
	}
	
}

#endif