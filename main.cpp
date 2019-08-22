/**
 * \file main.cpp
 * \author David Thompson
 * \brief Sets up the application and calls the main window constructor
 * \date 2019-07-19
 */

#include <memory>

#include <QApplication>
#include <QDialog>

#include "MainWindow.h"

int main(int argc, char * argv[]) {

    QApplication app(argc, argv);
    std::unique_ptr<qttodo::MainWindow> main_window(new qttodo::MainWindow);
    main_window->show();
    return app.exec();
}