# qt-todo

This is a project where I am learning the basics of Qt4 through building a
simple cross-platform TODO application

## BUILDING

This project was developed on Linux but should be able to be built on Mac and
Windows. All that's needed is a C++ development environment (c++ compiler,
make/nmake) and a development installation of Qt4.

Here are the commands to build the application under Linux:

`qmake`

`make`

On older versions of GCC, it may be necessary to specify `-std=c++11` in the
CXX compiler options in the generated Makefile. Put this in the Makefile
after running `qmake`.

## RUNNING TESTS

In order to unit test the application, the testing framework 
[Catch2](https://github.com/catchorg/Catch2) was used. Currently, these steps
only work under Linux. In order to be able to run the test suite, follow these
steps:
1. Download the latest release of `catch2.cpp` from [the Catch2 Github](https://github.com/catchorg/Catch2/releases)
2. Put the file into the `testing` folder
3. Run `make -f Maketest` in order to compile the test files
4. Run `./testing/test` in order to run the tests
