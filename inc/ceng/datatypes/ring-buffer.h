/*****************************************************************************
*
* ring-buffer.h
*
* By Jari Korkala 8/2014
*
*****************************************************************************/

#ifndef CENG_RING_BUFFER_H
#define CENG_RING_BUFFER_H

#include <atomic>

#include "basic-types.h"
#include "boolean.h"
#include "return-val.h"

#include "aligned-buffer.h"

namespace Ceng
{
	template<class t_ElemType>
	class RingBuffer
	{
	protected:

		AlignedBuffer<t_ElemType> linearBuffer;

		std::atomic<Ceng::INT32> front;

		std::atomic<Ceng::INT32> back;

	public:

		template<class t_ElemType>
		class RingBufferIterator
		{
		protected:
			RingBuffer<t_ElemType>* buffer;

			Ceng::INT32 position;

		public:

			RingBufferIterator(RingBuffer<t_ElemType>* buffer, Ceng::INT32 position)
				: buffer(buffer), position(position)
			{

			}

			RingBufferIterator(const RingBufferIterator<t_ElemType>& source)
				: buffer(source.buffer), position(source.position)
			{

			}

			RingBufferIterator& operator = (const RingBufferIterator<t_ElemType>& source)
			{
				buffer = source.buffer;
				position = source.position;

				return *this;
			}


			t_ElemType& operator * ()
			{
				return buffer->linearBuffer[position];
			}

			t_ElemType* operator -> ()
			{
				return &buffer->linearBuffer[position];
			}

			RingBufferIterator<t_ElemType>& operator ++ ()
			{
				position = buffer->WrapIndex(position + 1);

				return *this;
			}

			RingBufferIterator<t_ElemType>& operator -- ()
			{
				position = buffer->DecrAndWrap(position);

				return *this;
			}

			RingBufferIterator<t_ElemType> operator ++ (int)
			{
				RingBufferIterator<t_ElemType> out{ *this };

				position = buffer->WrapIndex(position + 1);

				return out;
			}

			RingBufferIterator<t_ElemType> operator -- (int)
			{
				RingBufferIterator<t_ElemType> out{ *this };

				position = buffer->DecrAndWrap(position);

				return out;
			}

			bool operator == (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer != other.buffer)
				{
					return false;
				}

				return (position == other.position);
			}

			bool operator != (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer == other.buffer)
				{
					return true;
				}

				return (position != other.position);
			}

			bool operator < (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer != other.buffer)
				{
					return false;
				}

				return (position < other.position);
			}

			bool operator > (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer != other.buffer)
				{
					return false;
				}

				return (position > other.position);
			}

			bool operator <= (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer != other.buffer)
				{
					return false;
				}

				return (position <= other.position);
			}

			bool operator >= (const RingBufferIterator<t_ElemType>& other)
			{
				if (buffer != other.buffer)
				{
					return false;
				}

				return (position >= other.position);
			}
		};

	public:

		RingBuffer();

		RingBuffer(const RingBuffer &source);
		RingBuffer(RingBuffer &&source);

		~RingBuffer();

		static RingBuffer Allocate(const Ceng::UINT32 elements,const Ceng::UINT32 alignment);
		
	protected:

		RingBuffer(AlignedBuffer<t_ElemType>&& buffer);

		const Ceng::INT32 RingDistance() const;

	public:

		const Ceng::INT32 WrapIndex(const Ceng::INT32 index) const;		

		const Ceng::INT32 DecrAndWrap(const Ceng::INT32 index) const;

	public:

		void Clear();

		const Ceng::CRESULT PushBack(const t_ElemType &input);
		const Ceng::CRESULT PushBack(t_ElemType &&input);

		const Ceng::CRESULT PopFront();
		const Ceng::CRESULT PopFront(Ceng::UINT32 amount);

		t_ElemType& Front();
		const t_ElemType& Front() const;

		const t_ElemType ReadAbsoluteIndex(const Ceng::UINT32 index) const;

		t_ElemType operator [] (const Ceng::UINT32 index);
		const t_ElemType operator [] (const Ceng::UINT32 index) const;

		const Ceng::CRESULT FrontPtr(t_ElemType **front) const;

		const Ceng::CRESULT BackPtr(t_ElemType **back) const;

		const Ceng::INT32 Capacity() const;

		const Ceng::INT32 Size() const;

		const Ceng::INT32 FrontPos() const;
		const Ceng::INT32 BackPos() const;

		const Ceng::BOOL IsEmpty() const;

		const Ceng::BOOL IsFull() const;

		RingBufferIterator<t_ElemType> Begin();

		RingBufferIterator<t_ElemType> End();

		RingBuffer& operator = (const RingBuffer &source);
		RingBuffer& operator = (RingBuffer &&source);
	};

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBuffer()
	{
		front = 0;
		back = 0;
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBuffer(AlignedBuffer<t_ElemType> &&buffer)
		: linearBuffer(buffer)
	{
		front.store(0);
		back.store(0);
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::~RingBuffer()
	{
		Clear();
	}

	template<class t_ElemType>
	void RingBuffer<t_ElemType>::Clear()
	{
		if (linearBuffer != nullptr)
		{
			while(front != back)
			{
				linearBuffer[front].~t_ElemType();

				++front;
				front = WrapIndex(front);
			}

			back.store(front);
		}
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType> RingBuffer<t_ElemType>::Allocate(const Ceng::UINT32 elements,const Ceng::UINT32 alignment)
	{
		// NOTE: We leave one element empty in order to detect when the buffer is full,
		//       so add one to number of elements so that user sees expected number of elements.

		auto buffer = AlignedBuffer<t_ElemType>(elements+1,alignment);

		return RingBuffer<t_ElemType>(std::move(buffer));
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBuffer(const RingBuffer<t_ElemType> &source)
	{

		front = 0;
		back = 0;

		linearBuffer = AlignedBuffer<t_ElemType>(source.linearBuffer.GetElements(),
			source.linearBuffer.GetAlignment());

		// Call object copy constructors

		Ceng::UINT32 k=source.front;

		while(k != source.back)
		{
			new (&linearBuffer[back]) t_ElemType(source.linearBuffer[k]); 

			++k;
			k = source.WrapIndex(k);

			++back;
			back = WrapIndex(back);
		}

	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBufferIterator<t_ElemType> RingBuffer<t_ElemType>::Begin()
	{
		return RingBufferIterator<t_ElemType>(this, front);
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBufferIterator<t_ElemType> RingBuffer<t_ElemType>::End()
	{
		return RingBufferIterator<t_ElemType>(this, back);
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>& RingBuffer<t_ElemType>::operator = (const RingBuffer<t_ElemType> &source)
	{
		if (&source == this)
		{
			return *this;
		}

		Clear();

		front = 0;
		back = 0;

		linearBuffer = AlignedBuffer<t_ElemType>(source.linearBuffer.GetElements(),
			source.linearBuffer.GetAlignment());

		// Call object copy constructors

		Ceng::UINT32 k=source.front;

		while(k != source.back)
		{
			new (&linearBuffer[back]) t_ElemType(source.linearBuffer[k]); 

			++k;
			k = source.WrapIndex(k);

			++back;
			back = WrapIndex(back);
		}

		return *this;
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>::RingBuffer(RingBuffer<t_ElemType> &&source)
	{
		front.store(source.front);
		back.store(source.back);

		linearBuffer = std::move(source.linearBuffer);
	}

	template<class t_ElemType>
	RingBuffer<t_ElemType>& RingBuffer<t_ElemType>::operator = (RingBuffer<t_ElemType> &&source)
	{
		if (&source == this)
		{
			return *this;
		}

		Clear();

		front.store(source.front);
		back.store(source.back);

		linearBuffer = std::move(source.linearBuffer);

		return *this;
	}


	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::FrontPos() const
	{
		return front;
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::BackPos() const
	{
		return back;
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::Capacity() const
	{
		return linearBuffer.GetElements()-1;
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::RingDistance() const
	{
		Ceng::INT32 dist = back-front;

		if (dist < 0)
		{
			dist = (linearBuffer.GetElements()-front + back);
		}

		return dist;
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::Size() const
	{
		return RingDistance();
		//return linearBuffer.GetElements()-1-RingDistance();
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::WrapIndex(const Ceng::INT32 index) const
	{
		if (index == linearBuffer.GetElements())
		{
			return 0;
		}

		return index;
	}

	template<class t_ElemType>
	const Ceng::INT32 RingBuffer<t_ElemType>::DecrAndWrap(const Ceng::INT32 index) const
	{
		if (index == 0)
		{
			return linearBuffer.GetElements() - 1;
		}

		return index - 1;
	}

	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::PushBack(const t_ElemType &input)
	{
		if (IsFull())
		{
			return Ceng::CE_ERR_FAIL;
		}

		// Call copy constructor

		new (&linearBuffer[back]) t_ElemType(input);

		// Calculate final value of back index before
		// updating atomically

		Ceng::INT32 tempBack = back;

		++tempBack;

		back = WrapIndex(tempBack);
	
		return Ceng::CE_OK;
	}

	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::PushBack(t_ElemType &&input)
	{
		if (IsFull())
		{
			return Ceng::CE_ERR_FAIL;
		}

		// Call copy constructor

		new (&linearBuffer[back]) t_ElemType(std::move(input));

		// Calculate final value of back index before
		// updating atomically

		Ceng::INT32 tempBack = back;

		++tempBack;

		back = WrapIndex(tempBack);
	
		return Ceng::CE_OK;
	}

	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::PopFront()
	{
		if (IsEmpty())
		{
			return Ceng::CE_ERR_FAIL;
		}

		// Call destructor on front object

		linearBuffer[front].~t_ElemType();

		// Calculate final value of front index before
		// updating atomically

		Ceng::INT32 temp = front;

		++temp;

		front = WrapIndex(temp);

		return Ceng::CE_OK;
	}

	// Pop given amount of elements from front of queue.
	// Unsafe: safe amount to pop must be determined in advance.
	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::PopFront(Ceng::UINT32 amount)
	{
		if (IsEmpty())
		{
			return Ceng::CE_ERR_FAIL;
		}

		Ceng::INT32 index = front;

		for (int k = 0; k < amount; ++k)
		{
			linearBuffer[index].~t_ElemType();

			index = WrapIndex(index + 1);
		}

		front = index;

		return Ceng::CE_OK;
	}

	template<class t_ElemType>
	const Ceng::BOOL RingBuffer<t_ElemType>::IsEmpty() const
	{
		return (front == back);
	}

	template<class t_ElemType>
	const Ceng::BOOL RingBuffer<t_ElemType>::IsFull() const
	{
		return (RingDistance() == linearBuffer.GetElements()-1);
	}

	template<class t_ElemType>
	const t_ElemType RingBuffer<t_ElemType>::ReadAbsoluteIndex(const Ceng::UINT32 index) const
	{
		if (index <= linearBuffer.GetElements()-1)
		{
			return linearBuffer[index];
		}

		return t_ElemType();
	}

	template<class t_ElemType>
	t_ElemType& RingBuffer<t_ElemType>::Front()
	{
		if (IsEmpty())
		{
			return linearBuffer[0];
		}

		return linearBuffer[front];
	}

	template<class t_ElemType>
	const t_ElemType& RingBuffer<t_ElemType>::Front() const
	{
		if (IsEmpty())
		{
			return linearBuffer[0];
		}

		return linearBuffer[front];
	}
	
	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::FrontPtr(t_ElemType **out) const
	{
		if (IsEmpty())
		{
			return Ceng::CE_ERR_FAIL;
		}

		*out = &linearBuffer[front];

		return Ceng::CE_OK;
	}

	template<class t_ElemType>
	const Ceng::CRESULT RingBuffer<t_ElemType>::BackPtr(t_ElemType **out) const
	{
		if (IsEmpty())
		{
			return Ceng::CE_ERR_FAIL;
		}

		*out = &linearBuffer[DecrAndWrap(back)];

		return Ceng::CE_OK;
	}

	template<class t_ElemType>
	t_ElemType RingBuffer<t_ElemType>::operator [] (const Ceng::UINT32 index)
	{
		Ceng::UINT32 realIndex = front + index;

		if (realIndex >= linearBuffer.GetElements())
		{
			return realIndex;
		}

		return realIndex - linearBuffer.GetElements();
	}

	template<class t_ElemType>
	const t_ElemType RingBuffer<t_ElemType>::operator [] (const Ceng::UINT32 index) const
	{
		Ceng::UINT32 realIndex = front + index;

		if (realIndex >= linearBuffer.GetElements())
		{
			return realIndex;
		}

		return realIndex - linearBuffer.GetElements();
	}

}

#endif