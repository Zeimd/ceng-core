/*****************************************************************************
*
* gl33-vertex-format.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef GL33_VERTEX_FORMAT_H
#define GL33_VERTEX_FORMAT_H

#include <gl/glew.h>

#include <vector>

#include <ceng/datatypes/return-val.h>
#include <ceng/interfaces/vertex-format.h>
#include <ceng/interfaces/vertex-decl.h>

#include <ceng/datatypes/ce-string.h>

#include "gl32-constants.h"
#include "gl32-state-vertex-stream.h"

namespace Ceng
{
	class GL32_ShaderProgram;

	/**
	* TODO: Replace with query of OpenGL capabilities?
	*/

	class GL_VertexData
	{
	public:
		Ceng::StringUtf8 name;
	
		/**
		* OpenGL data type. Can be GL_FLOAT,GL_BYTE,GL_UNSIGNED_BYTE,
		* GL_SHORT,GL_UNSIGNED_SHORT,GL_FIXED.
		*/
		GLenum type;		
		
		/**
		* 1-4
		*/
		GLint elements; 

		/**
		* Size of attribute in bytes. Example: vec4 = 4*sizeof(float)=16
		*/
		GLint size;

		/**
		* Selects the input vertex stream this data comes from.
		*/
		Ceng::UINT32 stream;

		/**
		* Offset within vertex format.
		*/
		GLint offset;

		/**
		* If true, integer values are normalized to [0,1] for unsigned
		* data, and [-1,1] for signed data.
		*/
		GLboolean normalized;
	
		/**
		* OpenGL handle for vertex attribute arrays.
		*/
		GLint gl_attribHandle;

		Ceng::BOOL shaderLink;

		/**
		* Vertex attribute array for this variable is enabled.
		* Indicates linked=true.
		*/
		Ceng::BOOL arrayEnabled;

		/**
		* The vertex stream for this variable is available.
		*/
		Ceng::BOOL streamLink;

		GL_VertexData() : name(), stream(0), elements(0), type(0), normalized(GL_FALSE), gl_attribHandle(-1), shaderLink(false),
			arrayEnabled(false), streamLink(false)
		{}

	public:

		const Ceng::CRESULT TranslateFormat(const Ceng::VTX_DATATYPE::value format);
	};

	class StreamData
	{
	public:
		Ceng::UINT32 index;
		Ceng::UINT32 stride;

		std::vector<Ceng::UINT32> attributes;

		StreamData() : index(0),stride(0)
		{
		}

		StreamData(const Ceng::UINT32 index) : index(index),stride(0)
		{
		}
	};

	class GL32_ShaderProgram;

	class LinkVector
	{
	public:
		GL32_ShaderProgram *program;
		std::vector<Ceng::INT32> linkValues;

		LinkVector(const Ceng::UINT32 elements, GL32_ShaderProgram *program) : program(program),
			linkValues(std::vector<Ceng::INT32>(elements, -1))
		{
			//linkValues = ;
		}
	};



	class GL33_VertexFormat : public VertexFormat
	{
	public:

		std::vector<GL_VertexData> vertexData;

		std::vector<StreamData> streamList;
		std::vector<LinkVector> shaderLink;

		Ceng::BOOL locked;

		/**
		 * Set if any vertex attribute is currently enabled.
		 */
		Ceng::BOOL enabledArrays;

	protected:

		GL33_VertexFormat();

	public:

		void Clear();

		GL33_VertexFormat(std::vector<GL_VertexData> &&vertexData,std::vector<StreamData> &&streamList);

		virtual ~GL33_VertexFormat();

		virtual void Release() override;

		static const CRESULT GetInstance(const std::vector<VertexDeclData> &vertexDecl, GL33_VertexFormat **out_format);

		const Ceng::UINT32 StreamCount();

		/**
		* Returns the stride of a stream. Index is relative to streamList, not API-defined stream index.
		*/
		const Ceng::UINT32 StreamStride(const Ceng::UINT32 stream);

		void DisableStreamLinks();

		void LinkVertexStream(const Ceng::UINT32 index, GL32_VertexStreamState *stream);

		void LinkShaderProgram(GL32_ShaderProgram *program);

	protected:

		void SetEmptyLinks();

		static void TranslateFormat(const Ceng::VTX_DATATYPE::value format, GL_VertexData &dest);
	};
}

#endif