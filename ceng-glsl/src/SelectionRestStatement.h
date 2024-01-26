#ifndef CENG_GLSL_SELECTION_REST_STATEMENT_H
#define CENG_GLSL_SELECTION_REST_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class SelectionRestStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif