#ifndef CR_UNIFORM_MAT4_H
#define CR_UNIFORM_MAT4_H

#include "cr-shader-const.h"

namespace Ceng
{
	class CR_UniformMat4 : public CR_ShaderConstant
	{
	public:
		Ceng::FLOAT32 values[16];

	protected:

		~CR_UniformMat4() override;

	public:
		CR_UniformMat4();
		CR_UniformMat4(Ceng::UINT32 index, Ceng::CR_ShaderProgram* program);


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