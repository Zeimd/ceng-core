/*****************************************************************************
*
* gl32-state-change.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef CENG_GL32_STATE_CHANGE_H
#define CENG_GL32_STATE_CHANGE_H

namespace Ceng
{
	class GL32_StateChange
	{
	public:
		GL32_StateChange();
		virtual ~GL32_StateChange();

		virtual void GL32_ApplyState() = 0;
	};
}

#endif