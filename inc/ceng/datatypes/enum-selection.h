#pragma once

#ifndef CENG_ENUM_SELECTION_H
#define CENG_ENUM_SELECTION_H

#include "basic-types.h"

namespace Ceng
{
	template<typename T> 
	class EnumSelection
	{
	protected:

		Ceng::UINT32 data;		

	public:
		EnumSelection():
			data(0)
		{

		}

		EnumSelection(const EnumSelection& other) :
			data(other.data)
		{

		}

		EnumSelection(const EnumSelection&& other) :
			data(other.data)
		{

		}

		EnumSelection& operator = (const EnumSelection& other)
		{
			data = other.data;
			return *this;
		}

		EnumSelection& operator = (const EnumSelection&& other)
		{
			data = other.data;
			return *this;
		}

		EnumSelection operator | (const EnumSelection& other)
		{
			return EnumSelection(data | other.data);
		}

		EnumSelection operator & (const EnumSelection& other)
		{
			return EnumSelection(data & other.data);
		}

		EnumSelection operator ^ (const EnumSelection& other)
		{
			return EnumSelection(data ^ other.data);
		}

		EnumSelection& operator |= (const EnumSelection& other)
		{
			data |= other.data;
			return *this;
		}

		EnumSelection& operator &= (const EnumSelection& other)
		{
			data &= other.data;
			return *this;
		}

		EnumSelection& operator ^= (const EnumSelection& other)
		{
			data ^= other.data;
			return *this;
		}

		EnumSelection operator | (const T value)
		{
			return EnumSelection(data | value);
		}

		EnumSelection operator & (const T value)
		{
			return EnumSelection(data & value);
		}

		EnumSelection operator ^ (const T value)
		{
			return EnumSelection(data ^ value);
		}

		EnumSelection& operator |= (const T value)
		{
			data |= value;
			return *this;
		}

		EnumSelection& operator &= (const T value)
		{
			data &= value;
			return *this;
		}

		EnumSelection& operator ^= (const T value)
		{
			data ^= value;
			return *this;
		}

		EnumSelection& operator ~()
		{
			data = ~data;
			return *this;
		}

		void Add(const T value)
		{
			data |= value;
		}

		void Remove(const T value)
		{
			data &= ~value;
		}

		bool Check(const T value)
		{
			return (data & value);
		}

		bool operator == (const T value)
		{
			return (data & value);
		}

		bool operator != (const T value)
		{
			return !(*this == value);
		}

		bool operator == (const EnumSelection& other)
		{
			return (data == other.data);
		}

		bool operator != (const EnumSelection& other)
		{
			return !(*this == other);
		}

	};

	template<typename T>
	bool operator == (const T a, const typename EnumSelection<T>& b)
	{
		return b == a;
	}

	template<typename T>
	bool operator != (const T a, const typename EnumSelection<T>& b)
	{
		return b != a;
	}

	template<typename T>
	bool operator & (const T a, const typename EnumSelection<T>& b)
	{
		return b & a;
	}

	template<typename T>
	bool operator | (const T a, const typename EnumSelection<T>& b)
	{
		return b | a;
	}

	template<typename T>
	bool operator ^ (const T a, const typename EnumSelection<T>& b)
	{
		return b ^ a;
	}


}

#endif