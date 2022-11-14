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

- [ ] Implement x64 version of WinProcThunk

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

------------------------------------------
Windows Layer

- [ ] Handle multiple displays, so that moving the window to different display doesn't crash the app
      NOTE: maybe test with laptop?

------------------------------------------
Logging

- [ ] Add log levels (RELEASE, DEBUG, VERBOSE, etc..)

- [ ] Add printf style function

------------------------------------------
Filesystem

- [ ] Integrate zip files so that they are seamlessly considered a folder