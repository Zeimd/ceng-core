/*****************************************************************************
*
* gl32-index-buffer.h
*
* By Jari Korkala 28/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_INDEX_BUFFER_H
#define CENG_GL32_INDEX_BUFFER_H

#include <gl/glew.h>

#include <ceng/datatypes/boolean.h>

#include <ceng/datatypes/return-val.h>

#include <ceng/interfaces/index-buffer.h>

namespace Ceng
{
	class GL32_IndexBuffer : public IndexBuffer
	{
	public:
		GLuint gl_bufferID;
		GLuint gl_usage;
		GLuint gl_size;

		Ceng::UINT32 elements;
		Ceng::UINT32 elementSize;

		Ceng::BOOL cpuWrite;

	public:
		GL32_IndexBuffer();
		GL32_IndexBuffer(const GLuint gl_bufferID, const GLuint gl_usage, const GLuint gl_size, const Ceng::UINT32 elementSize,const Ceng::UINT32 elements,
			const Ceng::BOOL cpuWrite);

		virtual ~GL32_IndexBuffer();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements, 
			const Ceng::UINT32 usage, void *initialData,Ceng::GL32_IndexBuffer **output);

		static const Ceng::CRESULT TranslateUsage(const Ceng::UINT32 usage, GLint *gl_usage, Ceng::BOOL *cpuWrite);
	};
}

#endif