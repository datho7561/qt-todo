/**
 * \file main.cpp
 * \author David Thompson
 * \brief This file handles the top-level application flow, such as setting up
 * windows.
 * \detail As of yet it really doesn't do anything except open the settings
 * dialog
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