#ifndef CENG_GLSL_FILE_POSITION_H
#define CENG_GLSL_FILE_POSITION_H

#include <memory>

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	struct FilePosition
	{
		std::shared_ptr<const Ceng::StringUtf8> file;
		Ceng::UINT32 line;
		Ceng::UINT32 column;

		FilePosition() : line(0), column(0)
		{
		}

		FilePosition(const std::shared_ptr<const Ceng::StringUtf8>& file, Ceng::UINT32 line, Ceng::UINT32 column)
			: file(file), line(line), column(column)
		{

		}
	};
}

#endif