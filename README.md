# qt-todo

[![travis-ci](https://travis-ci.org/datho7561/qt-todo.svg?branch=master)](https://travis-ci.org/datho7561/qt-todo)
[![qt-todo](https://snapcraft.io/qt-todo/badge.svg)](https://snapcraft.io/qt-todo)

This is a project where I am learning the basics of Qt through building a
simple cross-platform Desktop TODO application.

---

## TABLE OF CONTENTS

* Building
* Tests
* Snapcraft
* VSCode Files

---

## BUILDING

This project was developed on Linux, but it should be able to be built on macOS
and Windows. All that's needed is a C++ development environment (c++ compiler,
make/nmake/msbuild) and a development installation of Qt4 or Qt5. Note that
either Qt4 or Qt5 should work, but this application was tested using Qt5 on
Linux and Qt4 on Windows.

Make sure that the compiler being used supports C++11 or later, because features
added in this standard are being used in the application.

#### Linux/Mac

1. `qmake` or `qmake-qt4` or `qmake-qt5`, depending on what version of Qt you
    want to compile under.

2. `make`

3. Run with `./build/qt-todo`

#### Windows

Qt4 is a hassle to set up now that it's no longer supported. I will update
these instructions when I have tested the application against Qt5.

These instructions are for Visual Studio. I have built it on Visual Studio 2019,
but it should work on any version newer than 2010 that includes a compiler that
supports C++11. I would have included instructions for how to build on
MinGW/Cygwin, but I have not had the time to attempt these methods.

1. In a developer command prompt where you have Qt4's bin files on the path,
    enter `qmake -tp vc` while in the `qt-todo` folder.

2. Open the generated .vcxproj with Visual Studio.

3. It should prompt to update the project to the latest version of Visual
    Studio. Accept this offer.

4. Build/run the project as normal. If you need to make changes to the
    qt-todo.pro or add/remove files, you will need to regenerate the Visual
    Studio project. (At least, I find regenerating the project is the easiest
    method, because this means no manual editing of the .vcxproj to get Visual
    Studio to run the correct preprocessing commands).

---

## TESTS

The testing framework [Catch2](https://github.com/catchorg/Catch2) is used to
unit test some of the list classes. Currently there is no automatic testing of
any GUI elements. [TravisCI](https://travis-ci.org/) is configured to run the
test suite automatically on each push to the master branch. So far, it only
tests under Linux.

#### RUNNING TESTS

__WARNING__: The checked in test suite creates the folders and file
`~/.config/qt-todo/setting`. If you have a file there currently
(such as settings for this or other programs), it will be overwritten
without warning.

To run the test suite, follow these steps:

##### LINUX

1. Download the latest release of `catch2.hpp` from
    [the Catch2 Github](https://github.com/catchorg/Catch2/releases)
2. Put the file into the `testing` folder
3. Run `qmake test=1` in order to set up the testing Makefile
4. Run `make` in order to build the testing program
5. Run `./testing/qt-todo` in order to run the tests

##### WINDOWS

1. Download the latest release of `catch2.hpp` from
    [the Catch2 Github](https://github.com/catchorg/Catch2/releases)
2. Put the file into the `testing` folder
3. Run `qmake -tp vc test=1` in order to create the test Visual Studio project
4. Open the project, then retarget it
5. Build the project
6. Run the generated .exe in a Command Prompt/Powershell/Windows Terminal in
    order to view the results of the tests.

#### ADDING TEST CASES

Please refer to the Catch2 documentation on how to use Catch2 to write tests.
I am using the convention of making an additional file for each class I am
testing, so please refer to the documentation on how to structure these files.
Here is the current process for testing a class that is not yet being tested:

1. Make a new file under the folder `testing` called `test_myClass.cpp`, where
    MyClass is the class being tested.
2. Follow the steps in the RUNNING TESTS section in order to run the added
    tests.

---

## SNAPCRAFT

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/qt-todo)

This application is available on the Snap Store. This will allow for an easier
installation across Linux distributions. The repository is set up to
automatically build and deploy Snaps when there is a push to the master branch.

If you are intending to add new features to qt-todo, then it may be necessary
to modify `snap/snapcraft.yaml`. This is because of the Snap sandboxing. You
will need to declare slots for every time you wish to access a restricted system
feature. Please refer to the
[Snapcraft Documentation](https://snapcraft.io/docs) for more information.

If you have added new slots, you should test to make sure that the snap build
works. You can build the snap on your computer if you have snapcraft installed by
running `snapcraft --debug` in the root of the project. It will take a
while to build, because it needs to make a Ubuntu VM in order to build the
snap. Once it is built, you can install it with
`sudo snap install (name).snap --dangerous` in order to test.

---

## VSCODE FILES

I have included VSCode build tasks for the program in order to help anyone else
who wants to build the application and happens to be using VSCode. They are
currently set up to use the default Qt make (`qmake`) and only work on Linux.
The tasks that are intended to be run directly are `build-app`, `build-test`,
and `build-snap`. I put them all under the 'Build' section of Tasks so that
they can be run with the `Ctrl+Shift+B` shortcut
