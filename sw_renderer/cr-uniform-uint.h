#ifndef CR_UNIFORM_UINT_H
#define CR_UNIFORM_UINT_H

#include "cr-shader-const.h"

namespace Ceng
{
	class CR_UniformUint : public CR_ShaderConstant
	{
	public:
		Ceng::UINT32 value;

	protected:

		~CR_UniformUint() override;

	public:
		CR_UniformUint();
		CR_UniformUint(Ceng::UINT32 index, Ceng::ShaderWrapper* wrapper);


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

		void UpdateThis() override;
	};
}

#endif