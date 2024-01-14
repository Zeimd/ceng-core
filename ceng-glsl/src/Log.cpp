#include <ceng/GLSL/Log.h>

using namespace Ceng;

void Log::Clear()
{
	log.clear();
}

void Log::Print(LogLevel::value level, const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
{
	log.emplace_back(level, message, fileName, line, column);
}

void Log::Print(LogLevel::value level, const Ceng::StringUtf8& message)
{
	log.emplace_back(level, message);
}

void Log::Debug(const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
{
	Print(LogLevel::debug, message, fileName, line, column);
}


void Log::Debug(const Ceng::StringUtf8& message)
{
	Print(LogLevel::debug, message);
}

Ceng::StringUtf8 Log::ToString() const
{
	Ceng::StringUtf8 temp;

	for (auto& x : log)
	{
		temp += x.ToString();
		temp += '\n';
	}

	return temp;
}