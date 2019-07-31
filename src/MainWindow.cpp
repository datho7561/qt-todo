/**
 * \file MainWindow.cpp
 * \brief Logic for the application and the main window of the application
 * \author David Thompson
 * \date 2019-07-31
 */

#include <QMessageBox>

#include "MainWindow.h"
#include "SettingsDialog.h"

namespace qttodo {

MainWindow::MainWindow():
    setting() {
    if (Setting::setting_file_exists()) {
        setting.reset(new Setting(Setting::read_setting_file()));
    } else {
        setting.reset(new Setting);
        std::unique_ptr<SettingsDialog> settings_dialog(
            new SettingsDialog(setting.get(), this));
        settings_dialog->exec();
    }

    // TODO: Read/create default list file

    setupUi(this);

    // TODO: Add a new tab, and then populate it with the widget that displays
    // the TaskList

    // Set up the actions

    // Quit closes the application
    connect(quit_act, SIGNAL(triggered()),
        this, SLOT(close()));

    // About Qt
    connect(about_qt_act, SIGNAL(triggered()),
        this, SLOT(about_qt()));

}

// SLOTS

void MainWindow::open_list() {
    // TODO: implement opening the list and adding it to a new tab
}

void MainWindow::new_list() {
    // TODO: Implement selecting a name and file name to store the list as, then
    // open it in a new tab
}

void MainWindow::about_qt() {
    QMessageBox::aboutQt(this, this->windowTitle());
}

}
