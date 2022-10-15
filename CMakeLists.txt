# CMakeList.txt : CMake project for ceng-core, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ceng-core")

include_directories("deps/inc")
include_directories("inc")

link_directories("deps/lib/win32")

# Add source to this project's executable.

add_subdirectory("timerlib")
add_subdirectory("liblog")

add_subdirectory("ceng-win32")

# TODO: Add tests and install targets if needed.
