/*****************************************************************************
*
* gl32-uniform-sampler2d.h
*
* Created By Jari Korkala 26/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_UNIFORM_SAMPLER_2D_H
#define CENG_GL32_UNIFORM_SAMPLER_2D_H

#include <gl/glew.h>

#include "gl32-shader-const.h"

namespace Ceng
{
	class GL32_UniformSampler2D : public GL32_ShaderConstant
	{
	public:
		Ceng::UINT32 value;

	public:
		GL32_UniformSampler2D();
		GL32_UniformSampler2D(GLint index, Ceng::GL32_ShaderProgram *program);

		virtual ~GL32_UniformSampler2D();

		virtual void Release() override;

		virtual const CRESULT SetFloat(const Ceng::FLOAT32 value) override;
		virtual const CRESULT SetFloat2(const Ceng::FLOAT32 *values) override;
		virtual const CRESULT SetFloat3(const Ceng::FLOAT32 *values) override;
		virtual const CRESULT SetFloat4(const Ceng::FLOAT32 *values) override;

		virtual const CRESULT SetInt(const Ceng::INT32 value) override;
		virtual const CRESULT SetInt2(const Ceng::INT32 *values) override;
		virtual const CRESULT SetInt3(const Ceng::INT32 *values) override;
		virtual const CRESULT SetInt4(const Ceng::INT32 *values) override;

		virtual const CRESULT SetBool(const Ceng::BOOL value) override;
		virtual const CRESULT SetBool2(const Ceng::BOOL *values) override;
		virtual const CRESULT SetBool3(const Ceng::BOOL *values) override;
		virtual const CRESULT SetBool4(const Ceng::BOOL *values) override;

		virtual const CRESULT SetMatrix_4x4(const Ceng::FLOAT32 *values, const Ceng::BOOL transpose) override;

		virtual void GL_UpdateThis() override;
	};
}

#endif