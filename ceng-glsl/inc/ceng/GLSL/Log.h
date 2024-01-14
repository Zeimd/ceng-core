#ifndef CENG_LOG_H
#define CENG_LOG_H

#include <vector>
#include <memory>

#include "LogEntry.h"

namespace Ceng
{
	class Log
	{
	protected:
		std::vector<LogEntry> log;

	public:

		void Clear();

		void Print(LogLevel::value level, const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column);

		void Print(LogLevel::value level, const Ceng::StringUtf8& message);

		void Debug(const Ceng::StringUtf8& message);

		void Debug(const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column);

		Ceng::StringUtf8 ToString() const;

	};
}

#endif