#include <ceng/GLSL/LogEntry.h>

using namespace Ceng;

LogEntry::LogEntry(LogLevel::value level, const Ceng::StringUtf8& message)
	: level(level), message(message), useLocation(false)
{

}

LogEntry::LogEntry(LogLevel::value level, const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
	: level(level), message(message), fileName(fileName), line(line), column(column),useLocation(true)
{

}

LogEntry::LogEntry(LogLevel::value level, const Ceng::StringUtf8&& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
	: level(level),message(message),fileName(fileName),line(line),column(column),useLocation(true)
{

}

const char* LogEntry::LogLevelToString(LogLevel::value level)
{
	switch (level)
	{
	case LogLevel::nominal:
		return "";
	case LogLevel::error:
		return "ERROR";
	case LogLevel::debug:
		return "DEBUG";
	case LogLevel::debug_low:
		return "DEBUG_LOW";
	case LogLevel::verbose:
		return "VERBOSE";
	case LogLevel::warning:
		return "WARNING";
	}

	return "";
}

Ceng::StringUtf8 LogEntry::ToString() const
{
	Ceng::StringUtf8 temp = LogLevelToString(level);

	if (useLocation)
	{
		temp += ": ";
		temp += *fileName;
		temp += ": ";
		temp += line;
		temp += ": ";
		temp += column;
	}
	temp += ": ";
	temp += message;

	return temp;
}