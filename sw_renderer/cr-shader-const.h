/*****************************************************************************
*
* cr-shader-const.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_SHADER_CONST_H
#define _CENG_CR_SHADER_CONST_H

#include <ceng/interfaces/shader-const.h>

#include "shader-const-data.h"

#include "shader-wrapper.h"

namespace Ceng
{
	class CR_ShaderConstHandle : public Ceng::ShaderConstant
	{
	protected:

		Ceng::UINT32 index;

		ShaderWrapper *shader;

	public:

		CR_ShaderConstHandle();

		CR_ShaderConstHandle(const Ceng::UINT32 index,ShaderWrapper *shader);

		~CR_ShaderConstHandle() override;

		void Release() override;

		const CRESULT SetFloat(const Ceng::FLOAT32 value) override;
		const CRESULT SetFloat2(const Ceng::FLOAT32* values) override;
		const CRESULT SetFloat3(const Ceng::FLOAT32* values) override;
		const CRESULT SetFloat4(const Ceng::FLOAT32* values) override;

		const CRESULT SetInt(const Ceng::INT32 value) override;
		const CRESULT SetInt2(const Ceng::INT32* values) override;
		const CRESULT SetInt3(const Ceng::INT32* values) override;
		const CRESULT SetInt4(const Ceng::INT32* values) override;

		const CRESULT SetBool(const Ceng::BOOL value) override;
		const CRESULT SetBool2(const Ceng::BOOL* values) override;
		const CRESULT SetBool3(const Ceng::BOOL* values) override;
		const CRESULT SetBool4(const Ceng::BOOL* values) override;

		const CRESULT SetMatrix_4x4(const Ceng::FLOAT32* values, const Ceng::BOOL transpose) override;
		
	};
};

#endif