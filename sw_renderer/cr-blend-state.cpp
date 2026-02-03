#include "cr-blend-state.h"

using namespace Ceng;

CR_BlendState::CR_BlendState(const BlendStateDesc& source)
	: state(source), targetState(source.targets, RenderTargetBlendDesc())
{
	if (source.targets > 0 && source.descList != nullptr)
	{
		memcpy(&targetState[0], source.descList, source.targets * sizeof(RenderTargetBlendDesc));

		state.descList = &targetState[0];
	}
	else
	{
		state.targets = 0;
		state.descList = nullptr;
	}	
}

CR_BlendState::~CR_BlendState()
{

}

void CR_BlendState::Release()
{
	delete this;
}