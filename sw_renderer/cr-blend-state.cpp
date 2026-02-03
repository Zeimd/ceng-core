#include "cr-blend-state.h"

using namespace Ceng;

CR_BlendState::CR_BlendState(const BlendStateDesc& source)
	: state(source)
{

}

CR_BlendState::~CR_BlendState()
{

}

void CR_BlendState::Release()
{
	delete this;
}