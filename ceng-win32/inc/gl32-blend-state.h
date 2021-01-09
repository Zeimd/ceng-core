/*****************************************************************************
*
* gl32-blend-state.h
*
* Created By Jari Korkala 10/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_BLEND_STATE_H
#define CENG_GL32_BLEND_STATE_H

#include <gl/glew.h>

#include <ceng/datatypes/return-val.h>

#include <ceng/datatypes/boolean.h>

#include <ceng/interfaces/blend-state.h>

namespace Ceng
{
	class BlendStateDesc;

	class GL32_BlendState : public BlendState
	{
	public:
		Ceng::BOOL blendEnable;
		Ceng::BOOL independentBlend;

		/**
		 * Blend equation for color.
		 */
		GLenum gl_colorEquation;

		/**
		 * Blend equation for alpha.
		 */
		GLenum gl_alphaEquation;
	
		GLenum gl_sourceBlend;
		GLenum gl_destBlend;

		GLenum gl_sourceAlpha;
		GLenum gl_destAlpha;

	public:
		GL32_BlendState();

		GL32_BlendState(const Ceng::BOOL blendEnable, const GLenum gl_colorEquation, const GLenum gl_alphaEquation,
			const GLenum gl_sourceBlend, const GLenum gl_destBlend, const GLenum gl_sourceAlpha, const GLenum gl_destAlpha);

		virtual ~GL32_BlendState();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(BlendStateDesc *desc, GL32_BlendState **statePtr);

		static const Ceng::CRESULT BlendEquation(const BlendOp::value op, GLenum *gl_blendEquation);

		static const Ceng::CRESULT BlendFactor(const BlendType::value type, GLenum *gl_blendFactor);

		void GL_SetState(const GLenum gl_state, const Ceng::BOOL enable);

		void GL_Enable();
		void GL_Disable();
	};
}

#endif