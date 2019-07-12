# qt-todo

This is a project where I am learning the basics of Qt4 through building a
simple cross-platform TODO application

---

## BUILDING

This project was developed on Linux but should be able to be built on Mac and
Windows. All that's needed is a C++ development environment (c++ compiler,
make/nmake) and a development installation of Qt4.

Make sure that the compiler being used support C++11 or later, because features
from these standards are being used in the application.

#### Linux/Mac

`qmake`

`make`

Then, run with `./build/qt-todo`

#### Windows

I will put the instructions for building under Visual Studio up here once I
try it for myself.

---

## TESTS

#### RUNNING TESTS

In order to unit test the application, the testing framework 
[Catch2](https://github.com/catchorg/Catch2) was used. Currently, these steps
only work under Linux. This is because I am using `pkg-config` to link/include
dependencies in the test `Makefile`. In order to be able to run the test suite, 
follow these steps:

1. Download the latest release of `catch2.cpp` from
    [the Catch2 Github](https://github.com/catchorg/Catch2/releases)
2. Put the file into the `testing` folder
3. Run `make -f Maketest` in order to compile the test files
4. Run `./testing/test` in order to run the tests

#### ADDING TEST CASES

Please refer to the Catch2 documentation on how to use Catch2 to write tests.
I am using the convention of making an additional file for each class I am
testing, so please refer to the documentation on how to structure these files.
Here is the current process for testing a class that is not yet being tested:

1. Make a new file under the folder `testing` called        
    `test_myClass.cpp`, where MyClass is the class being tested.
2. Set this file to be compiled by adding the line
    `TEST_OBJ += testing/test_myClass.o` in the makefile under the line
    `TEST_OBJ = testing/test_main.o`
3. Remake the test application (`make -f Maketest`) and run the test
    application (`./testing/test`) in order to run the added tests
