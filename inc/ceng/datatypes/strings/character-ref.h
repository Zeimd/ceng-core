/*****************************************************************************
*
* character-ref.h
*
* By Jari Korkala 3/2014
*
*****************************************************************************/

#ifndef CENG_STRING_CHARACTER_REF_H
#define CENG_STRING_CHARACTER_REF_H

#include "buffer-ref.h"

#include "character.h"

#include "../basic-types.h"
#include "../boolean.h"

namespace Ceng
{
	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	class CharacterRef
	{
	protected:

		BUFFER_REF stringBuffer;

		size_t index;
		size_t rawPosition;
		Ceng::INT32 bytes;

	public:

		CharacterRef();

		~CharacterRef();

		CharacterRef(BUFFER_REF stringBuffer,const size_t index,
						const size_t rawPosition);

		CharacterRef(const CharacterRef &source);

		const Ceng::INT32 Bytes() const;

		explicit operator const CHAR32() const;

		explicit operator const char32_t() const;

		const Ceng::INT32 ToChar(char *output) const;

		const Ceng::INT32 ToWideChar(wchar_t *output) const;

		const Ceng::INT32 ToUTF16(char16_t *output) const;

		CharacterRef& operator = (const CharacterRef &source);

		CharacterRef& operator = (const CHAR32 source);

		const bool operator == (const Ceng::INT8 ascii) const;
		const bool operator != (const Ceng::INT8 ascii) const;
	
	};

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::CharacterRef() : stringBuffer(nullptr)
	{
		index = 0;
		rawPosition = 0;
		bytes = 0;
	}


	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::~CharacterRef()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::CharacterRef(BUFFER_REF stringBuffer,const size_t index,
															const size_t rawPosition) 
		: stringBuffer(stringBuffer)
	{
		this->index = index;
		this->rawPosition = rawPosition;

		bytes = typename CHARACTER_TYPE::CalculateSize(stringBuffer.GetPointer(0));
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::CharacterRef(const CharacterRef &source) 
		: stringBuffer(source.stringBuffer)
	{
		index = source.index;
		rawPosition = source.rawPosition;

		bytes = source.bytes;
	}
	
	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	const Ceng::INT32 CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::Bytes() const
	{
		return bytes;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::operator const CHAR32() const
	{
		if (stringBuffer == nullptr)
		{
			return '\0';
		}

		return typename CHARACTER_TYPE::ToUTF32(stringBuffer.GetPointer(rawPosition));
	}

	template<class CHARACTER_TYPE, class DATA_ELEMENT, class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE, DATA_ELEMENT, BUFFER_REF>::operator const char32_t() const
	{
		if (stringBuffer == nullptr)
		{
			return '\0';
		}

		return (char32_t)typename CHARACTER_TYPE::ToUTF32(stringBuffer.GetPointer(rawPosition));
	}

	template<class CHARACTER_TYPE, class DATA_ELEMENT, class BUFFER_REF>
	const bool CharacterRef<CHARACTER_TYPE, DATA_ELEMENT, BUFFER_REF>::operator == (const Ceng::INT8 ascii) const
	{
		CHAR32 value = CHAR32(*this);

		return (value == ascii);
	}

	template<class CHARACTER_TYPE, class DATA_ELEMENT, class BUFFER_REF>
	const bool CharacterRef<CHARACTER_TYPE, DATA_ELEMENT, BUFFER_REF>::operator != (const Ceng::INT8 ascii) const
	{
		return !(*this == ascii);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	const Ceng::INT32 CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::ToChar(char *output) const
	{
		return typename CHARACTER_TYPE::ToChar(stringBuffer.GetPointer(rawPosition),output);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	const Ceng::INT32 CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::ToWideChar(wchar_t *output) const
	{
		return typename CHARACTER_TYPE::ToWideChar(stringBuffer.GetPointer(rawPosition),output);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	const Ceng::INT32 CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::ToUTF16(char16_t *output) const
	{
		return typename CHARACTER_TYPE::ToUTF16(stringBuffer.GetPointer(rawPosition),output);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>& 
		CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::operator = (const CharacterRef &source)
	{
		return *this = CHAR32(source);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>& 
		CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF>::operator = (const CHAR32 source)
	{
		UINT8 encoding[4];
		UINT8 newBytes;

		newBytes = typename CHARACTER_TYPE::EncodeUTF32(source,encoding);

		if (newBytes > bytes)
		{
			stringBuffer.Insert(rawPosition,newBytes-bytes,0);
		}
		else if (newBytes < bytes)
		{
			stringBuffer.Erase(rawPosition,rawPosition+bytes-newBytes);
		}

		UINT32 k;

		UINT8 *ptr = stringBuffer.GetPointer(rawPosition);

		for(k=0;k<newBytes;k++)
		{
			ptr[k] = encoding[k];
		}

		bytes = newBytes;

		return *this;
	}
}

#include <iostream>

namespace std
{
	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	ostream& operator << (ostream &stream,const Ceng::CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF> &source)
	{
		char bytes[4];
		Ceng::INT32 length;

		length = source.ToChar(bytes);

		Ceng::INT32 k;

		for(k=0;k<length;k++)
		{
			stream << bytes[k];
		}

		return stream;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF>
	wostream& operator << (wostream &stream,const Ceng::CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF> &source)
	{
		wchar_t encoding[2];
		Ceng::INT32 bytes=0;
		
		bytes = source.ToWideChar(encoding);
		
		Ceng::INT32 k;

		for(k=0;k<bytes;k++)
		{
			stream << *reinterpret_cast<wchar_t*>(&encoding[k]);
		}

		return stream;
	}
}

#endif