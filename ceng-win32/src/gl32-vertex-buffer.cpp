/*****************************************************************************
*
* gl32-vertex-buffer.cpp
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#include <ceng/enums/buffer-usage.h>

#include "../inc/gl32-vertex-buffer.h"

using namespace Ceng;

GL32_VertexBuffer::GL32_VertexBuffer()
{
}

GL32_VertexBuffer::GL32_VertexBuffer(const GLuint bufferID, const GLenum bufferUsage, const Ceng::UINT32 bufferSize,
	const Ceng::UINT32 elementSize, const Ceng::UINT32 elementCount)
	: bufferID(bufferID),bufferUsage(bufferUsage),bufferSize(bufferSize),elementSize(elementSize),elementCount(elementCount)
{
}

GL32_VertexBuffer::~GL32_VertexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void GL32_VertexBuffer::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_VertexBuffer::GetInstance(const Ceng::UINT32 vertexSizeBytes, const Ceng::UINT32 vertexNum,
	const Ceng::UINT32 usage, GL32_VertexBuffer **output)
{
	GLuint bufferID;

	glGenBuffers(1, &bufferID);

	GLenum result = glGetError();

	if (result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	GLint oldBuffer;

	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	GLenum gl_usage;

	switch (usage)
	{
	case Ceng::BufferUsage::gpu_read_only:
		gl_usage = GL_STATIC_DRAW;
		break;
	default:
		glBindBuffer(GL_ARRAY_BUFFER, oldBuffer);
		glDeleteBuffers(1, &bufferID);
		return CE_ERR_FAIL;
	}

	// Allocate space
	glBufferData(GL_ARRAY_BUFFER, vertexSizeBytes*vertexNum, nullptr, gl_usage);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glBindBuffer(GL_ARRAY_BUFFER, oldBuffer);
		glDeleteBuffers(1, &bufferID);
		return CE_ERR_FAIL;
	}

	glBindBuffer(GL_ARRAY_BUFFER, oldBuffer);

	*output = new GL32_VertexBuffer(bufferID, gl_usage, vertexSizeBytes*vertexNum,vertexSizeBytes,vertexNum);

	return CE_OK;
}

const Ceng::CRESULT GL32_VertexBuffer::LoadData(void *dataPtr)
{
	return LoadPartialData(0, bufferSize, dataPtr);
}

const Ceng::CRESULT GL32_VertexBuffer::LoadPartialData(const Ceng::UINT32 startOffset, const Ceng::UINT32 size, void *dataPtr)
{
	GLint oldBuffer;

	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	glBufferSubData(GL_ARRAY_BUFFER, startOffset,size, dataPtr);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glBindBuffer(GL_ARRAY_BUFFER, oldBuffer);
		return CE_ERR_FAIL;
	}

	glBindBuffer(GL_ARRAY_BUFFER, oldBuffer);

	return CE_OK;
}

const Ceng::CRESULT GL32_VertexBuffer::BufferPtr(Ceng::UINT8 **bufferPtr)
{
	return CE_OK;
}

const Ceng::CRESULT GL32_VertexBuffer::ElementSize(Ceng::UINT32 *size)
{
	*size = elementSize;
	return CE_OK;
}

const Ceng::CRESULT GL32_VertexBuffer::ElementCount(Ceng::UINT32 *elements)
{
	*elements = elementCount;
	return CE_OK;
}

const Ceng::BufferType::value GL32_VertexBuffer::GetResourceType()
{
	return Ceng::BufferType::buffer;
}