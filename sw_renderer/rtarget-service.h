#pragma once

#include <memory>

#include <ceng/swshader/RenderTargetService.h>

namespace Ceng
{
	class PixelShaderContextCommon;

	class SW_RenderTargetService : public Ceng::Pshader::RenderTargetService
	{
	public:

		PixelShaderContextCommon* common;

	protected:

		~SW_RenderTargetService() override;

	public:

		SW_RenderTargetService(PixelShaderContextCommon* common);

		void Release() override;

		void GenerateAddresses(Ceng::UINT32 screenX, Ceng::UINT32 screenY, POINTER* quadTargetOffset) override;

	};
}