/*****************************************************************************
*
* primitive-data.h
*
* Created By Jari Korkala 31/8/2014
*
*****************************************************************************/

#ifndef CRENDER_PRIMITIVE_DATA_H
#define CRENDER_PRIMITIVE_DATA_H

#include "../datatypes/basic-types.h"
#include "../enums/primitive-type.h"

namespace Ceng
{
	class PrimitiveData
	{
	public:

		PRIMITIVE_TYPE::value primitiveType;

		Ceng::UINT8* fragmentPtr[4];
	};
}

#endif