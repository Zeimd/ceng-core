/*****************************************************************************
*
* gl32-index-buffer.cpp
*
* By Jari Korkala 28/10/2015
*
*****************************************************************************/

#include "../inc/gl32-index-buffer.h"

#include <ceng/enums/buffer-usage.h>

using namespace Ceng;

GL32_IndexBuffer::GL32_IndexBuffer()
{
}

GL32_IndexBuffer::GL32_IndexBuffer(const GLuint gl_bufferID, const GLuint gl_usage,
	const GLuint gl_size, const Ceng::UINT32 elementSize, const Ceng::UINT32 elements, const Ceng::BOOL cpuWrite)
	: gl_bufferID(gl_bufferID), gl_usage(gl_usage), gl_size(gl_size), elements(elements), cpuWrite(cpuWrite),
	elementSize(elementSize)
{
}


GL32_IndexBuffer::~GL32_IndexBuffer()
{
	glDeleteBuffers(1, &gl_bufferID);
}

void GL32_IndexBuffer::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_IndexBuffer::GetInstance(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements,
	const Ceng::UINT32 usage, void *initialData,Ceng::GL32_IndexBuffer **output)
{
	GLint gl_usage;

	Ceng::BOOL cpuWrite;

	CRESULT cresult = TranslateUsage(usage, &gl_usage,&cpuWrite);

	if (cpuWrite == false && initialData == nullptr)
	{
		return CE_ERR_INVALID_PARAM;
	}

	GLint gl_size;

	switch (elementSize)
	{
	case 1:
		gl_size = GL_UNSIGNED_BYTE;
		break;
	case 2:
		gl_size = GL_UNSIGNED_SHORT;
		break;
	case 4:
		gl_size = GL_UNSIGNED_INT;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	GLuint gl_bufferID;

	glGenBuffers(1, &gl_bufferID);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	// Store current binding

	GLint oldBuffer;

	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_bufferID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize*elements, initialData, gl_usage);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteBuffers(1, &gl_bufferID);

		// Restore previous binding
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldBuffer);

		return CE_ERR_FAIL;
	}

	// Restore previous binding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldBuffer);

	*output = new GL32_IndexBuffer(gl_bufferID,gl_usage,gl_size,elementSize,elements,cpuWrite);

	return cresult;
}

const Ceng::CRESULT GL32_IndexBuffer::TranslateUsage(const Ceng::UINT32 usage, GLint *gl_usage,Ceng::BOOL *cpuWrite)
{
	switch (usage)
	{
	case BufferUsage::gpu_read_only:
		*gl_usage = GL_STATIC_DRAW;
		*cpuWrite = false;
		break;
	case BufferUsage::gpu_read_write:
		*gl_usage = GL_DYNAMIC_COPY;
		*cpuWrite = false;
		break;
	case BufferUsage::gpu_cpu_write:
		*gl_usage = GL_DYNAMIC_COPY;
		*cpuWrite = true;
		break;
	case BufferUsage::gpu_to_cpu:
		*gl_usage = GL_DYNAMIC_READ;
		*cpuWrite = false;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}
