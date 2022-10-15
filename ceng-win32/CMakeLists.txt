cmake_minimum_required (VERSION 3.8)

project ("ceng-win32")

set (SRC_DIR "src")

#[[
set( INCLUDES

		"inc/ceng-win32.h"

		"inc/cpu-x86.h"
		"inc/d3d9-adapter.h"
		"inc/d3d9-swap-chain.h"
		"inc/gl32-adapter.h"
		"inc/gl32-blend-state.h"
		"inc/gl32-buffer-bits.h"
		"inc/gl32-cubemap.h"
		"inc/gl32-depth-stencil-state.h"
		"inc/gl32-index-buffer.h"
		"inc/gl32-pixel-shader.h"
		"inc/gl32-sampler-state.h"
		"inc/gl32-shader-const.h"
		"inc/gl32-shader-program.h"
		"inc/gl32-target-slot.h"
		"inc/gl32-target-tex2d.h"
		"inc/gl32-texture-2d.h"
		"inc/gl32-texture-unit.h"
		"inc/gl32-uniform-empty.h"
		"inc/gl32-uniform-float.h"
		"inc/gl32-uniform-float2.h"
		"inc/gl32-uniform-float3.h"
		"inc/gl32-uniform-float4.h"
		"inc/gl32-uniform-mat4.h"
		"inc/gl32-uniform-sampler2d.h"
		"inc/gl32-vertex-buffer.h"
		"inc/gl32-vertex-shader.h"
		"inc/gl32-view-cubemap.h"
		"inc/gl32-view-tex2d.h"
		"inc/gl33-context.h"
		"inc/gl33-device.h"
		"inc/gl33-swap-chain.h"
		"inc/gl33-vertex-format.h"

		"inc/graphics-2d-d3d10.h"
		"inc/graphics-2d-d3d9.h"
		
		"inc/system-info.h"

		"inc/win32-cond-var.h"
		"inc/win32-crend-d3d10.h"
		"inc/win32-crend-d3d9.h"
		"inc/win32-crit-section.h"
		"inc/win32-d3d9.h"
		"inc/win32-dll.h"
		"inc/win32-keyboard.h"
		"inc/win32-mouse.h"
		"inc/win32-mutex.h"
		"inc/win32-opengl32.h"
		"inc/win32-thread.h"
		"inc/win32-window.h"
		"inc/winproc-thunk.h"

		"inc/win32-types.h"

   )
]]



set( SOURCES 
		"src/cpu-x86.cpp"
		"src/d3d9-adapter.cpp"
		"src/d3d9-swap-chain.cpp"
		"src/gl32-adapter.cpp"
		"src/gl32-blend-state.cpp"
		"src/gl32-buffer-bits.cpp"
		"src/gl32-cubemap.cpp"
		"src/gl32-depth-stencil-state.cpp"
		"src/gl32-index-buffer.cpp"
		"src/gl32-pixel-shader.cpp"
		"src/gl32-sampler-state.cpp"
		"src/gl32-shader-const.cpp"
		"src/gl32-shader-program.cpp"
		"src/gl32-target-slot.cpp"
		"src/gl32-target-tex2d.cpp"
		"src/gl32-texture-2d.cpp"
		"src/gl32-texture-unit.cpp"
		"src/gl32-uniform-empty.cpp"
		"src/gl32-uniform-float.cpp"
		"src/gl32-uniform-float2.cpp"
		"src/gl32-uniform-float3.cpp"
		"src/gl32-uniform-float4.cpp"
		"src/gl32-uniform-mat4.cpp"
		"src/gl32-uniform-sampler2d.cpp"
		"src/gl32-vertex-buffer.cpp"
		"src/gl32-vertex-shader.cpp"
		"src/gl32-view-cubemap.cpp"
		"src/gl32-view-tex2d.cpp"
		"src/gl33-context.cpp"
		"src/gl33-device.cpp"
		"src/gl33-swap-chain.cpp"
		"src/gl33-vertex-format.cpp"

		"src/graphics-2d-d3d10.cpp"
		"src/graphics-2d-d3d9.cpp"
		"src/graphics-system.cpp"

		"src/layer-win32.cpp"
		"src/path.cpp"

		"src/win32-cond-var.cpp"
		"src/win32-crend-d3d10.cpp"
		"src/win32-crend-d3d9.cpp"
		"src/win32-crit-section.cpp"
		"src/win32-d3d9.cpp"
		"src/win32-dll.cpp"
		"src/win32-keyboard.cpp"
		"src/win32-mouse.cpp"
		"src/win32-mutex.cpp"
		"src/win32-opengl32.cpp"
		"src/win32-thread.cpp"
		"src/win32-window.cpp"
		"src/winproc-thunk.cpp"
	)

add_library("ceng-win32" SHARED  ${INCLUDES} ${SOURCES})

target_include_directories("ceng-win32" 
							PRIVATE "inc"
							)

target_link_libraries("ceng-win32"

						"glew32.lib"
						"Dinput8.lib"
						"d3d9.lib"
						"d3d10.lib"
						"Dxguid.lib"
						"opengl32.lib"

					 )
