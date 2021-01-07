/*****************************************************************************
*
* ceng.h
*
* By Jari Korkala 1/6/2011
*
*****************************************************************************/

#ifndef _CONCEPT2_MAIN_H
#define _CONCEPT2_MAIN_H

#define CONCEPT_VERSION 0
#define CONCEPT_MINOR 3
#define CONCEPT_BUILD 84

//#define _CE_FORCE_FIXEDPOINT

#include "ceng/platform.h"

#include "ceng/datatypes.h"

#include "ceng/lib/liblog.h"

#include "ceng/interfaces/render-device.h"
#include "ceng/interfaces/render-context.h"
#include "ceng/interfaces/swap-chain.h"

#include "ceng/interfaces/depth-stencil-desc.h"
#include "ceng/interfaces/rasterizer-state.h"

#include "ceng/interfaces/cubemap.h"
#include "ceng/interfaces/texture-2d.h"

#include "ceng/interfaces/vertex-buffer.h"
#include "ceng/interfaces/vertex-format.h"

#include "ceng/interfaces/vertex-shader.h"
#include "ceng/interfaces/pixel-shader.h"

#include "ceng/interfaces/index-buffer.h"
#include "ceng/interfaces/blend-state.h"
#include "ceng/interfaces/render-target-view.h"
#include "ceng/interfaces/shader-resource-view.h"

#include "ceng/interfaces/shader-program.h"

#include "ceng/interfaces/depth-stencil-state.h"
#include "ceng/interfaces/sampler-state.h"

#include "ceng/interfaces/shader-const.h"

#include "ceng/datatypes/rectangle.h"

#include "ceng/interfaces/render-enums.h"

#include "ceng/math/ce-vector.h"
#include "ceng/math/ce-matrix.h"
#include "ceng/math/ce-quaternion.h"

#endif