/*****************************************************************************
*
* gl32-depth-stencil-state.h
*
* By Jari Korkala 11/11/2015
*
*****************************************************************************/

#include "../inc/gl32-depth-stencil-state.h"

using namespace Ceng;

GL32_DepthStencilState::GL32_DepthStencilState()
{
}

GL32_DepthStencilState::~GL32_DepthStencilState()
{
}

void GL32_DepthStencilState::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_DepthStencilState::GetInstance(const DepthStencilDesc & desc, GL32_DepthStencilState **out_state)
{
	GL32_DepthStencilState *temp = new GL32_DepthStencilState();

	temp->depthEnable = desc.depthEnable;
	temp->stencilEnable = desc.stencilEnable;

	temp->gl_depthFunction = GetTestType(desc.depthTest);

	temp->gl_depthWrite = GL_FALSE;
	if (desc.depthWrite == true)
	{
		temp->gl_depthWrite = GL_TRUE;
	}	

	// Front face

	temp->gl_frontStencilTest = GetTestType(desc.frontFace.stencilTest);

	temp->gl_frontStencilFailOp = GetStencilAction(desc.frontFace.stencilFail);
	temp->gl_frontDepthFailOp = GetStencilAction(desc.frontFace.depthFail);
	temp->gl_frontDepthPassOp = GetStencilAction(desc.frontFace.depthPass);

	temp->gl_frontStencilRef = desc.frontFace.stencilRef;
	temp->gl_frontStencilReadMask = desc.frontFace.stencilReadMask;
	temp->gl_frontStencilWriteMask = desc.frontFace.stencilWriteMask;

	// Back face

	temp->gl_backStencilTest = GetTestType(desc.backFace.stencilTest);

	temp->gl_backStencilFailOp = GetStencilAction(desc.backFace.stencilFail);
	temp->gl_backDepthFailOp = GetStencilAction(desc.backFace.depthFail);
	temp->gl_backDepthPassOp = GetStencilAction(desc.backFace.depthPass);

	temp->gl_backStencilRef = desc.backFace.stencilRef;
	temp->gl_backStencilReadMask = desc.backFace.stencilReadMask;
	temp->gl_backStencilWriteMask = desc.backFace.stencilWriteMask;

	*out_state = temp;

	return CE_OK;
}

const GLenum GL32_DepthStencilState::GetStencilAction(const Ceng::STENCIL_ACTION::value action)
{
	switch (action)
	{
	case STENCIL_ACTION::KEEP:
		return GL_KEEP;
	case STENCIL_ACTION::INCREMENT:
		return GL_INCR_WRAP;
	case STENCIL_ACTION::INCREMENT_SAT:
		return GL_INCR;
	case STENCIL_ACTION::DECREMENT:
		return GL_DECR_WRAP;
	case STENCIL_ACTION::DECREMENT_SAT:
		return GL_DECR;
	case STENCIL_ACTION::ZERO:
		return GL_ZERO;
	case STENCIL_ACTION::SET_REF:
		return GL_REPLACE;
	case STENCIL_ACTION::BIT_INVERT:
		return GL_INVERT;
	}

	return GL_KEEP;
}

const GLenum GL32_DepthStencilState::GetTestType(const Ceng::TEST_TYPE::value test)
{
	switch (test)
	{
	case TEST_TYPE::ALWAYS_PASS:
		return GL_ALWAYS;
	case TEST_TYPE::NEVER_PASS:
		return GL_NEVER;
	case TEST_TYPE::LESS:
		return GL_LESS;
	case TEST_TYPE::LESS_EQ:
		return GL_LEQUAL;
	case TEST_TYPE::EQUAL:
		return GL_EQUAL;
	case TEST_TYPE::ABOVE_EQ:
		return GL_GEQUAL;
	case TEST_TYPE::ABOVE:
		return GL_GREATER;
	case TEST_TYPE::NOT_EQUAL:
		return GL_NOTEQUAL;
	}

	return GL_LESS;
}

void GL32_DepthStencilState::GL_SetState(const GLenum state, const Ceng::BOOL value)
{
	if (value == true)
	{
		glEnable(state);
	}
	else
	{
		glDisable(state);
	}
}

void GL32_DepthStencilState::GL_Enable()
{
	GL_SetState(GL_DEPTH_TEST, depthEnable);
	GL_SetState(GL_STENCIL_TEST, stencilEnable);

	glDepthMask(gl_depthWrite);

	glDepthFunc(gl_depthFunction);

	glStencilFuncSeparate(GL_FRONT, gl_frontStencilTest, gl_frontStencilRef, gl_frontStencilReadMask);

	glStencilOpSeparate(GL_FRONT, gl_frontStencilFailOp, gl_frontDepthFailOp,gl_frontDepthPassOp);

	glStencilMaskSeparate(GL_FRONT, gl_frontStencilWriteMask);

	glStencilFuncSeparate(GL_BACK, gl_backStencilTest, gl_backStencilRef, gl_backStencilReadMask);

	glStencilOpSeparate(GL_BACK, gl_backStencilFailOp, gl_backDepthFailOp, gl_backDepthPassOp);

	glStencilMaskSeparate(GL_BACK, gl_backStencilWriteMask);

}