#include "cr-target-tex2d.h"

#include "rtarget-data.h"

using namespace Ceng;

CR_TargetTexture2D::CR_TargetTexture2D(std::shared_ptr<CR_NewTargetData> &data)
	: bufferObject(data)
{
}

CR_TargetTexture2D::~CR_TargetTexture2D()
{
}

void CR_TargetTexture2D::Release()
{
	delete this;
}

std::shared_ptr<CR_NewTargetData> CR_TargetTexture2D::GetTargetData()
{
	return bufferObject;
}

CR_NewTargetData* CR_TargetTexture2D::GetDataPtr()
{
	return bufferObject.get();
}