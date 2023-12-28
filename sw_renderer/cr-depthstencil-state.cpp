#include "cr-depthstencil-state.h"

using namespace Ceng;

CR_DepthStencilState::CR_DepthStencilState(const DepthStencilDesc& desc)
	: desc(desc)
{

}

CR_DepthStencilState::~CR_DepthStencilState()
{

}

void CR_DepthStencilState::Release()
{
	delete this;
}