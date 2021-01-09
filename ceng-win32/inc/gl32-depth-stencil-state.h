/*****************************************************************************
*
* gl32-depth-stencil-state.h
*
* By Jari Korkala 11/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_DEPTH_STENCIL_STATE_H
#define CENG_GL32_DEPTH_STENCIL_STATE_H

#include <gl/glew.h>

#include <ceng/datatypes/return-val.h>

#include <ceng/interfaces/depth-stencil-desc.h>
#include <ceng/interfaces/depth-stencil-state.h>

namespace Ceng
{
	class GL32_DepthStencilState : public DepthStencilState
	{
	protected:
		GL32_DepthStencilState();
	public:
		Ceng::BOOL depthEnable;
		Ceng::BOOL stencilEnable;

		GLboolean gl_depthWrite;

		GLenum gl_depthFunction;

		GLenum gl_frontStencilTest;

		GLenum gl_frontStencilFailOp;
		GLenum gl_frontDepthFailOp;
		GLenum gl_frontDepthPassOp;

		GLint gl_frontStencilRef;
		GLuint gl_frontStencilReadMask;
		GLuint gl_frontStencilWriteMask;

		GLenum gl_backStencilTest;

		GLenum gl_backStencilFailOp;
		GLenum gl_backDepthFailOp;
		GLenum gl_backDepthPassOp;

		GLint gl_backStencilRef;
		GLuint gl_backStencilReadMask;
		GLuint gl_backStencilWriteMask;


	public:

		virtual ~GL32_DepthStencilState();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(const DepthStencilDesc & desc, GL32_DepthStencilState **out_state);

		static void GL_SetState(const GLenum state, const Ceng::BOOL value);

		static const GLenum GetStencilAction(const Ceng::STENCIL_ACTION::value action);
		static const GLenum GetTestType(const Ceng::TEST_TYPE::value test);

		void GL_Enable();
		
	};
}

#endif