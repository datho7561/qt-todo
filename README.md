# qt-todo

This is a project where I am learning the basics of Qt4 through building a
simple cross-platform TODO application.

---

## BUILDING

This project was developed on Linux but should be able to be built on Mac and
Windows. All that's needed is a C++ development environment (c++ compiler,
make/nmake) and a development installation of Qt4.

Make sure that the compiler being used supports C++11 or later, because features
from these standards are being used in the application.

#### Linux/Mac

1. `qmake`

2. `make`

3. Run with `./build/qt-todo`

#### Windows

Installing Qt4 on Windows i kind of difficult. I will most likely include
instructions on how to do this in the future.

These instructions are for Visual Studio. I have built on Visual Studio 2019, but
it should work on any version newer than 2010. I would have included instructions
for how to build on MinGW/Cygwin, but I have not had time to attempt these
methods.

1. In a developer command prompt where you have Qt4's bin files on the path,
   enter `qmake -tp vc` while in the `qt-todo` folder.

2. Open the generated .vcxproj with Visual Studio.

3. It should prompt to update the project to the latest version of Visual Studio.
   Accept this offer.

4. Build/run the project as normal. If you need to make changes to the qt-todo.pro
   or add/remove files, you will need to regenerate the Visual Studio project.
   (At least, I find regenerating the project is the easiest method, because this
   means no manually editing the .vcxproj to get Visual Studio to run the
   correct preprocessing commands).

---

## TESTS

#### RUNNING TESTS

__WARNING__: the checked in test suite created the folders and file
`~/.config/qt-todo/setting`. If you have a file there currently, it will be
overwritten.

In order to unit test the application, the testing framework 
[Catch2](https://github.com/catchorg/Catch2) was used. Currently, these steps
only work under Linux. In order to be able to run the test suite, follow these steps:

1. Download the latest release of `catch2.cpp` from
    [the Catch2 Github](https://github.com/catchorg/Catch2/releases)
2. Put the file into the `testing` folder
3. Run `qmake test=1` in order to set up the testing Makefile
4. Run `./testing/qt-todo` in order to run the tests

#### ADDING TEST CASES

Please refer to the Catch2 documentation on how to use Catch2 to write tests.
I am using the convention of making an additional file for each class I am
testing, so please refer to the documentation on how to structure these files.
Here is the current process for testing a class that is not yet being tested:

1. Make a new file under the folder `testing` called        
    `test_myClass.cpp`, where MyClass is the class being tested.
2. Follow the steps in the RUNNING TESTS section in order to run the added
    tests.

---

## VSCODE FILES

I have included VSCode build tasks for the program in order to help anyone else
who wants to build the application and happens to be using VSCode. They are
currently set up to compile with Qt5 instead of Qt4, and only work on Linux. The
tasks that are intended to be run directly are `build-app` and `build-test`. I
put them both under the 'Build' section of Tasks so that they can be run with
the `Ctrl+Shift+B` shortcut
