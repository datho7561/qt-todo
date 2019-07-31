/**
 * \file MainWindow.cpp
 * \brief Logic for the application and the main window of the application
 * \author David Thompson
 * \date 2019-07-31
 */

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

    // Read/create default list file

    setupUi(this);

    // TODO: populate the central widget with the list file. Need to make a
    // widget class that does this

}

}
