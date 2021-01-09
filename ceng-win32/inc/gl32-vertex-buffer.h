/*****************************************************************************
*
* gl32-vertex-buffer.h
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_VERTEX_BUFFER_H
#define CENG_GL32_VERTEX_BUFFER_H

#include <gl/glew.h>

#include <ceng/interfaces/vertex-buffer.h>

namespace Ceng
{
	class GL32_VertexBuffer : public Ceng::VertexBuffer
	{
	public:

		GLuint bufferID;
		GLenum bufferUsage;

		Ceng::UINT32 elementSize;
		Ceng::UINT32 elementCount;

		Ceng::UINT32 bufferSize;


	public:
		GL32_VertexBuffer();
		GL32_VertexBuffer(const GLuint bufferID, const GLenum bufferUsage,const Ceng::UINT32 bufferSize,
			const Ceng::UINT32 elementSize,const Ceng::UINT32 elementCount);
		virtual ~GL32_VertexBuffer();

		static const Ceng::CRESULT GetInstance(const Ceng::UINT32 vertexSizeBytes, const Ceng::UINT32 vertexNum,
			const Ceng::UINT32 usage, GL32_VertexBuffer **output);

		virtual void Release() override;

		virtual const CRESULT BufferPtr(Ceng::UINT8 **bufferPtr) override;
		virtual const CRESULT ElementSize(Ceng::UINT32 *size) override;
		virtual const CRESULT ElementCount(Ceng::UINT32 *elements) override;

		virtual const BufferType::value GetResourceType() override;

		// Loads entire buffer's worth of data
		virtual const Ceng::CRESULT LoadData(void *dataPtr) override;

		// Loads partial buffer's worth of data
		virtual const Ceng::CRESULT LoadPartialData(const Ceng::UINT32 startOffset, const Ceng::UINT32 size, void *dataPtr) override;
	};
}

#endif