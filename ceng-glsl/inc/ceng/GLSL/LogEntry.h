#ifndef CENG_GLSL_LOG_ENTRY_H
#define CENG_GLSL_LOG_ENTRY_H

#include <memory>

#include <ceng/datatypes/ce-string.h>

#include "LogLevel.h"

namespace Ceng
{
	class LogEntry
	{
	public:
		LogLevel::value level;
		Ceng::StringUtf8 message;

		bool useLocation;

		std::shared_ptr<const Ceng::StringUtf8> fileName;
		Ceng::UINT32 line;
		Ceng::UINT32 column;

		LogEntry(LogLevel::value level, const Ceng::StringUtf8& message);

		LogEntry(LogLevel::value level, const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column);

		LogEntry(LogLevel::value level, const Ceng::StringUtf8&& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column);

		Ceng::StringUtf8 ToString() const;

		static const char* LogLevelToString(LogLevel::value level);
	};
}

#endif