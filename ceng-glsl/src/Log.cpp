#include <ceng/GLSL/Log.h>

using namespace Ceng;

void Log::Clear()
{
	log.clear();
}

void Log::FlushMode(bool set)
{
	flushMode = true;
}

void Log::Print(LogLevel::value level, const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
{
	log.emplace_back(level, message, fileName, line, column);

	if (flushMode)
	{
		Flush();
	}
}

void Log::Print(LogLevel::value level, const Ceng::StringUtf8& message)
{
	log.emplace_back(level, message);

	if (flushMode)
	{
		Flush();
	}
}

void Log::Debug(const Ceng::StringUtf8& message, const std::shared_ptr<const Ceng::StringUtf8>& fileName, const Ceng::UINT32 line, const Ceng::UINT32 column)
{
	Print(LogLevel::debug, message, fileName, line, column);
}

void Log::Nominal(const Ceng::StringUtf8& message)
{
	Print(LogLevel::nominal, message);
}

void Log::Debug(const Ceng::StringUtf8& message)
{
#ifdef _DEBUG
	Print(LogLevel::debug, message);
#endif
}

void Log::Error(const Ceng::StringUtf8& message)
{
	Print(LogLevel::error, message);
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

void Log::Flush()
{
	Ceng::StringUtf8 temp = ToString();

	printf("%s", temp.ToCString());

	log.clear();
}