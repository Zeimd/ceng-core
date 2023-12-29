#ifndef CR_SHADER_PROGRAM_H
#define CR_SHADER_PROGRAM_H

#include <ceng/interfaces/shader-program.h>

namespace Ceng
{
	class CR_VertexShader;
	class CR_PixelShader;

	class CR_ShaderProgram : public ShaderProgram
	{
	protected:

		CR_ShaderProgram()
		{

		}

		~CR_ShaderProgram() override
		{

		}

	public:

		CR_VertexShader* vShader;
		CR_PixelShader* pShader;

	public:

		static Ceng::CRESULT GetInstance(CR_VertexShader* vShader, CR_PixelShader* pShader,CR_ShaderProgram** out_program);

		void Release() override;

		const Ceng::CRESULT GetConstant(const char* variableName, Ceng::ShaderConstant** handle) override;

		const Ceng::CRESULT GetLog(Ceng::StringUtf8** log) override;

		const Ceng::BOOL Linked() override;
	};
}

#endif