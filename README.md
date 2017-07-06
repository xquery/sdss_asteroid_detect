# sdss_asteroid_detect 

IMPORTANT NOTE- this is unstable and under development.

[![Build Status](https://travis-ci.org/xquery/asteroid_detect.svg?branch=master)](https://travis-ci.org/xquery/asteroid_detect)

Small collection of utilities for processing sdss images.

## Usage

> naive_detect image-file-name

## Build and deploy

To build you may have to install some additional deps:
```
yum install epel-release
yum install cmake3
yum install curl-devel
```

To build this set of utilities on linux, osx and windows platforms.

```
>cmake3 -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"
```

Note that running cmake will pull down dependencies.

then run make, make install.

and to create a release package
```
>cpack3 --config CPackConfig.cmake
```

### Dependencies
This project uses the following libs:

* [rapidjson](https://github.com/miloyip/rapidjson): for json munging
* [loguru](https://github.com/emilk/loguru): for logging
* [gnuplot-cpp](https://github.com/orbitcowboy/gnuplot-cpp): for speaking to gnuplot
* [googletest](https://github.com/google/googletest): for testing

## License

[Apache License v2.0](LICENSE)

## Background
