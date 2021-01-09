/*****************************************************************************
*
* gl32-uniform-empty.h
*
* Created By Jari Korkala 4/11/2015
*
* 
*
*****************************************************************************/

#ifndef GL32_UNIFORM_EMPTY_H
#define GL32_UNIFORM_EMPTY_H

#include "gl32-shader-const.h"

namespace Ceng
{
	class GL32_UniformEmpty : public GL32_ShaderConstant
	{
	public:

	public:
		GL32_UniformEmpty();

		virtual ~GL32_UniformEmpty();

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