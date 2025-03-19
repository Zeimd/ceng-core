/*****************************************************************************
*
* iterator.h
*
* By Jari Korkala 3/2014
*
*****************************************************************************/

#ifndef CENG_STRING_ITERATOR_H
#define CENG_STRING_ITERATOR_H

#include "character.h"
#include "buffer-ref.h"

#include "../basic-types.h"
#include "../boolean.h"

namespace Ceng
{
	class BaseIterator
	{
	protected:

		/**
		 * Element currently pointed at. For variable-length encodings,
		 * not equal to rawPosition.
		 */
		size_t index;

		/**
		 * Actual offset in the container. 
		 */
		size_t rawPosition;


	public:

		BaseIterator() : index(0), rawPosition(0)
		{
		}

		~BaseIterator()
		{
		}

		const size_t Index() const
		{
			return index;
		}

		const size_t RawPosition() const
		{
			return rawPosition;
		}
	};


	//***************************************************************************
	// Class FixedLengthIterator

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	class FixedLengthIterator
	{
	public:
		typedef typename CHARACTER_TYPE CHARACTER_TYPE;

		typedef CharacterRef<CHARACTER_TYPE,const DATA_ELEMENT,const PointerRef<const DATA_ELEMENT>> CONST_REF_TYPE;

		FixedLengthIterator();
		~FixedLengthIterator();

		static Ceng::INT64 StepForward(const DATA_ELEMENT *character,size_t *index,
										const size_t maxIndex);

		static Ceng::INT64 StepForwardMultiple(const DATA_ELEMENT *characters,
											size_t *index,const size_t maxIndex,
											const Ceng::INT64 delta);

		static Ceng::INT64 StepBackward(const DATA_ELEMENT *characters,
											size_t *index,const size_t startPos);

		static Ceng::INT64 StepBackwardMultiple(const DATA_ELEMENT *characters,size_t *index,
											const size_t startPos,const Ceng::INT64 delta);

	};

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::FixedLengthIterator()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::~FixedLengthIterator()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepForward(const DATA_ELEMENT *character,size_t *index,const size_t maxIndex)
	{
		Ceng::INT32 step = 0;

		if (*index < maxIndex)
		{
			(*index)++;
			step = 1;
		}

		return step;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepForwardMultiple(const DATA_ELEMENT *characters,
							size_t *index,const size_t maxIndex,
							const Ceng::INT64 delta)
	{
		Ceng::INT32 newIndex = *index + delta;

		if (newIndex > maxIndex)
		{
			newIndex = maxIndex;
		}

		Ceng::INT32 step = newIndex - *index;

		*index = newIndex;

		return step;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepBackward(const DATA_ELEMENT *characters,
						size_t *index,const size_t startPos)
	{
		Ceng::INT32 step = 0;

		if (*index > -1)
		{
			(*index)--;
			step = -1;
		}

		return step;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 FixedLengthIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepBackwardMultiple(const DATA_ELEMENT *characters,size_t *index,
								const size_t startPos,const Ceng::INT64 delta)
	{
		Ceng::INT64 newIndex = *index - delta;

		if (newIndex < -1)
		{
			newIndex = -1;
		}

		Ceng::INT64 step = newIndex - *index;

		*index = newIndex;

		return step;
	}

	//*****************************************************************************
	// Class VaryingIterator

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	class VaryingIterator
	{	
	public:

		typedef typename CHARACTER_TYPE CHARACTER_TYPE;

		typedef CharacterRef<CHARACTER_TYPE,const DATA_ELEMENT,const PointerRef<const DATA_ELEMENT>> CONST_REF_TYPE;

		VaryingIterator();
		~VaryingIterator();

		static Ceng::INT64 StepForward(const DATA_ELEMENT *character,size_t *index,
										const size_t maxIndex) ;

		static Ceng::INT64 StepForwardMultiple(const DATA_ELEMENT *characters,
											size_t *index,const size_t maxIndex,
											const Ceng::INT64 delta) ;

		static Ceng::INT64 StepBackward(const DATA_ELEMENT *characters,
											size_t *index,const size_t startPos) ;

		static Ceng::INT64 StepBackwardMultiple(const DATA_ELEMENT *characters,size_t *index,
											const size_t startPos,const Ceng::INT64 delta) ;
	};

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::VaryingIterator()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::~VaryingIterator()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepForward(const DATA_ELEMENT *character,size_t *p_index,const size_t maxIndex) 
	{
		if (*p_index == -1)
		{
			*p_index = 0;
			return 1;
		}

		CONST_REF_TYPE step(PointerRef<const DATA_ELEMENT>(character),0,0);

		if (step.Bytes() > 0)
		{
			(*p_index)++;
		}

		return step.Bytes();
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepForwardMultiple(const DATA_ELEMENT *characters,
								size_t *index,const size_t maxIndex,
								const Ceng::INT64 delta) 
	{
		if (delta <= 0)
		{
			return 0;
		}

		if (*index == -1)
		{
			*index = 0;
			return 1;
		}	

		Ceng::INT64 k=0;

		Ceng::INT64 step;

		Ceng::INT64 totalStep=0;

		do
		{
			step = StepForward(&characters[totalStep],index,maxIndex);

			totalStep += step;
			k++;

		} while( step > 0 && k < delta);

		return totalStep;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepBackward(const DATA_ELEMENT *characters,
						size_t *index,const size_t startPos) 
	{
		if (startPos <= 0)
		{
			*index = -1;
			return -1;
		}

		Ceng::INT64 k = startPos-1;

		(*index)--;

		do
		{
			Ceng::UINT8 temp = characters[k];

			Ceng::INT32 bytes = typename CHARACTER_TYPE::GetByteCount(temp);

			if (bytes > 0)
			{
				break;
			}

			k--;
		} while(k > 0);

		return k;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT>
	Ceng::INT64 VaryingIterator<CHARACTER_TYPE,DATA_ELEMENT>::
		StepBackwardMultiple(const DATA_ELEMENT *characters,size_t *index,
								const size_t startPos,const Ceng::INT64 delta) 
	{
		if (delta <= 0)
		{
			return startPos;
		}

		if (startPos <= 0)
		{
			*index = -1;
			return -1;
		}		

		Ceng::INT64 k=0;

		Ceng::INT64 outPos=startPos;

		do
		{
			outPos = StepBackward(&characters[outPos],index,outPos);

			k++;

		} while( outPos > -1 && k < delta);

		return outPos;
	}

	//***************************************************************************************
	// Class StringIterator

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	class StringIterator : public BaseIterator
	{
	protected:

		BUFFER_REF buffer;

	public:

		typedef CharacterRef<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF> REF_TYPE;

		~StringIterator();

		StringIterator();

		StringIterator(const BUFFER_REF &buffer);

		StringIterator(const BUFFER_REF &buffer,const size_t index,const size_t rawPosition);

		StringIterator(const StringIterator &source);

		StringIterator& operator = (StringIterator source);

		void Swap(StringIterator &a,StringIterator &b);

		BUFFER_REF Buffer() const;

		StringIterator& operator ++ ();

		const StringIterator operator ++ (int);

		StringIterator& operator += (const Ceng::INT64 delta);

		const StringIterator operator + (const Ceng::INT64 delta);

		StringIterator& operator -- ();

		const StringIterator operator -- (int);

		StringIterator& operator -= (const Ceng::INT64 delta);

		const StringIterator operator - (const Ceng::INT64 delta);

		const Ceng::INT32 operator - (const StringIterator &other);

		REF_TYPE operator [] (const Ceng::INT64 delta) const;
		
		REF_TYPE operator * () const;

		const Ceng::BOOL operator == (const StringIterator &other) const;

		const Ceng::BOOL operator != (const StringIterator &other) const;

		const Ceng::BOOL operator < (const StringIterator &other) const;

		const Ceng::BOOL operator > (const StringIterator &other) const;

		const Ceng::BOOL operator >= (const StringIterator &other) const;

		const Ceng::BOOL operator <= (const StringIterator &other) const;
	};

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		~StringIterator()
	{
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		StringIterator() : buffer(BUFFER_REF())
	{
	}	

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		StringIterator(const BUFFER_REF &buffer) : buffer(buffer)
	{
		index = 0;
		rawPosition = 0;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		StringIterator(const BUFFER_REF &buffer,size_t index,const size_t rawPosition)
		: buffer(buffer)
	{
		this->index = index;
		this->rawPosition = rawPosition;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		StringIterator(const StringIterator &source) : buffer(source.buffer)
	{
		index = source.index;
		rawPosition = source.rawPosition;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>& 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>
		::operator = (StringIterator source)
	{
		Swap(*this,source);

		return *this;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	void StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		Swap(StringIterator &a,StringIterator &b)
	{
		std::swap(a.buffer,b.buffer);
		std::swap(a.index,b.index);
		std::swap(a.rawPosition,b.rawPosition);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	BUFFER_REF StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		Buffer() const
	{
		return buffer;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>& 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator ++ ()
	{
		rawPosition += ITERATOR_TYPE::StepForward(buffer.GetPointer(rawPosition),&index,buffer.MaxIndex());

		return *this;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator ++ (int)
	{
		StringIterator temp(*this);

		operator++();

		return temp;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>& 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator += (const Ceng::INT64 delta)
	{
		if (delta < 0)
		{
			rawPosition = ITERATOR_TYPE::StepBackwardMultiple(buffer.GetPointer(0),&index,
									rawPosition,-delta);
		}
		else
		{
			rawPosition += ITERATOR_TYPE::StepForwardMultiple(buffer.GetPointer(rawPosition),&index,
									buffer.MaxIndex(),delta);
		}

		return *this;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE> 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator + (const Ceng::INT64 delta)
	{
		StringIterator temp(*this);

		temp += delta;

		return temp;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>& 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator -- ()
	{
		rawPosition = ITERATOR_TYPE::StepBackward(buffer.GetPointer(0),&index,rawPosition);

		return *this;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator -- (int)
	{
		StringIterator temp(*this);

		operator--();

		return temp;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>& 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator -= (const Ceng::INT64 delta)
	{
		return *this += (-delta);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE> 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator - (const Ceng::INT64 delta)
	{
		StringIterator temp(*this);

		temp -= delta;

		return temp;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::INT32 StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator - (const StringIterator &other)
	{
		return index - other.index;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	typename StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::REF_TYPE 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator [] (const Ceng::INT64 delta) const
	{
		StringIterator temp(*this);

		temp += delta;

		return REF_TYPE(buffer,temp.Index(),temp.RawPosition());			
	}
		
	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	typename StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::REF_TYPE 
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator * () const
	{
		return REF_TYPE(buffer,index,rawPosition);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator == (const StringIterator &other) const
	{
		if (buffer != other.buffer)
		{
			return false;
		}

		if (rawPosition != other.rawPosition)
		{
			return false;
		}

		return true;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator != (const StringIterator &other) const
	{
		return !(*this == other);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator < (const StringIterator &other) const
	{
		if (buffer != other.buffer)
		{
			return false;
		}

		if (rawPosition < other.rawPosition)
		{
			return true;
		}

		return false;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator > (const StringIterator &other) const
	{
		if (buffer != other.buffer)
		{
			return false;
		}

		if (rawPosition > other.rawPosition)
		{
			return true;
		}

		return false;
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator >= (const StringIterator &other) const
	{
		return (*this == other) || (*this > other);
	}

	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const Ceng::BOOL StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE>::
		operator <= (const StringIterator &other) const
	{
		return (*this == other) || (*this < other);
	}
	
	template<class CHARACTER_TYPE,class DATA_ELEMENT,class BUFFER_REF,class ITERATOR_TYPE>
	const StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE> operator + (const Ceng::INT32 base,
															const StringIterator<CHARACTER_TYPE,
															DATA_ELEMENT,BUFFER_REF,ITERATOR_TYPE> &other)
	{
		StringIterator<CHARACTER_TYPE,DATA_ELEMENT,BUFFER_REF> temp(other);

		return temp += base;
	}

	//************************************************************************
	// Class ReverseIterator

	template<class ITERATOR_TYPE>
	class ReverseIterator
	{
	protected:
		ITERATOR_TYPE iterator;

		typedef typename ITERATOR_TYPE::REF_TYPE REF_TYPE;

	public:

		ReverseIterator();
		~ReverseIterator();

		ReverseIterator(const ITERATOR_TYPE &iterator);

		ReverseIterator(const ReverseIterator &source);

		ReverseIterator& operator = (const ITERATOR_TYPE &source);

		ReverseIterator& operator = (const ReverseIterator &source);

		const Ceng::BOOL operator == (const ReverseIterator &other);

		const Ceng::BOOL operator != (const ReverseIterator &other);

		const Ceng::BOOL operator < (const ReverseIterator &other);

		const Ceng::BOOL operator > (const ReverseIterator &other);

		const Ceng::BOOL operator <= (const ReverseIterator &other);

		const Ceng::BOOL operator >= (const ReverseIterator &other);

		ReverseIterator& operator ++ ();

		const ReverseIterator operator ++ (int);

		ReverseIterator& operator += (const ReverseIterator &other);

		ReverseIterator& operator += (const Ceng::INT32 delta);

		const ReverseIterator operator + (const ReverseIterator &other);

		const ReverseIterator operator + (const Ceng::INT32 delta);

		ReverseIterator& operator -- ();

		const ReverseIterator operator -- (int);

		ReverseIterator& operator -= (const ReverseIterator &other);

		ReverseIterator& operator -= (const Ceng::INT32 delta);


		const ReverseIterator operator - (const ReverseIterator &other);

		const ReverseIterator operator - (const Ceng::INT32 delta);

		REF_TYPE operator [] (const Ceng::INT32 delta) const;
		
		REF_TYPE operator * () const;

		ITERATOR_TYPE Iterator() const;
	
	};

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>::ReverseIterator() : iterator(ITERATOR_TYPE())
	{

	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>::~ReverseIterator()
	{
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>::ReverseIterator(const ITERATOR_TYPE &iterator) : iterator(iterator)
	{
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>::ReverseIterator(const ReverseIterator &source) : iterator(source.iterator)
	{
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator = (const ITERATOR_TYPE &source)
	{
		iterator = source;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator = (const ReverseIterator &source)
	{
		iterator = source.iterator;
		return *this;
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator == (const ReverseIterator &other)
	{
		return iterator == other.iterator;
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator != (const ReverseIterator &other)
	{
		return !(*this == other);
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator < (const ReverseIterator &other)
	{
		return (iterator > other.iterator);
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator > (const ReverseIterator &other)
	{
		return (iterator < other.iterator);
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator <= (const ReverseIterator &other)
	{
		return (iterator >= other.iterator);
	}

	template<class ITERATOR_TYPE>
	const Ceng::BOOL ReverseIterator<ITERATOR_TYPE>::operator >= (const ReverseIterator &other)
	{
		return (iterator <= other.iterator);
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator ++ ()
	{
		--iterator;
		return *this;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator ++ (int)
	{
		ReverseIterator temp(*this);

		operator++();

		return temp;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator += (const ReverseIterator &other)
	{
		iterator -= other.iterator;
		return *this;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator += (const Ceng::INT32 delta)
	{
		iterator -= delta;
		return *this;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator + (const ReverseIterator &other)
	{
		ReverseIterator temp(*this);

		temp += other;

		return temp;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator + (const Ceng::INT32 delta)
	{
		ReverseIterator temp(*this);

		temp += delta;

		return temp;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator -- ()
	{
		++iterator;
		return *this;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator -- (int)
	{
		ReverseIterator temp(*this);

		operator--();

		return temp;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator -= (const ReverseIterator &other)
	{
		iterator += other.iterator;
		return *this;
	}

	template<class ITERATOR_TYPE>
	ReverseIterator<ITERATOR_TYPE>& ReverseIterator<ITERATOR_TYPE>::operator -= (const Ceng::INT32 delta)
	{
		iterator += delta;
		return *this;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator - (const ReverseIterator &other)
	{
		ReverseIterator temp(*this);

		temp -= other;

		return temp;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> ReverseIterator<ITERATOR_TYPE>::operator - (const Ceng::INT32 delta)
	{
		ReverseIterator temp(*this);

		temp -= delta;

		return temp;
	}

	template<class ITERATOR_TYPE>
	typename ReverseIterator<ITERATOR_TYPE>::REF_TYPE 
		ReverseIterator<ITERATOR_TYPE>::operator [] (const Ceng::INT32 delta) const
	{
		ITERATOR_TYPE temp(*this);

		temp += delta;

		return REF_TYPE(temp.buffer,temp.Index(),temp.RawPosition());			
	}
		
	template<class ITERATOR_TYPE>
	typename ReverseIterator<ITERATOR_TYPE>::REF_TYPE 
		ReverseIterator<ITERATOR_TYPE>::operator * () const
	{
		return REF_TYPE(iterator.Buffer(),iterator.Index(),iterator.RawPosition());
	}

	template<class ITERATOR_TYPE>
	ITERATOR_TYPE ReverseIterator<ITERATOR_TYPE>::Iterator() const
	{
		return iterator;
	}

	template<class ITERATOR_TYPE>
	const ReverseIterator<ITERATOR_TYPE> operator + (const Ceng::INT32 base,
															const ReverseIterator<ITERATOR_TYPE> &other)
	{
		ReverseIterator<ITERATOR_TYPE> temp(other);

		return temp += base;
	}
}

#endif