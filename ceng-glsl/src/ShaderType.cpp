#include <ceng/GLSL/ShaderType.h>

namespace Ceng
{
	namespace GLSL
	{
		namespace ShaderType
		{
			const char* ToString(ShaderType::value type)
			{
				switch (type)
				{
				case ShaderType::vertex:
					return "vertex";
				case ShaderType::fragment:
					return "fragment";
				case ShaderType::geometry:
					return "geometry";
				default:
					return "<UNHANDLED SHADER TYPE>";
				}
			}
		}
	}
}