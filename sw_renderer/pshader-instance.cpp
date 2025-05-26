/*****************************************************************************
*
* pshader-instance.cpp
*
* Created By Jari Korkala 2/9/2014
*
*****************************************************************************/

#include "pshader-instance.h"

#include <ceng/enums/pshader-output-semantic.h>

#include "cr-pixel-shader.h"

#include "quad-format.h"

#include "task-pshader.h"
#include "rasterizer-batch.h"

#include "cr-shader-const.h"

#include "ShaderLinkInstance.h"

#include "shader-link.h"

#include "pshader-types.h"
#include "pshader-util.h"

using namespace Ceng;

PixelShaderInstance::~PixelShaderInstance()
{
	
}

CRESULT PixelShaderInstance::GetInstance(std::shared_ptr<PixelShaderInstanceCommon>& common, std::shared_ptr<PixelShaderInstance>& out)
{
	out = nullptr;

	PixelShaderInstance* temp = new PixelShaderInstance(common);

	CRESULT cresult;

	cresult = temp->ConfigureInput(common->shader->inputSemantics);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = temp->ConfigureOutput(common->shader->renderTargets);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = temp->SetFragmentFormat(common->shader->inputSemantics, common->shader->renderTargets);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = temp->SetRenderTargets(common->shader->renderTargets);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = temp->ConfigureLocals();

	if (cresult != CE_OK)
	{
		return cresult;
	}

	out = std::shared_ptr<PixelShaderInstance>(temp);

	return CE_OK;
}

PixelShaderInstance::PixelShaderInstance(std::shared_ptr<PixelShaderInstanceCommon>& common)
{	
	this->common = common;

	quadTargetStart = 0;

	perspectiveTemp = AlignedBuffer<Ceng::UINT8>(64,common->shader->cacheLine);

	coverageAddress = NULL;
	inputBaseAddress = NULL;
	stepBufferPtr = NULL;
	
	IN_POSITION = &common->shader->nullInput;
	IN_SCREENPOS = &common->shader->nullInput;

	IN_NORMAL = &common->shader->nullInput;
	IN_BINORMAL = &common->shader->nullInput;
	IN_TANGENT = &common->shader->nullInput;

	IN_COLOR0 = &common->shader->nullInput;
	IN_COLOR1 = &common->shader->nullInput;

	IN_TEXCOORD0 = &common->shader->nullInput;
	IN_TEXCOORD1 = &common->shader->nullInput;
	IN_TEXCOORD2 = &common->shader->nullInput;
	IN_TEXCOORD3 = &common->shader->nullInput;
	IN_TEXCOORD4 = &common->shader->nullInput;
	IN_TEXCOORD5 = &common->shader->nullInput;
	IN_TEXCOORD6 = &common->shader->nullInput;
	IN_TEXCOORD7 = &common->shader->nullInput;

	OUT_DEPTH = &common->shader->nullOutput;
	OUT_STENCIL = &common->shader->nullOutput;

	OUT_TARGET0 = &common->shader->nullOutput;
	OUT_TARGET1 = &common->shader->nullOutput;
	OUT_TARGET2 = &common->shader->nullOutput;
	OUT_TARGET3 = &common->shader->nullOutput;
	OUT_TARGET4 = &common->shader->nullOutput;
	OUT_TARGET5 = &common->shader->nullOutput;
	OUT_TARGET6 = &common->shader->nullOutput;
	OUT_TARGET7 = &common->shader->nullOutput;
	
}

const CRESULT PixelShaderInstance::ConfigureInput(std::vector<PixelShaderInputDesc> &inputSemantics)
{
	UINT32 k;

	inputRegisters = AlignedBuffer<CR_PixelShaderInput>(
			Ceng::UINT32(inputSemantics.size()),common->shader->cacheLine);

	// Set up references to input variables
	for(k=0;k<inputSemantics.size();k++)
	{
		inputRegisters[k].stepBuffer = &stepBufferPtr;
		inputRegisters[k].perspective = (void*)perspectiveTemp;

		switch(inputSemantics[k].semantic)
		{
		case Ceng::SHADER_SEMANTIC::POSITION:
			IN_POSITION = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::SCREENPOS:
			IN_SCREENPOS = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::NORMAL:
			IN_NORMAL = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::BINORMAL:
			IN_BINORMAL = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TANGENT:
			IN_TANGENT = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_0:
			IN_COLOR0 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_1:
			IN_COLOR1 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_0:
			IN_TEXCOORD0 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_1:
			IN_TEXCOORD1 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_2:
			IN_TEXCOORD2 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_3:
			IN_TEXCOORD3 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_4:
			IN_TEXCOORD4 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_5:
			IN_TEXCOORD5 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_6:
			IN_TEXCOORD6 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_7:
			IN_TEXCOORD7 = &inputRegisters[k];
			break;
		default:
			break;
		}
	}

	return CE_OK;
}

const CRESULT PixelShaderInstance::ConfigureOutput(std::vector<PixelShaderOutputDesc> &renderTargets)
{
	UINT32 k;

	outputRegisters = AlignedBuffer<CR_psOutputRegister>(
			Ceng::UINT32(renderTargets.size()),common->shader->cacheLine);

	for(k=0;k<renderTargets.size();k++)
	{
		outputRegisters[k].coverageAddress = &coverageAddress;

		switch(renderTargets[k].target)
		{
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET0:
			OUT_TARGET0 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET1:
			OUT_TARGET1 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET2:
			OUT_TARGET2 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET3:
			OUT_TARGET3 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET4:
			OUT_TARGET4 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET5:
			OUT_TARGET5 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET6:
			OUT_TARGET6 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET7:
			OUT_TARGET7 = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET_DEPTH:
			OUT_DEPTH = &outputRegisters[k];
			break;
		case PSHADER_OUTPUT_SEMANTIC::CR_SHADER_TARGET_STENCIL:
			OUT_STENCIL = &outputRegisters[k];
			break;
		default:
			break;
		};
	}

	return CE_OK;
}

const CRESULT PixelShaderInstance::ConfigureLocals()
{
	/*
	Ceng::UINT32 localBufferSize = 0;
	
	localBufferSize += 16 * 4; // shaderLocal_temp
	localBufferSize += 16 * 4; // sample2d cache
	localBufferSize += 8 * 4; // shaderLocal_uvDiffuse
	localBufferSize += 4 * 4; // shaderLocal_colorScale

	localVariables = AlignedBuffer<Ceng::UINT8>(localBufferSize,common->shader->cacheLine);

	shaderLocal_temp.dataAddress = &localVariables[0];
	sample2d.dataAddress = &localVariables[16 * 4];
	shaderLocal_uvDiffuse.dataAddress = &localVariables[16 * 4 + 16 * 4];
	shaderLocal_colorScale.dataAddress = &localVariables[16 * 4 + 16 * 4 + 8 * 4];

	//sample2d.textureUnits = &textureUnits;
	*/

	return CE_OK;
}


const CRESULT PixelShaderInstance::SetFragmentFormat(const std::vector<PixelShaderInputDesc> &inputSemantics,
													 const std::vector<PixelShaderOutputDesc> &targetSemantics)
{
	UINT32 k,j;
	
	// Allocate space for a quad's varying data

	if (quadBuffer == nullptr)
	{
		quadBuffer = AlignedBuffer<UINT8>(common->link->quadSize,common->shader->cacheLine);
	}

	quadTargetStart = common->link->link->quadFormat.targetStart;

	// Set up input register offsets within the quad format

	for(k=0;k<inputSemantics.size();k++)
	{
		for(j=0;j<common->link->link->quadFormat.variables.size();j++)
		{
			// Link all input registers to the variable
			// with a matching semantic

			// NOTE: Multiple registers can map to one semantic

			if (inputSemantics[k].semantic == common->link->link->quadFormat.variables[j].semantic)
			{
				inputRegisters[k].inputAddress = (POINTER)((UINT8*)quadBuffer) + 
													common->link->link->quadFormat.variables[j].quadOffset;

				// TODO: Set staticly
				inputRegisters[k].inputFormat = common->link->link->quadFormat.variables[j].format;

				inputRegisters[k].variableStep = common->link->link->quadFormat.variables[j].gradientOffset;		
			}
		}
	}


	// Set up render target address locations within the quad format

	for(k=0;k<targetSemantics.size();k++)
	{
		outputRegisters[k].inputAddress = (POINTER)((UINT8*)quadBuffer) +
			common->link->link->quadFormat.targetStart + targetSemantics[k].target*sizeof(POINTER);
	}

	return CE_OK;
}

const CRESULT PixelShaderInstance::SetRenderTargets(const std::vector<PixelShaderOutputDesc> &targetSemantics)
{
	Ceng::UINT32 k,j;

	for(k=0;k<targetSemantics.size();k++)
	{
		// NOTE: these should be set up at configuration time
		

		for(j=2;j<common->activeRenderTargets;j++)
		{
			if (targetSemantics[k].target == common->targetHandles[j]->shaderSemantic)
			{				
				outputRegisters[k].bufferFormat = common->targetHandles[j]->bufferFormat;
				
				if (common->targetHandles[j]->baseAddress == NULL)
				{
					outputRegisters[k].bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;
				}

				break;
			}
		}

		if (j == common->activeRenderTargets)
		{
			// No match found
			outputRegisters[k].bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;
		}

	}

	return CE_OK;
}

_declspec(align(64)) const Ceng::INT8 newVertTable[16][4] =
	{
		{0,0,0,0} ,
		{-1,0,0,0} ,
		{0,-1,0,0} ,
		{-1,-1,0,0} ,
		{0,0,-1,0} ,
		{-1,0,-1,0} ,
		{0,-1,-1,0} ,
		{-1,-1,-1,0} ,
		{0,0,0,-1} ,
		{-1,0,0,-1} ,
		{0,-1,0,-1} ,
		{-1,-1,0,-1} ,
		{0,0,-1,-1} ,
		{-1,0,-1,-1} ,
		{0,-1,-1,-1} ,
		{-1,-1,-1,-1}
	};

_declspec(align(16)) const Ceng::FLOAT32 allOnes[4] = {1.0f,1.0f,1.0f,1.0f};

_declspec(align(16)) const Ceng::FLOAT32 colorScaleVec[4] = {255.0f,255.0f,255.0f,255.0f};

const CRESULT PixelShaderInstance::ProcessQuads(Task_PixelShader *batch, const Ceng::INT32 threadId)
{
	UINT32 k;

	// Initialize pointer to current quad chain structure
	// NOTE: Input & output registers access this value through a pointer

	inputBaseAddress = (POINTER)((UINT8*)quadBuffer);
	
	FLOAT32 *localPerspective = (FLOAT32*)&perspectiveTemp[0];

	// ***** Constant setup

	const Ceng::UINT32 *diffuseTexture = (Ceng::UINT32*)common->uniformPtr[0];

	diffuseTexUnit = common->textureUnits[*diffuseTexture];

	UINT32 chainIndex;

	_declspec(align(16)) VectorF4 packedW;

	FLOAT32 *invertW = (FLOAT32*)&packedW;

	CR_TriangleData *triangle;

	UINT32 quadFloatOffset = Ceng::UINT32(common->link->link->quadFormat.floatStart);
	UINT32 quadDoubleOffset = Ceng::UINT32(common->link->link->quadFormat.doubleStart);
	UINT32 quadTargetOffset = Ceng::UINT32(common->link->link->quadFormat.targetStart);

	UINT8 *inputBuffer = quadBuffer;
	UINT8 *localCoverage;
	

	const FLOAT32 colorScaleScalar = FLOAT32(255.0f);

	triangle = batch->rasterizerBatch->triangle.get();

	for(k=0 ; k < batch->quadCount ; k++)
	{
		CR_QuadHeader *quad = &batch->quadList[k];

		stepBufferPtr = (POINTER)(triangle->fragment.variableStep);

		UINT8 *localSteps = (UINT8*)stepBufferPtr;

		//**********************************
		// Generate temporary quad

		UINT32 floatBlockSize = common->link->link->quadFormat.floatBlocks;
		UINT32 doubleBlockSize = common->link->link->quadFormat.doubleBlocks;
		
		CR_FloatFragment *floatParam = (CR_FloatFragment*)triangle->fragment.floatBlock;
		CR_DoubleFragment *doubleParam = (CR_DoubleFragment*)triangle->fragment.doubleBlock;

		FLOAT32 screenX = FLOAT32(quad->screenX);
		FLOAT32 screenY = FLOAT32(quad->screenY);

		packedW = triangle->packedW;
		
		packedW += triangle->packedW_dx * (screenX);
		packedW += triangle->packedW_dy * (screenY);

		VectorF4 *destF4 = (VectorF4*)&quadBuffer[quadFloatOffset];

		__m128 screenVecX = _mm_load1_ps(&screenX);
		__m128 screenVecY = _mm_load1_ps(&screenY);

		for (Ceng::UINT32 i = 0; i < floatBlockSize; ++i)
		{
			__m128 startValue = _mm_load_ps((float*)&floatParam[i].startValue);

			__m128 stepX = _mm_load_ps((float*)&floatParam[i].step_dx);
			__m128 stepY = _mm_load_ps((float*)&floatParam[i].step_dy);

			stepX = _mm_mul_ps(stepX, screenVecX);
			stepY = _mm_mul_ps(stepY, screenVecY);

			startValue = _mm_add_ps(startValue, stepX);
			startValue = _mm_add_ps(startValue, stepY);

			_mm_store_ps((float*)&destF4[i], startValue);
		}

		/*
		for(i=0;i<floatBlockSize;i++)
		{
			destF4[i] = floatParam[i].startValue + (floatParam[i].step_dx*screenX) +
				(floatParam[i].step_dy*screenY);
		}
		*/
	
		// Write DOUBLE variables for the first quad

		/*
		VectorD2 *destD2 = (VectorD2*)&quadBuffer[quadDoubleOffset];

		for(i=0;i<doubleBlockSize;i++)
		{
			destD2[i] = doubleParam[i].startValue + (doubleParam[i].step_dx*screenX)
				+ (doubleParam[i].step_dy*screenY);
		}
		*/
		
		// Write render target addresses
				
		// NOTE: Skip targets 0,1 because shader
		//       doesn't use depth-stencil buffer

		POINTER *target = (POINTER*)&quadBuffer[quadTargetOffset];

		for(Ceng::UINT32 i=2;i<common->activeRenderTargets;i++)
		{
			target[i] = common->targetHandles[i]->GetQuadAddress(0,quad->screenX,
																quad->screenY);
		}

		__m128 allOnesVec = _mm_load_ps((float*)allOnes);

		__m128 quadStepVec = _mm_loadu_ps((float*)&triangle->packedW_quad_dx);

		__m128 invertVecW = _mm_load_ps((float*)invertW);

		__m128 perspectiveVec;

		if (quad->coverageMask[0] == 0)
		{
			// Set coverage pointer to fully covered

			coverageAddress = 15; 

			localCoverage = (UINT8*)&newVertTable[15];

			// Chain contains only fully covered quads

			Ceng::UINT32 chainLength = quad->chainLength;

			Ceng::UINT32 chainPacks = chainLength >> 2;
			Ceng::UINT32 chainRemainder = chainLength & 3;

			for(chainIndex=0; chainIndex < chainPacks; chainIndex++)
			{
				// First quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec,invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0],&invertW[0],Ceng::INT32(coverageAddress),threadId);

				// Second quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0],&invertW[0],Ceng::INT32(coverageAddress),threadId);

				// Third quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0],&invertW[0],Ceng::INT32(coverageAddress),threadId);

				// Fourth quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0],&invertW[0],Ceng::INT32(coverageAddress),threadId);

			}

			for(chainIndex=0; chainIndex < chainRemainder ; chainIndex++)
			{
				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				// Process the quad
				ShaderFunction(&localPerspective[0], &invertW[0],Ceng::INT32(coverageAddress),threadId);
			}
		}
		else
		{
			// Partially filled chain

			UINT32 coverageIndex = 0;

			Ceng::UINT32 chainLength = quad->chainLength;

			for(chainIndex=0; chainIndex < chainLength ; chainIndex++)
			{
				perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				// Extract coverage information for the quad

				coverageIndex = quad->coverageMask[chainIndex>>3] >> (4*(chainIndex & 7));
				coverageIndex = coverageIndex & 15;

				coverageAddress = coverageIndex;

				// Process the quad
				ShaderFunction(&localPerspective[0],&invertW[0],Ceng::INT32(coverageAddress),threadId);	
			}
		}
	}

	return CE_OK;
}

const CRESULT PixelShaderInstance::ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	UINT32 k;

	// Initialize pointer to current quad chain structure
	// NOTE: Input & output registers access this value through a pointer

	inputBaseAddress = (POINTER)((UINT8*)quadBuffer);

	FLOAT32* localPerspective = (FLOAT32*)&perspectiveTemp[0];

	// ***** Constant setup

	const Ceng::UINT32* diffuseTexture = (Ceng::UINT32*)common->uniformPtr[0];

	diffuseTexUnit = common->textureUnits[*diffuseTexture];

	UINT32 chainIndex;

	_declspec(align(16)) VectorF4 packedW;

	FLOAT32* invertW = (FLOAT32*)&packedW;

	CR_TriangleData* triangle;

	UINT32 quadFloatOffset = Ceng::UINT32(common->link->link->quadFormat.floatStart);
	UINT32 quadDoubleOffset = Ceng::UINT32(common->link->link->quadFormat.doubleStart);
	UINT32 quadTargetOffset = Ceng::UINT32(common->link->link->quadFormat.targetStart);

	UINT8* inputBuffer = quadBuffer;
	UINT8* localCoverage;


	const FLOAT32 colorScaleScalar = FLOAT32(255.0f);

	triangle = batch->rasterizerBatch->triangle.get();

	for (k = 0; k < batch->quadCount; k++)
	{
		CR_QuadHeader* quad = &batch->quadList[k];

		stepBufferPtr = (POINTER)(triangle->fragment.variableStep);

		UINT8* localSteps = (UINT8*)stepBufferPtr;

		//**********************************
		// Generate temporary quad

		UINT32 floatBlockSize = common->link->link->quadFormat.floatBlocks;
		UINT32 doubleBlockSize = common->link->link->quadFormat.doubleBlocks;

		CR_FloatFragment* floatParam = (CR_FloatFragment*)triangle->fragment.floatBlock;
		CR_DoubleFragment* doubleParam = (CR_DoubleFragment*)triangle->fragment.doubleBlock;

		FLOAT32 screenX = FLOAT32(quad->screenX);
		FLOAT32 screenY = FLOAT32(quad->screenY);

		packedW = triangle->packedW;

		packedW += triangle->packedW_dx * (screenX);
		packedW += triangle->packedW_dy * (screenY);

		VectorF4* destF4 = (VectorF4*)&quadBuffer[quadFloatOffset];

		__m128 screenVecX = _mm_load1_ps(&screenX);
		__m128 screenVecY = _mm_load1_ps(&screenY);

		for (Ceng::UINT32 i = 0; i < floatBlockSize; ++i)
		{
			__m128 startValue = _mm_load_ps((float*)&floatParam[i].startValue);

			__m128 stepX = _mm_load_ps((float*)&floatParam[i].step_dx);
			__m128 stepY = _mm_load_ps((float*)&floatParam[i].step_dy);

			stepX = _mm_mul_ps(stepX, screenVecX);
			stepY = _mm_mul_ps(stepY, screenVecY);

			startValue = _mm_add_ps(startValue, stepX);
			startValue = _mm_add_ps(startValue, stepY);

			_mm_store_ps((float*)&destF4[i], startValue);
		}

		/*
		for(i=0;i<floatBlockSize;i++)
		{
			destF4[i] = floatParam[i].startValue + (floatParam[i].step_dx*screenX) +
				(floatParam[i].step_dy*screenY);
		}
		*/

		// Write DOUBLE variables for the first quad

		/*
		VectorD2 *destD2 = (VectorD2*)&quadBuffer[quadDoubleOffset];

		for(i=0;i<doubleBlockSize;i++)
		{
			destD2[i] = doubleParam[i].startValue + (doubleParam[i].step_dx*screenX)
				+ (doubleParam[i].step_dy*screenY);
		}
		*/

		// Write render target addresses

		// NOTE: Skip targets 0,1 because shader
		//       doesn't use depth-stencil buffer

		POINTER* target = (POINTER*)&quadBuffer[quadTargetOffset];

		for (Ceng::UINT32 i = 2; i < common->activeRenderTargets; i++)
		{
			target[i] = common->targetHandles[i]->GetQuadAddress(0, quad->screenX,
				quad->screenY);
		}

		__m128 allOnesVec = _mm_load_ps((float*)allOnes);

		__m128 quadStepVec = _mm_loadu_ps((float*)&triangle->packedW_quad_dx);

		__m128 invertVecW = _mm_load_ps((float*)invertW);

		__m128 perspectiveVec;

		if (quad->coverageMask[0] == 0)
		{
			// Set coverage pointer to fully covered

			coverageAddress = 15;

			localCoverage = (UINT8*)&newVertTable[15];

			// Chain contains only fully covered quads

			Ceng::UINT32 chainLength = quad->chainLength;

			Ceng::UINT32 chainPacks = chainLength >> 2;
			Ceng::UINT32 chainRemainder = chainLength & 3;

			for (chainIndex = 0; chainIndex < chainPacks; chainIndex++)
			{
				// First quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec,invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);

				// Second quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);

				// Third quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);

				// Fourth quad

				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);

			}

			for (chainIndex = 0; chainIndex < chainRemainder; chainIndex++)
			{
				perspectiveVec = _mm_rcp_ps(invertVecW);
				//perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				// Process the quad
				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);
			}
		}
		else
		{
			// Partially filled chain

			UINT32 coverageIndex = 0;

			Ceng::UINT32 chainLength = quad->chainLength;

			for (chainIndex = 0; chainIndex < chainLength; chainIndex++)
			{
				perspectiveVec = _mm_div_ps(allOnesVec, invertVecW);

				invertVecW = _mm_add_ps(invertVecW, quadStepVec);

				_mm_store_ps((float*)localPerspective, perspectiveVec);
				_mm_store_ps((float*)invertW, invertVecW);

				// Extract coverage information for the quad

				coverageIndex = quad->coverageMask[chainIndex >> 3] >> (4 * (chainIndex & 7));
				coverageIndex = coverageIndex & 15;

				coverageAddress = coverageIndex;

				// Process the quad
				ShaderFunction(&localPerspective[0], &invertW[0], Ceng::INT32(coverageAddress), threadId);
			}
		}
	}

	return CE_OK;
}

void PixelShaderInstance::ShaderFunction(const FLOAT32 *perspective,
										 const FLOAT32 *invertW,
										 const INT32 coverageIndex,
										 const Ceng::INT32 threadId)
{
	// ***** Constant setup

	//const Ceng::UINT32 *diffuseTexture = (Ceng::UINT32*)uniformPtr[0];

	// NOTE: Read input registers / write outputs only once because of
	//       automatic pixel stepping

	Pshader::Float2 uvDiffuse;
	
	uvDiffuse = *IN_TEXCOORD0;

	//shaderLocal_temp = *IN_COLOR0;

	Pshader::Float4 shaderLocal_temp;
	Pshader::Float shaderLocal_colorScale;



	//shaderLocal_uvDiffuse = *IN_TEXCOORD0;

	//shaderLocal_colorScale = *IN_TEXCOORD1;

	//shaderLocal_temp *= shaderLocal_colorScale;

	_declspec(align(16)) Ceng::VectorF4 color;

	color.x = 0.0f;
	color.y = 0.0f;
	color.z = 0.0f;
	color.w = 0.0f;

	/*
	switch (threadId)
	{
	case 0:
		color.x = 0.0f;
		color.y = 0.5f;
		color.z = 0.0f;
		break;
	case 1:
		color.x = 0.5f;
		color.y = 0.0f;
		break;
	case 2:
		color.y = 0.0f;
		color.z = 0.5f;
		break;
	case 3:
		color.x = 1.0f;
		color.y = 0.0f;
		color.z = 1.0f;
		break;
	case 4:
		color.x = 0.0f;
		color.y = 0.5f;
		color.z = 1.0f;
		break;
	case 5:
		color.x = 0.5f;
		color.y = 0.5f;
		color.z = 0.0f;
		break;
	case 6:
		color.x = 0.5f;
		color.y = 0.5f;
		color.z = 0.5f;
		break;
	case 7:
		color.x = 0.25f;
		color.y = 0.25f;
		color.z = 0.5f;
		break;
	default:
		break;
	}
	*/

	//OUT_TARGET0->Write(color,coverageIndex);
	

	OUT_TARGET0->Write(sample2d(diffuseTexUnit, uvDiffuse), coverageIndex);

}

		