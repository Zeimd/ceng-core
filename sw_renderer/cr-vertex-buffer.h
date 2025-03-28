/*****************************************************************************
*
* cr-vertex-buffer.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_VERTEX_BUFFER_H
#define _CENG_CR_VERTEX_BUFFER_H

#include <ceng/interfaces/vertex-buffer.h>

#include "crender-base.h"

namespace Ceng
{
	class CR_VertexBuffer : public Ceng::VertexBuffer
	{
	protected:
		Ceng::UINT8 *vertexBuffer;
		Ceng::UINT32 elementSizeBytes;
		Ceng::UINT32 elementCount;
	
	public:
		CR_VertexBuffer();
		
		CR_VertexBuffer(Ceng::UINT8 *ptr,const Ceng::UINT32 newSize,const Ceng::UINT32 elements);
		
		~CR_VertexBuffer() override;

		void Release() override;
		
		const CRESULT BufferPtr(Ceng::UINT8** bufferPtr) override;
		const CRESULT ElementSize(Ceng::UINT32* size) override;
		const CRESULT ElementCount(Ceng::UINT32* elements) override;

		// Loads entire buffer's worth of data
		const Ceng::CRESULT LoadData(void* dataPtr) override;

		// Loads partial buffer's worth of data
		const Ceng::CRESULT LoadPartialData(const Ceng::UINT32 startOffset, const Ceng::UINT32 size, void* dataPtr) override;

		const BufferType::value GetResourceType() override;
	};
};

#endif