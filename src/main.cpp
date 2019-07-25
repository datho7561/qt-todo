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

#include "SettingsDialog.h"

// TODO: Move this logic into a QApplication instance
int main(int argc, char * argv[]) {

    QApplication app(argc, argv);

	std::unique_ptr<qttodo::SettingsDialog> settings_dialog(new qttodo::SettingsDialog);

    settings_dialog->show();

    return app.exec();

}