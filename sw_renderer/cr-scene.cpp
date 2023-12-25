/*****************************************************************************
*
* cr-scene.cpp
*
* By Jari Korkala 6/2012
*
* Concept Renderer's scene methods.
*
*****************************************************************************/

#include <ceng/platform.h>

#include <ceng/datatypes/condition-variable.h>
#include <ceng/datatypes/critical-section.h>

#include "crender.h"
#include "crender-context.h"

#include "rasterizer-cr.h"
#include "clipper.h"

#include "cr-vertex-shader.h"

#include "api-command.h"

#include "task-clipper.h"

#include "draw-batch.h"

using namespace Ceng;

/*
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3
*/

