/*****************************************************************************
*
* path.cpp
*
* By Jari Korkala 10/12/2015
*
*****************************************************************************/

#include <Windows.h>

#include <ceng/datatypes/string-manipulator.h>

#include "../inc/ceng-win32.h"

using namespace Ceng;

const Ceng::INT8 Separator(const Ceng::StringUtf8 &path)
{
	Ceng::INT8 separator = '/';

	if (path.SubString(0, 4) == "\\\\?\\")
	{
		separator = '\\';
	}

	return separator;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_GetFilename(const Ceng::StringUtf8 &path,
	Ceng::StringUtf8 &filename)
{
	auto separator = Separator(path);

	auto iter = path.FindLast(separator, path.ConstReverseBeginIterator());

	--iter;

	filename = path.SubString(iter.Iterator(), path.ConstEndIterator());

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_IsRelativePath(const Ceng::StringUtf8 &path)
{
	if (path.Length() >= 3)
	{
		if (path[1] == ':' && path[2] == '\\')
		{
			// Standard drive header
			return CE_ERR_INVALID_PARAM;
		}
	}

	if (path.Length() >= 2)
	{
		if (path[0] == '\\' && path[1] == '\\')
		{
			// Path starts with server name
			return CE_ERR_INVALID_PARAM;
		}
	}

	if (path.Length() >= 4)
	{
		// UNC paths aren't relative, so raise error
		if (path[0] == '\\' && path[1] == '\\' && path[2] == '?' && path[3] == '\\')
		{
			return CE_ERR_INVALID_PARAM;
		}
	}

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_OpenFileRead(const Ceng::StringUtf8 &name,
	const std::ios_base::openmode mode, std::ifstream &stream)
{
	Ceng::StringUtf8 tempName;
	
	Ceng_MakeOSPath(name, tempName);

	// Convert to UTF-16 for Windows API
	Ceng::StringUtf16 wideName = tempName;
	
	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_MakeOSPath(const Ceng::StringUtf8 &path,
	Ceng::StringUtf8 &output)
{
	// Convert given path into UNC form

	// TODO: Check that given path isn't relative

	output = Ceng::StringManipulator::ReplaceWith(path, "/", '\\');

	//if (output.BufferSize() >= MAX_PATH)
	//{
		output = Ceng::StringUtf8("\\\\?\\") + output;
	//}

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_ApplyRelativePath(const Ceng::StringUtf8 &base,
	const Ceng::StringUtf8 &relativePath, Ceng::StringUtf8 &output)
{
	Ceng::CRESULT cresult = Ceng_IsRelativePath(relativePath);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	Ceng::StringUtf8 temp;

	Ceng::StringUtf8 basePath = base;

	Ceng::INT8 separator = '/';

	if (basePath.SubString(0, 4) == "\\\\?\\")
	{
		separator = '\\';
	}

	if (base[base.Length() - 1] == separator)
	{
		basePath.RemoveLastChar();
	}

	auto relativeIter = relativePath.ConstBeginIterator();

	do
	{
		auto start = relativeIter;

		relativeIter = relativePath.FindFirst('/', relativeIter);

		auto end = relativeIter;

		relativeIter = end;
		++relativeIter;

		temp = relativePath.SubString(start, end);

		if (temp == "..")
		{
			auto baseStart = basePath.FindLast('/', basePath.ConstReverseBeginIterator());
			//++baseStart;

			basePath.Erase(baseStart.Iterator(), basePath.ConstEndIterator());
		}
		else
		{
			basePath += separator;
			basePath += temp;
		}

		if (relativeIter == relativePath.ConstEndIterator())
		{
			break;
		}

	} while (1);

	output = basePath;
	if (relativePath[relativePath.Length() - 1] == '/')
	{
		output += separator;
	}

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_ExePath(Ceng::StringUtf8 &path)
{
	::DWORD length;
	
	std::vector<::WCHAR> buffer(2048,0);

	do
	{
		// Leave space for null-terminator when giving buffer size as param
		length = ::GetModuleFileName(NULL, &buffer[0], buffer.size()-1);

		::DWORD error = ::GetLastError();

		if (error != 0)
		{
			if (error != ERROR_INSUFFICIENT_BUFFER)
			{
				return CE_ERR_FAIL;
			}
		}

		if (length != buffer.size() - 1)
		{
			break;
		}

		buffer = std::vector<::WCHAR>(2 * buffer.size(), 0);
	} while (1);

	Ceng::StringUtf8 temp = &buffer[0];

	// Remove executable name

	auto iter = temp.FindLast('\\',temp.ConstReverseBeginIterator());

	temp = temp.SubString(temp.ConstBeginIterator(), (--iter).Iterator());

	path = Ceng::StringManipulator::ReplaceWith(temp, "\\", '/');

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_CurrentPath(Ceng::StringUtf8 &path)
{
	::DWORD length;

	length = ::GetCurrentDirectory(0, NULL);

	std::vector<::WCHAR> buffer(length+1);

	length = ::GetCurrentDirectory(length + 1, &buffer[0]);

	path = &buffer[0];

	path = Ceng::StringManipulator::ReplaceWith(path, "\\", '/');

	path += '/';

	return CE_OK;
}