/****************************************************************************
*
* cr-pixel-shader.cpp
*
* --------------------------------------------------------
*
* Jari Korkala 8/2014
*
* - Renamed to cr-pixel-shader.cpp
*
* ---------------------------------------------------------
*
* Created By Jari Korkala 1/2012
*
****************************************************************************/

#include "cr-pixel-shader.h"

#include "ShaderLinkInstance.h"

#include "rtarget-data.h"

#include "quad-format.h"

#include "ShaderDatatypeMeta.h"

using namespace Ceng;

CR_PixelShader::CR_PixelShader()
{
	compiled = false;

	cacheLine = 64;

	wrapper.shader = this;

	nullWriter = new Writer_null();

	nextInstance = std::make_shared< Ceng::PixelShaderContextCommon>(this);

	// Set up a NULL input and output registers 
	// to guard against exceptions from use
	// of undefined semantic links

	//nullInput.semantic = Ceng::SHADER_SEMANTIC::POSITION;
	//nullInput.inputFormat = Ceng::SHADER_DATATYPE::UNKNOWN;

	//nullOutput.target = CR_SHADER_TARGET0;
	//nullOutput.bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;
}

CR_PixelShader::~CR_PixelShader()
{
	nullWriter->Release();
}

void CR_PixelShader::Release()
{
	delete this;
}

const Ceng::CRESULT CR_PixelShader::GetLog(Ceng::StringUtf8** log)
{
	return CE_ERR_FAIL;
}

const Ceng::BOOL CR_PixelShader::Compiled()
{
	return compiled;
}

CRESULT CR_PixelShader::ConfigureConstants()
{	
	uniformManager.Build(uniformList);

	return nextInstance->ConfigureUniforms(uniformList, uniformManager);
}

CRESULT CR_PixelShader::GetConstant(const char *variableName,
	Ceng::UINT32& out_index, Ceng::SHADER_DATATYPE::value& out_type)
{
	UINT32 k;

	for(k=0;k<uniformList.size();k++)
	{
		if (strcmp(uniformList[k].name, variableName) == 0)
		{
			out_index = k;
			out_type = CR_SHADER_UNIFORM_EFFECTIVE_TYPE[uniformList[k].dataType];
			return CE_OK;
		}
	}

	return CE_ERR_FAIL;
}

const CRESULT CR_PixelShader::ReadUniform(const Ceng::UINT32 index,void *destBuffer)
{
	memcpy(destBuffer,nextInstance->uniformBuffer.uniformPtr[index],uniformManager.uniformAllocation[index].size);

	return CE_OK;
}


const CRESULT CR_PixelShader::WriteUniform(const Ceng::UINT32 index,void *sourceBuffer)
{
	memcpy(nextInstance->uniformBuffer.uniformPtr[index],sourceBuffer,uniformManager.uniformAllocation[index].size);

	return CE_OK;
}

CRESULT CR_PixelShader::SetShaderLink(ShaderLinkInstance* link)
{
	nextInstance->link = link;

	return CE_OK;
}

const CRESULT CR_PixelShader::SetTextureUnits(std::vector<TextureUnit> &source)
{
	nextInstance->textureUnits = &source;
	return CE_OK;
}

CRESULT CR_PixelShader::SetRenderTargets(Ceng::UINT32 amount,
	std::shared_ptr<CR_NewTargetData> targets[],
	std::shared_ptr<CR_NewTargetData> &depthStencil,
	CombinedBlendState* blendState)
{

	UINT32 k;

	UINT32 tempFlags = 0;

	nextInstance->activeRenderTargets = amount;

	nextInstance->blendState = blendState;

	for(k=0;k<amount;k++)
	{
		nextInstance->targetHandles[k] = targets[k];

		if (targets[k] != nullptr)
		{
			Pshader::PshaderTargetWriter* writer = targets[k]->GetWriter(blendState);

			if (writer != nullptr)
			{
				nextInstance->targetWriters[k].writer = writer;
				nextInstance->targetWriters[k].isNull = false;
			}
			else
			{
				nextInstance->targetWriters[k].writer = nullWriter;
				nextInstance->targetWriters[k].isNull = true;
			}			
		}
		else
		{
			nextInstance->targetWriters[k].writer = nullWriter;
			nextInstance->targetWriters[k].isNull = true;
		}		
	}

	return CE_OK;	
}

