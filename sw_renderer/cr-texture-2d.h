/*****************************************************************************
*
* cr-texture-2d.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef CENG_CR_TEXTURE_2D_H
#define CENG_CR_TEXTURE_2D_H

#include <memory>

#include <ceng/datatypes/bufferdata-2d.h>
#include <ceng/interfaces/texture-2d.h>
#include <ceng/interfaces/render-target.h>

#include "crender-base.h"

#include "rtarget-data.h"

#include <ceng/datatypes/tex2d-desc.h>

#include "cr-resource.h"

namespace Ceng
{
	typedef std::vector<std::shared_ptr<CR_NewTargetData>> TextureMipVector;

	typedef std::vector<TextureMipVector> TextureArrayVector;

	class CR_Texture2D : public Ceng::Texture2D
	{
	public:

		Texture2dDesc desc;

		TextureArrayVector textures;

	protected:

		CR_Texture2D();

	public:

		CR_Texture2D(const Texture2dDesc &desc, TextureArrayVector &&textures);
		
		~CR_Texture2D() override;

		void Release() override;

		const CRESULT GetBufferData2D(Ceng::BufferData2D* dataPtr) override;

		const Ceng::CRESULT GetShaderViewTex2D(const Ceng::ShaderResourceViewDesc& desc, Ceng::ShaderResourceView** resourceView) override;

		const Ceng::CRESULT GetRenderTargetView(const Ceng::RenderTargetViewDesc& desc,
			Ceng::RenderTargetView** targetView) override;

		const Ceng::CRESULT GetSubResourceData(const Ceng::UINT32 mipLevel, void* destPtr) override;

		const BufferType::value GetResourceType() override;

		//virtual const CRESULT GetBufferData2D(Ceng::BufferData2D *dataPtr);
		//virtual const CRESULT GetRenderTarget(Ceng::RenderTarget **targetPtr);

		//virtual const CRESULT GetShaderViewTex2D(const ShaderResourceViewDesc &viewDesc, 
			//ShaderResourceView **out_view) override;

		const CRESULT GenerateMipMaps(const Ceng::UINT32 startLevel);

		const CRESULT ConvertToTiled();

	protected:
		const CRESULT SuperSampleDown(std::shared_ptr<CR_NewTargetData> &source, std::shared_ptr<CR_NewTargetData> &out_texture);

		const CRESULT SuperSampleHorizontal1D(std::shared_ptr<CR_NewTargetData> &source,
			std::shared_ptr<CR_NewTargetData> &out_texture);

		const CRESULT SuperSampleVertical1D(std::shared_ptr<CR_NewTargetData> &source,
			std::shared_ptr<CR_NewTargetData> &out_texture);

		void SuperSampleHorizontal(Ceng::UINT8 *destScanline, const Ceng::UINT32 destPitch,
			Ceng::UINT8 *sourceScanline, const Ceng::UINT32 sourcePitch,
			const Ceng::UINT32 bytesPerPixel, const Ceng::UINT32 xStart, const Ceng::UINT32 xEnd, const Ceng::UINT32 y);

		void SuperSampleHorizontalOdd(Ceng::UINT8 *destScanline, const Ceng::UINT32 destPitch,
			Ceng::UINT8 *sourceScanline, const Ceng::UINT32 sourcePitch,
			const Ceng::UINT32 bytesPerPixel, const Ceng::UINT32 xStart, const Ceng::UINT32 xEnd, const Ceng::UINT32 y);

		void SuperSampleHorizontalCenter(Ceng::UINT8 *destScanline, const Ceng::UINT32 destPitch,
			Ceng::UINT8 *sourceScanline, const Ceng::UINT32 sourcePitch,
			const Ceng::UINT32 bytesPerPixel, const Ceng::UINT32 x, const Ceng::UINT32 y);

		void SuperSampleTrueCenter(Ceng::UINT8 *destScanline, const Ceng::UINT32 destPitch,
			Ceng::UINT8 *sourceScanline, const Ceng::UINT32 sourcePitch,
			const Ceng::UINT32 bytesPerPixel, const Ceng::UINT32 x, const Ceng::UINT32 y);
	};
};

#endif