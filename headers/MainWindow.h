/**
 * \file MainWindow.h
 * \author David Thompson
 * \brief
 * \date 2019-07-31
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>
#include <QMainWindow>

#include "Setting.h"
#include "ui_MainWindow.h"

namespace qttodo {

class MainWindow: public QMainWindow, public Ui::MainWindow {

    Q_OBJECT

private:
    std::unique_ptr<Setting> setting;

public:
    MainWindow();

};

}

#endif // MAIN_WINDOW_H
