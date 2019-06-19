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