/**
 * \file MainWindow.cpp
 * \brief Logic for the application and the main window of the application
 * \author David Thompson
 * \date 2019-07-31
 */

#include <QMessageBox>

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "ListWidget.h"

namespace qttodo {

MainWindow::MainWindow():
    setting() {
    if (Setting::setting_file_exists()) {
        setting.reset(new Setting(Setting::read_setting_file()));
    } else {
        setting.reset(new Setting);
        QMessageBox welcome_dialog(
            QMessageBox::Information,
            windowTitle(),
            tr("Welcome to qt-todo! Before you begin using the application, "
            "we need you to set your settings."),
            QMessageBox::Ok);
        welcome_dialog.exec();
        std::unique_ptr<SettingsDialog> settings_dialog(
            new SettingsDialog(setting.get(), this));
        settings_dialog->exec();
    }

    // TODO: Read/create default list file

    setupUi(this);

    QFile default_list_file(
        QString::fromStdString(setting->get_default_list_file()));

	try {
		// NOTE: The added tab is resource-managed by the tab_widget, so there
		// is no need to worry about it being leaked
		ListWidget * new_tab = nullptr;
		if (default_list_file.exists()) {
			// Call the `open` constructor for the new tab
			new_tab = new ListWidget(
				setting->get_default_list_file(),
				setting.get(),
				tab_widget
			);
		} else {
			// Call the `create` constructor for the new tab
			
			new_tab = new ListWidget(
				setting->get_default_list_file(),
				setting.get(),
				tab_widget
			);
		}
		if (new_tab != nullptr) {
			tab_widget->addTab(new_tab,
				QString::fromStdString(new_tab->get_widget_name()));
		}
	} catch (std::exception e) {
		// TODO: what to do if this fails?
	}

    // TODO: Add a new tab, and then populate it with the widget that displays
    // the TaskList

    // Set up the actions

    // Quit closes the application
    connect(quit_act, SIGNAL(triggered()),
        this, SLOT(close()));

    // About Qt
    connect(about_qt_act, SIGNAL(triggered()),
        this, SLOT(about_qt()));

	// Connect the add task button to the

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

void MainWindow::on_settings_act_triggered() {
    SettingsDialog settings_dialog(setting.get(), this);
    settings_dialog.exec();
}

}
