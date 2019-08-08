/**
 * \file MainWindow.cpp
 * \brief Logic for the application and the main window of the application
 * \author David Thompson
 * \date 2019-07-31
 */

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "ListWidget.h"
#include "NameNewListDialog.h"

namespace qttodo {

MainWindow::MainWindow():
    QMainWindow(),
    setting() {
    
    // Set settings if first time, read them otherwise
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

    setupUi(this);

    // Add the widget that displays the default TaskList
    QFile default_list_file(
        QString::fromStdString(setting->get_default_list_file()));

	
    // NOTE: The added tab is resource-managed by the tab_widget, so there
    // is no need to worry about it being leaked
    ListWidget * new_tab = nullptr;
    if (default_list_file.exists()) {
        // Call the `open` constructor for the new tab
        try {
        new_tab = new ListWidget(
            setting->get_default_list_file(),
            setting.get(),
            tab_widget
        );
        } catch(std::runtime_error re) {
            // DEBUG
            std::cout << "Incorrect format" << "\n";
            // TODO: Fix/detect leak?
            new_tab = nullptr;
        } catch (std::invalid_argument ia) {
            // DEBUG
            std::cout << "File cannot be opened" << "\n";
            // TODO: Fix/detect leak?
            new_tab = nullptr;
        }
    } else {
        // Call the `create` constructor for the new tab
        NameNewListDialog name_dlg(this);
        if (name_dlg.exec()) {
            new_tab = new ListWidget(
                setting->get_default_list_file(),
                setting.get(),
                name_dlg.get_list_name(),
                tab_widget
            );
        }
    }
    if (new_tab != nullptr) {
        tab_widget->addTab(new_tab,
            QString::fromStdString(new_tab->get_widget_name()));
    }
	


    // Set up the actions

    // Quit closes the application
    connect(quit_act, SIGNAL(triggered()),
        this, SLOT(close()));

    // About Qt
    connect(about_qt_act, SIGNAL(triggered()),
        this, SLOT(about_qt()));

    // Open list
    connect(open_act, SIGNAL(triggered()),
        this, SLOT(open_list()));

	// Connect the add task button to the

}

// SLOTS

void MainWindow::open_list() {
    // TODO: implement opening the list and adding it to a new tab
    // Get the list file using a dialog
    QString open_list_file_path = QFileDialog::getOpenFileName(
        this,
        tr("Open List"),
        QDir::homePath(),
        tr("qt-todo Lists (*.list)")
    );

    // If a file was selected
    if (open_list_file_path != QString()) {
        
        ListWidget * new_tab;

        // Read the list file in and handle any exceptions appropriately
        try {
            new_tab = new ListWidget(
                setting->get_default_list_file(),
                setting.get(),
                tab_widget
            );
        } catch (std::runtime_error re) {
            QMessageBox err_msg_box(
                QMessageBox::Warning,
                tr("List Reading Error"),
                tr("Unable to read the file as a list file. This may indicate "
                "that it has been corrupted or modified outside of qt-todo. "
                "The list opening has been cancelled."),
                QMessageBox::Ok,
                this
            );
            err_msg_box.exec();
            new_tab = nullptr;
        } catch (std::invalid_argument ia) {
            QMessageBox err_msg_box(
                QMessageBox::Warning,
                tr("List Reading Error"),
                tr("Unable to open the file for reading. Please make sure you "
                "have permission to read the file. The list opening has been "
                "cancelled."),
                QMessageBox::Ok,
                this
            );
            err_msg_box.exec();
            new_tab = nullptr;
        }

        // Add the tab if reading went well
        // TODO: Name of tab is not being processed correctly here
        // figure out why
        if (new_tab != nullptr) {
        tab_widget->addTab(new_tab,
            tr("Unadulterated potation"));
        }
    }
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
