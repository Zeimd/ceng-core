/*****************************************************************************
*
* gl32-uniform-mat4.h
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#ifndef GL32_UNIFORM_MAT4_H
#define GL32_UNIFORM_MAT4_H

#include <gl/glew.h>

#include "gl32-shader-const.h"

namespace Ceng
{
	class GL32_UniformMat4 : public GL32_ShaderConstant
	{
	public:
		GLboolean gl_transpose;
		Ceng::FLOAT32 values[16];

	public:
		GL32_UniformMat4();
		GL32_UniformMat4(GLint index, Ceng::GL32_ShaderProgram *program);

		virtual ~GL32_UniformMat4();

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

		virtual const CRESULT SetMatrix_4x4(const Ceng::FLOAT32 *values,const Ceng::BOOL transpose) override;

		virtual void GL_UpdateThis() override;
	};
}

#endif