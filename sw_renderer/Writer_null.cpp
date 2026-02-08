#include "Writer_null.h"

#include <ceng/swshader/pshader-sampler.h>

using namespace Ceng;

Writer_null::~Writer_null()
{

}


void Writer_null::Release()
{
	delete this;
}

void Writer_null::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_null::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_null::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_null::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_null::WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex)
{

}