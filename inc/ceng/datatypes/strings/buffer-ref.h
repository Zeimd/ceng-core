/*****************************************************************************
*
* buffer-ref.h
*
* By Jari Korkala 3/2014
*
*****************************************************************************/

#ifndef CENG_STRING_BUFFER_REF_H
#define CENG_STRING_BUFFER_REF_H

#include "../basic-types.h"
#include "../boolean.h"

#include <vector>

namespace Ceng
{
	template<class DATA_ELEMENT>
	class PointerRef
	{
	protected:

		DATA_ELEMENT *buffer;

	public:

		PointerRef();
		~PointerRef();

		PointerRef(DATA_ELEMENT *buffer);
	
		PointerRef(const PointerRef &source);

		PointerRef& operator = (const PointerRef &source);

		const ptrdiff_t MaxIndex() const;

		DATA_ELEMENT* GetPointer(const ptrdiff_t offset) const;

		const Ceng::BOOL operator == (const PointerRef &other) const;

		const Ceng::BOOL operator != (const PointerRef &other) const;
	};

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::~PointerRef()
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef(DATA_ELEMENT *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>::PointerRef(const PointerRef &source) : buffer(source.buffer)
	{
	}

	template<class DATA_ELEMENT>
	PointerRef<DATA_ELEMENT>& PointerRef<DATA_ELEMENT>::operator = (const PointerRef &source)
	{
		buffer = source.buffer;
		return *this;
	}

	template<class DATA_ELEMENT>
	const ptrdiff_t PointerRef<DATA_ELEMENT>::MaxIndex() const
	{
		return 0;
	}

	template<class DATA_ELEMENT>
	DATA_ELEMENT* PointerRef<DATA_ELEMENT>::GetPointer(const ptrdiff_t offset) const
	{
		return &buffer[offset];
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL PointerRef<DATA_ELEMENT>::operator == (const PointerRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL PointerRef<DATA_ELEMENT>::operator != (const PointerRef &other) const
	{
		return !(*this == other);
	}

	//**********************************************************************************
	// class VectorRef

	template<class DATA_ELEMENT>
	class VectorRef 
	{
	protected:

		std::vector<DATA_ELEMENT> *buffer;

	public:

		VectorRef();
		~VectorRef();

		VectorRef(std::vector<DATA_ELEMENT> *buffer);

		VectorRef& operator = (const VectorRef &other);

		const ptrdiff_t MaxIndex() const;

		const Ceng::BOOL operator == (const VectorRef &other) const;

		const Ceng::BOOL operator != (const VectorRef &other) const;

		const Ceng::BOOL operator == (const std::vector<DATA_ELEMENT> *other) const;

		const Ceng::BOOL operator != (const std::vector<DATA_ELEMENT> *other) const;

		DATA_ELEMENT* GetPointer(const ptrdiff_t offset) const;

		void Insert(const ptrdiff_t startPos,const ptrdiff_t amount,const Ceng::UINT8 value);

		void Erase(const ptrdiff_t startPos,const ptrdiff_t endPos);
	};

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::VectorRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::~VectorRef()
	{
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>::VectorRef(std::vector<DATA_ELEMENT> *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	VectorRef<DATA_ELEMENT>& VectorRef<DATA_ELEMENT>::operator = (const VectorRef &other)
	{
		buffer = other.buffer;

		return *this;
	}

	template<class DATA_ELEMENT>
	const ptrdiff_t VectorRef<DATA_ELEMENT>::MaxIndex() const
	{
		return buffer->size()-1;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator == (const VectorRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator != (const VectorRef &other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator == (const std::vector<DATA_ELEMENT> *other) const
	{
		return buffer == other;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL VectorRef<DATA_ELEMENT>::operator != (const std::vector<DATA_ELEMENT> *other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	DATA_ELEMENT* VectorRef<DATA_ELEMENT>::GetPointer(const ptrdiff_t offset) const
	{
		return &(*buffer)[offset];
	}

	template<class DATA_ELEMENT>
	void VectorRef<DATA_ELEMENT>::Insert(const ptrdiff_t startPos,const ptrdiff_t amount,const Ceng::UINT8 value)
	{
		buffer->insert(buffer->begin()+startPos,amount,value);
	}

	template<class DATA_ELEMENT>
	void VectorRef<DATA_ELEMENT>::Erase(const ptrdiff_t startPos,const ptrdiff_t endPos)
	{
		buffer->erase(buffer->begin()+startPos,buffer->begin()+endPos);
	}

	//*****************************************************************************************
	// Class ConstVectorRef

	template<class DATA_ELEMENT>
	class ConstVectorRef 
	{
	protected:

		const std::vector<DATA_ELEMENT> *buffer;

	public:

		ConstVectorRef();
		~ConstVectorRef();

		ConstVectorRef(const std::vector<DATA_ELEMENT> *buffer);

		const ptrdiff_t MaxIndex() const;

		const Ceng::BOOL operator == (const ConstVectorRef &other) const;

		const Ceng::BOOL operator != (const ConstVectorRef &other) const;

		const Ceng::BOOL operator == (const std::vector<DATA_ELEMENT> *other) const;

		const Ceng::BOOL operator != (const std::vector<DATA_ELEMENT> *other) const;

		const DATA_ELEMENT* GetPointer(const ptrdiff_t offset) const;
	};

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::ConstVectorRef()
	{
		buffer = nullptr;
	}

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::~ConstVectorRef()
	{
	}

	template<class DATA_ELEMENT>
	ConstVectorRef<DATA_ELEMENT>::ConstVectorRef(const std::vector<DATA_ELEMENT> *buffer) : buffer(buffer)
	{
	}

	template<class DATA_ELEMENT>
	const ptrdiff_t ConstVectorRef<DATA_ELEMENT>::MaxIndex() const
	{
		return buffer->size()-1;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator == (const ConstVectorRef &other) const
	{
		return buffer == other.buffer;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator != (const ConstVectorRef &other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator == (const std::vector<DATA_ELEMENT> *other) const
	{
		return buffer == other;
	}

	template<class DATA_ELEMENT>
	const Ceng::BOOL ConstVectorRef<DATA_ELEMENT>::operator != (const std::vector<DATA_ELEMENT> *other) const
	{
		return !(*this == other);
	}

	template<class DATA_ELEMENT>
	const DATA_ELEMENT* ConstVectorRef<DATA_ELEMENT>::GetPointer(const ptrdiff_t offset) const
	{
		if (offset < 0)
		{
			return nullptr;
		}

		return &(*buffer)[offset];
	}
}

#endif