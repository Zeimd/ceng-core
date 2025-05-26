/*****************************************************************************
*
* cr-pshader.h
*
* By Jari Korkala 2/2012
*
* Pixel shader declarations moved here form "crender.h"
*
* Update 4/2013 : Moved PixelShaderInput and PixelShaderTarget to
*                 separate files.
*
*****************************************************************************/

#ifndef _CENG_CR_PSHADER_H
#define _CENG_CR_PSHADER_H

#include <memory>

#include <ceng/interfaces/pixel-shader.h>

#include <ceng/datatypes/pshader-input-desc.h>
#include <ceng/datatypes/pshader-output-desc.h>
#include <ceng/datatypes/shader-uniform-desc.h>

#include "crender-base.h"

#include "triangle-data.h"

#include "cr-shader-const.h"

#include <ceng/datatypes/pshader-input-desc.h>
#include "pshader-input.h"

#include <ceng/datatypes/pshader-output-desc.h>
#include "pshader-output.h"

#include "pshader-instance.h"

#include "pshader-wrapper.h"

#include "texture-unit.h"

#include "PixelShaderInstanceCommon.h"

namespace Ceng
{
	class CR_NewTargetData;

	
	struct CR_QuadHeader;

	class CR_PixelShader : public Ceng::PixelShader
	{
	public:

		Ceng::UINT32 cacheLine;

		PixelShaderWrapper wrapper;

		std::shared_ptr<PixelShaderInstanceCommon> nextInstance;
		std::shared_ptr<PixelShaderInstanceCommon> currentInstance;

		std::vector<PixelShaderInputDesc> inputSemantics;

		std::vector<PixelShaderOutputDesc> renderTargets;

		CR_NewTargetData *targetHandle[2+8];

		std::vector<ShaderUniformDesc> uniformList;

		Ceng::UINT32 uniformBufferSize;

		UINT32 outputFlags;

		UINT32 disableStencil;
		UINT32 disableDepth;

		CR_PixelShaderInput nullInput;
		CR_psOutputRegister nullOutput;

	protected:

		BOOL compiled;

	public:
		CR_PixelShader();
		~CR_PixelShader() override;

		void Release() override;

		CRESULT GetConstant(const char* variableName,
			Ceng::UINT32& out_index, Ceng::SHADER_DATATYPE::value& out_type);

		const Ceng::CRESULT GetLog(Ceng::StringUtf8** log) override;

		const Ceng::BOOL Compiled() override;

	public:

		CRESULT ConfigureConstants();

		const CRESULT ReadUniform(const Ceng::UINT32 index,void *destBuffer);

		const CRESULT WriteUniform(const Ceng::UINT32 index,void *sourceBuffer);

		CRESULT SetShaderLink(ShaderLinkInstance *link);

		const CRESULT SetTextureUnits(std::vector<TextureUnit> &source);

		CRESULT SetRenderTargets(UINT32 amount,std::shared_ptr<CR_NewTargetData> targets[],
									std::shared_ptr<CR_NewTargetData> &depthStencil);

		CRESULT SetGradients(CR_FloatFragment *floatVariable,CR_DoubleFragment *doubleVariable,
								UINT8 *variableStep);

		const CRESULT GetInstances(std::vector<std::shared_ptr<PixelShaderInstance>> &instances,
									const Ceng::UINT32 renderThreads);

	};

}; // namespace Ceng

#endif // Include guard