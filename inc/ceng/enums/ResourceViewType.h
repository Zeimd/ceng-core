#pragma once

#ifndef CENG_RESOURCE_VIEW_TYPE_H
#define CENG_RESOURCE_VIEW_TYPE_H

namespace Ceng
{
	namespace ResourceViewType
	{
		enum value
		{
			texture_1d,
			texture_2d,
			texture_3d,

			texture_array_1d,
			texture_array_2d,

			multisample_texture_2d,
			multisample_texture_array_2d,

			cubemap,

			force_32b = 1 << 30,
		};
	}
}

#endif