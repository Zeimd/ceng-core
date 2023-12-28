/*****************************************************************************
*
* return-val.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_RETURN_VAL_H
#define _CONCEPT2_RETURN_VAL_H

//******************************************************************
// Function return codes

namespace Ceng
{
	enum CRESULT 
	{ 
		CE_OK = 1,
		CE_EXIT = 2,
		
		CE_WARNING_INCOMPATIBLE_VERTEX_SHADER = 3,
		CE_WARNING_NO_VERTEX_SHADER = 4,
		CE_WARNING_INCOMPATIBLE_PIXEL_SHADER = 5,
		CE_WARNING_NO_PIXEL_SHADER = 6,
		CE_WARNING_SCENE_DISABLED = 7,
		
		CE_ERR_FAIL = 8,
		
		CE_ERR_INCOMPATIBLE_FORMAT = 9,
		
		CE_ERR_INVALID_PARAM = 10,
		CE_ERR_NOT_SUPPORTED = 11,
		CE_ERR_OUT_OF_MEMORY = 12,
		
		CE_ERR_DATA_ALIGNMENT = 13,
		
		CE_ERR_PARAM = 14,
		CE_ERR_NULL_PTR = 15,
		CE_ERR_ALLOC = 16,
		CE_ERR_IO = 17, 
		CE_ERR_FILE_WRITE = 18,
		CE_ERR_FILE_READ = 19,

		CE_ERR_WAIT_TIMEOUT = 20 ,
		CE_ERR_ABANDONED_OBJECT = 21 ,

		CE_ERR_OUT_OF_VIDEO_MEMORY = 22 ,

		CE_ERR_UNDEFINED_UNIFORM = 23 ,

		CE_ERR_DEBUG_0 = 1 << 16 ,
		CE_ERR_DEBUG_1 = (1 << 16) + 1,
		CE_ERR_DEBUG_2 = (1 << 16) + 2,
		CE_ERR_DEBUG_3 = (1 << 16) + 3,
		CE_ERR_DEBUG_4 = (1 << 16) + 4,
		CE_ERR_DEBUG_5 = (1 << 16) + 5,
		CE_ERR_DEBUG_6 = (1 << 16) + 6,
		CE_ERR_DEBUG_7 = (1 << 16) + 7,
		CE_ERR_DEBUG_8 = (1 << 16) + 8,
		CE_ERR_DEBUG_9 = (1 << 16) + 9,
		CE_ERR_DEBUG_10 = (1 << 16) + 10,
		CE_ERR_DEBUG_11 = (1 << 16) + 11,
		CE_ERR_DEBUG_12 = (1 << 16) + 12,

		CE_ERR_UNIMPLEMENTED = (1 << 29) , 
		
		CRESULT_FORCE_32BIT = (1 << 30) ,
	};

} // Namespace Ceng

#endif