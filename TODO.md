ceng-core

TODO
------------------------------------------

------------------------------------------
Project structure

- [ ] Rename solution to "ceng-core"

------------------------------------------
Bugs

- [ ] cube map creation crashes if mipLevels=0 and generate_mip_maps is not set.
      Shouldn't this just use the number of mip-map levels available in the file?

------------------------------------------
Features

- [ ] Gather data from shaders so that it's possible to tell if a uniform was optimized
      away, instead of returning UNIFORM_UNDEFINED error

------------------------------------------
Logging

- [ ] Add log levels (RELEASE, DEBUG, VERBOSE, etc..)

- [ ] Add printf style function

------------------------------------------
Filesystem

- [ ] Integrate zip files so that they are seamlessly considered a folder