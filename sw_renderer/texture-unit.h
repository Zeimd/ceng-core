/*****************************************************************************
*
* texture-unit.h
*
* Created By Jari Korkala 6/3/2015
*
*****************************************************************************/

#ifndef CENG_TEXTURE_UNIT_H
#define CENG_TEXTURE_UNIT_H

#include <memory>

#include <ceng/interfaces/shader-resource-view.h>
#include <ceng/datatypes/return-val.h>

namespace Ceng
{
	class CR_SamplerState;
	class CR_ShaderResourceView;

	namespace Pshader
	{
		class PShaderTextureUnitSampler;
	}
	

	class TextureUnit
	{
	public:

		CR_SamplerState *sampler;

		CR_ShaderResourceView *view;

		Pshader::PShaderTextureUnitSampler* samplerObject;

	public:
		TextureUnit();
		TextureUnit(CR_SamplerState* sampler, CR_ShaderResourceView* view);
		TextureUnit(const TextureUnit& source);

		~TextureUnit();

		const CRESULT SetSampler(CR_SamplerState *sampler);
		const CRESULT SetView(CR_ShaderResourceView *view);

		void ConfigureState();

	};
}

#endif