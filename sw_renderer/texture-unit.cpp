/*****************************************************************************
*
* texture-unit.cpp
*
* Created By Jari Korkala 6/3/2015
*
*****************************************************************************/

#include "texture-unit.h"

using namespace Ceng;

TextureUnit::TextureUnit()
	: sampler(nullptr), view(nullptr), samplerObject(nullptr)
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