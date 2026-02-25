#pragma once

#ifndef CENG_SWRENDER_VSHADER_INPUT_READER_H
#define CENG_SWRENDER_VSHADER_INPUT_READER_H

#include <ceng/swshader/vshader-input.h>

namespace Ceng::Vshader
{
	extern void NullVertexReader(void* dest, void* source);

	extern Vshader::VertexShaderInputReader GetReadCallback(Ceng::SHADER_DATATYPE::value destFormat,
		Ceng::VTX_DATATYPE::value sourceFormat);
}

#endif