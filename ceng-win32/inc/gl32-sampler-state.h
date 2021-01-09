/*****************************************************************************
*
* gl32-sampler-state.h
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_SAMPLER_STATE_H
#define CENG_GL32_SAMPLER_STATE_H

#include <gl/glew.h>

#include <ceng/datatypes/return-val.h>

#include <ceng/interfaces/sampler-state.h>
#include <ceng/datatypes/sampler-state-desc.h>

namespace Ceng
{
	class GL32_SamplerState : public SamplerState
	{
	protected:
		GL32_SamplerState();
	public:
		GLuint gl_samplerID;
	public:
		
		GL32_SamplerState(const GLuint gl_samplerID);

		virtual ~GL32_SamplerState();
		virtual void Release();

		static const Ceng::CRESULT GetInstance(const SamplerStateDesc &desc, GL32_SamplerState **output);

		static const Ceng::CRESULT TranslateWrapMode(const Ceng::TextureAddressMode::value mode, GLint *gl_mode);

		static const Ceng::CRESULT TranslateMinFilter(const Ceng::TextureMinFilter::value mode, GLint *gl_mode);

		static const Ceng::CRESULT TranslateMagFilter(const Ceng::TextureMagFilter::value mode, GLint *gl_mode);

		virtual void GetSamplerDesc(SamplerStateDesc &desc) override;
	};
}

#endif