/*****************************************************************************
*
* gl32-blend-state.cpp
*
* Created By Jari Korkala 10/11/2015
*
*****************************************************************************/

#include <ceng/datatypes/blend-state-desc.h>

#include "../inc/gl32-blend-state.h"

using namespace Ceng;

GL32_BlendState::GL32_BlendState()
{
}

GL32_BlendState::GL32_BlendState(const Ceng::BOOL blendEnable, const GLenum gl_colorEquation,
	const GLenum gl_alphaEquation, const GLenum gl_sourceBlend, const GLenum gl_destBlend,
	const GLenum gl_sourceAlpha, const GLenum gl_destAlpha)
	: blendEnable(blendEnable), gl_colorEquation(gl_colorEquation), gl_alphaEquation(gl_alphaEquation),
	gl_sourceBlend(gl_sourceBlend), gl_destBlend(gl_destBlend), gl_sourceAlpha(gl_sourceAlpha),
	gl_destAlpha(gl_destAlpha)
{
}


GL32_BlendState::~GL32_BlendState()
{
}

void GL32_BlendState::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_BlendState::GetInstance(BlendStateDesc *desc, GL32_BlendState **statePtr)
{
	if (desc->independentBlend == true)
	{
		return CE_ERR_NOT_SUPPORTED;
	}

	if (desc->alphaToCoverage == true)
	{

	}

	Ceng::BOOL blendEnable = desc->descList[0].blendEnable;

	GLenum gl_colorEquation;

	CRESULT cresult = BlendEquation(desc->descList[0].blendOp, &gl_colorEquation);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	GLenum gl_alphaEquation;

	cresult = BlendEquation(desc->descList[0].blendAlphaOp, &gl_alphaEquation);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	GLenum gl_sourceBlend;
	GLenum gl_destBlend;

	GLenum gl_sourceAlpha;
	GLenum gl_destAlpha;

	cresult = BlendFactor(desc->descList[0].sourceBlend, &gl_sourceBlend);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = BlendFactor(desc->descList[0].destBlend, &gl_destBlend);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = BlendFactor(desc->descList[0].sourceBlendAlpha, &gl_sourceAlpha);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = BlendFactor(desc->descList[0].destBlendAlpha, &gl_destAlpha);
	if (cresult != CE_OK)
	{
		return cresult;
	}


	*statePtr = new GL32_BlendState(blendEnable, gl_colorEquation, 
		gl_alphaEquation, gl_sourceBlend, gl_destBlend, gl_sourceAlpha, gl_destAlpha);

	return CE_OK;
}

const Ceng::CRESULT GL32_BlendState::BlendFactor(const BlendType::value type, GLenum *gl_blendFactor)
{
	switch (type)
	{
	case BlendType::zero:
		*gl_blendFactor = GL_ZERO;
		break;
	case BlendType::one:
		*gl_blendFactor = GL_ONE;
		break;
	case BlendType::source_color:
		*gl_blendFactor = GL_SRC_COLOR;
		break;
	case BlendType::invert_source_color:
		*gl_blendFactor = GL_ONE_MINUS_SRC_COLOR;
		break;
	case BlendType::dest_color:
		*gl_blendFactor = GL_DST_COLOR;
		break;
	case BlendType::invert_dest_color:
		*gl_blendFactor = GL_ONE_MINUS_DST_COLOR;
		break;
	case BlendType::source_alpha:
		*gl_blendFactor = GL_SRC_ALPHA;
		break;
	case BlendType::invert_source_alpha:
		*gl_blendFactor = GL_ONE_MINUS_SRC_ALPHA;
		break;
	case BlendType::dest_alpha:
		*gl_blendFactor = GL_DST_ALPHA;
		break;
	case BlendType::invert_dest_alpha:
		*gl_blendFactor = GL_ONE_MINUS_DST_ALPHA;
		break;
	case BlendType::source_alpha_saturate:
		*gl_blendFactor = GL_SRC_ALPHA_SATURATE;
		break;
	case BlendType::blend_factor:
		*gl_blendFactor = GL_CONSTANT_COLOR;
		break;
	case BlendType::invert_blend_factor:
		*gl_blendFactor = GL_ONE_MINUS_CONSTANT_COLOR;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_BlendState::BlendEquation(const BlendOp::value op,GLenum *gl_blendEquation)
{
	switch (op)
	{
	case BlendOp::add:
		*gl_blendEquation = GL_FUNC_ADD;
		break;
	case BlendOp::subtract:
		*gl_blendEquation = GL_FUNC_SUBTRACT;
		break;
	case BlendOp::reverse_subtract:
		*gl_blendEquation = GL_FUNC_REVERSE_SUBTRACT;
		break;
	case BlendOp::min:
		*gl_blendEquation = GL_MIN;
		break;
	case BlendOp::max:
		*gl_blendEquation = GL_MAX;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

void GL32_BlendState::GL_SetState(const GLenum gl_state, const Ceng::BOOL enable)
{
	if (enable == true)
	{
		glEnable(gl_state);
	}
	else
	{
		glDisable(gl_state);
	}
}

void GL32_BlendState::GL_Enable()
{
	GL_SetState(GL_BLEND, blendEnable);
	
	glBlendFuncSeparate(gl_sourceBlend, gl_destBlend, gl_sourceAlpha, gl_destAlpha);

	glBlendEquationSeparate(gl_colorEquation, gl_alphaEquation);
}

void GL32_BlendState::GL_Disable()
{

}