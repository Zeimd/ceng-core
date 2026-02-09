/*****************************************************************************
*
* texture-unit.cpp
*
* Created By Jari Korkala 6/3/2015
*
*****************************************************************************/

#include "texture-unit.h"

#include <ceng/swshader/PShaderTextureUnitSampler.h>

#include "cr-shader-view.h"

using namespace Ceng;

TextureUnit::TextureUnit()
	: sampler(nullptr), view(nullptr), samplerObject(nullptr)
{

}

TextureUnit::TextureUnit(CR_SamplerState* sampler, CR_ShaderResourceView* view)
	: sampler(sampler), view(view), samplerObject(nullptr)
{

}

TextureUnit::TextureUnit(const TextureUnit& source)
	: sampler(source.sampler), view(source.view), samplerObject(nullptr)
{

}

TextureUnit::~TextureUnit()
{
	if (samplerObject != nullptr)
	{
		samplerObject->Release();
	}
}

void TextureUnit::ConfigureState()
{
	if (samplerObject != nullptr)
	{
		samplerObject->Release();
		samplerObject = nullptr;
	}

	if (view == nullptr || sampler == nullptr)
	{
		samplerObject = nullptr;
		return;
	}

	samplerObject = view->GetSampler(sampler);
}