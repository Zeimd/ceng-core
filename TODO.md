ceng-core

TODO
------------------------------------------
Project structure

------------------------------------------
General

- [ ] Remove C++ use from library API. C++ classes and name mangling can't pass DLL boundary
      NOTE: So far it only works because Visual Studio has been used on both sides

- [ ] Make sure DLL side catches all exceptions

------------------------------------------
x64 target

- [ ] Make it possible to build for x64

- [ ] Check that winapi cpu info is still used correctly in x64 mode

- [X] Implement x64 version of WinProcThunk

- [ ] update string class to use size_t internally in all cases where length is used

------------------------------------------
String class

- [ ] Handle target dependency of size_t type properly instead of tossing int64/uint64 around unnecessarily.
            
            NOTE: Includes using size_t in stepping code too instead of signed types

------------------------------------------
Bugs

- [ ] cube map creation crashes if mipLevels=0 and generate_mip_maps is not set.
      Shouldn't this just use the number of mip-map levels available in the file?

------------------------------------------
Math

- [ ] Add euler angle initialization to MatrixF4 and Quaternion

------------------------------------------
Features

- [ ] Gather data from shaders so that it's possible to tell if a uniform was optimized
      away, instead of returning UNIFORM_UNDEFINED error

------------------------------------------
OpenGL wrapper

- [ ] Implement missing shader constant access types

- [ ] Handle multiple GPUs, so that OpenGL context is created on the correct one
      NOTE: maybe test with laptop?

- [ ] Relocate all generic OpenGL parts to different folder instead of having them in ceng-win32
      project

------------------------------------------
Platform Layer

- [ ] Handle multiple displays, so that moving the window to different display doesn't crash the app
      NOTE: maybe test with laptop?

- [ ] Add window menus

------------------------------------------
Logging

- [ ] Add log levels (RELEASE, DEBUG, VERBOSE, etc..)

- [ ] Add printf style function

------------------------------------------
Filesystem

- [ ] Integrate zip files so that they are seamlessly considered a folder

--------------------------------------------------
Software renderer

- [ ] CR_NewTargetData 

      Ensure that values of following fields can fit in int16_t:

            tileXstep, tileYstep, unitXstep, unitYstep can fit in int16_t

      Ensure that values of following fields can fit in uint32_t:

            bytesPerPixel

- [ ] Fix the way coverageAddress is used in pixel shader instance and ps output register, so that it's size and purpose is consistent

- [ ] Finish conversion of depth-stencil test to SIMD intrinsics

