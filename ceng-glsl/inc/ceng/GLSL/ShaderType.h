#ifndef CENG_GLSL_SHADER_TYPE_H
#define CENG_GLSL_SHADER_TYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace ShaderType
		{
			enum value
			{
				vertex,
				geometry,
				fragment,
			};

			const char* ToString(ShaderType::value type);
		}
	}
}

#endif