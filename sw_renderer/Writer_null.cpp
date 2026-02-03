#include "Writer_null.h"

using namespace Ceng;

Writer_null::~Writer_null()
{

}


void Writer_null::Release()
{
	delete this;
}

void Writer_null::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_null::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_null::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_null::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverage)
{

}