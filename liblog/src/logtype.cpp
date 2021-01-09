/*****************************************************************************
*
* logtype.cpp
*
* By Jari Korkala 10/2013
*
*****************************************************************************/

#include <ceng/lib/liblog.h>

using namespace Ceng;

LogType::LogType()
{
}

LogType::~LogType()
{
}

CRESULT LogType::Print(const Ceng::String &text)
{
	return CE_OK;
}