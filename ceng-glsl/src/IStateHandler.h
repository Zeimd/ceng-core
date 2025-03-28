#ifndef CENG_GLSL_ISTATEHANDLER_H
#define CENG_GLSL_ISTATEHANDLER_H

#include "HandlerReturn.h"
#include <ceng/GLSL/Token.h>

namespace Ceng
{
	class GLSL_Parser;

	class IStateHandler
	{
	public:
		virtual HandlerReturn Reduction(GLSL_Parser* parser) = 0;

		virtual HandlerReturn Shift(GLSL_Parser* parser, const Token& token) = 0;

		virtual HandlerReturn Goto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal) = 0;

		// Should be used in a situation where state stack top is an operator
		HandlerReturn DefaultExpressionShift(GLSL_Parser* parser, const Token& token);

		// Should be used in a situation where state stack top is an operator
		HandlerReturn DefaultExpressionGoto(GLSL_Parser* parser, std::shared_ptr<INonTerminal>& nonTerminal);
	};

}

#endif