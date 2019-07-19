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

#include "Setting.h"

#include "ui_SettingsDialog.h"

// TODO: Move this all into a subclass of QApplication?
// Or, into another class that I create?
int main(int argc, char * argv[]) {

    QApplication app(argc, argv);

    // Manage lifetime of the setting object, pass it down to the classes that
    // need it
    std::unique_ptr<qttodo::Setting> setting;

    // if (qttodo::Setting::setting_file_exists()) {
    //     // Display welcome dialog
    //     // Create default Setting
    //     // Open settings dialog with default Setting
    //     setting.reset(new qttodo::Setting);
        Ui::SettingsDialog ui;
        std::unique_ptr<QDialog> dialog(new QDialog);
        ui.setupUi(dialog.get());

        dialog->show();
    // } else {
    //     // Load settings from file
    //     // FIXME: inefficient because the copy constructor is called a few times
    //     setting.reset(
    //         new qttodo::Setting(qttodo::Setting::read_setting_file()));
    // }


    return app.exec();

}