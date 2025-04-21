#pragma once

#ifndef CENG_SWR_CYCLIC_COUNTER_H
#define CENG_SWR_CYCLIC_COUNTER_H

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	class CyclicCounter
	{
	private:
		Ceng::UINT32 limit;
		Ceng::UINT32 value;

	public:

		CyclicCounter(Ceng::UINT32 limit)
			: limit(limit), value(0)
		{

		}

		CyclicCounter(Ceng::UINT32 limit, Ceng::UINT32 value)
			: limit(limit), value(value% limit)
		{

		}

		CyclicCounter(CyclicCounter& source)
			: limit(source.limit), value(source.value)
		{

		}

		CyclicCounter& operator++()
		{
			CyclicIncrement();

			return *this;
		}

		CyclicCounter operator++(int)
		{
			CyclicCounter temp{ *this };

			CyclicIncrement();

			return temp;
		}

		operator Ceng::UINT32()
		{
			return value;
		}

	private:

		void CyclicIncrement()
		{
			++value;

			if (value == limit)
			{
				value = 0;
			}
		}
	};
}

#endif