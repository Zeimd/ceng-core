/*****************************************************************************
*
* gl32-state-vertex-stream.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef CENG_GL32_STATE_VERTEX_STREAM_H
#define CENG_GL32_STATE_VERTEX_STREAM_H

#include <ceng/datatypes/boolean.h>

namespace Ceng
{
	class GL32_VertexBuffer;

	class GL32_VertexStreamState
	{
	public:
		GL32_VertexBuffer *vertexBuffer;
		Ceng::UINT32 offset;
		Ceng::UINT32 stride;

		Ceng::BOOL changed;

	public:
		GL32_VertexStreamState() : vertexBuffer(nullptr),offset(0),stride(0),changed(false)
		{
		}
		~GL32_VertexStreamState()
		{
		}
	};
}

#endif