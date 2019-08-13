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

    // ACTIONS

    // Quit closes the application
    connect(quit_act, SIGNAL(triggered()),
        this, SLOT(close()));

    // About Qt
    connect(about_qt_act, SIGNAL(triggered()),
        this, SLOT(about_qt()));

    // Open list
    connect(open_act, SIGNAL(triggered()),
        this, SLOT(open_list()));

    // New List
    connect(new_act, SIGNAL(triggered()),
        this, SLOT(new_list()));

    // Connect the add task button to the currently open tabbed widget
    connect(add_task_widget,
        SIGNAL(task_created(Task)),
        dynamic_cast<ListWidget *>(tab_widget->currentWidget()),
        SLOT(add_new_task(Task)));

}

// SLOTS

void MainWindow::open_list() {

    // Get the list file using a dialog
    // TODO: Change the default open directory to the Documents/qt-todo
    // directory
    QString open_list_file_path = QFileDialog::getOpenFileName(
        this,
        tr("Open List"),
        QDir::homePath(),
        tr("qt-todo Lists (*.list)")
    );

    // If a file was selected
    if (open_list_file_path != QString()) {
        
        // Check if this list is already open, and if so, change to it
        for (int i = 0; i < tab_widget->count(); i++) {
            try {
                ListWidget * tab = dynamic_cast<ListWidget *>(
                    tab_widget->widget(i));
                if (tab->get_file_name() == open_list_file_path.toStdString()) {
                    tab_widget->setCurrentIndex(i);
                    return;
                }
            } catch (std::exception e) {
                // TODO: handle more elegantly?
                continue;
            }
        }

        ListWidget * new_tab;

        // Read the list file in and handle any exceptions appropriately
        try {
            new_tab = new ListWidget(
                open_list_file_path.toStdString(),
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
        if (new_tab != nullptr) {
            tab_widget->addTab(new_tab,
                QString::fromStdString(new_tab->get_widget_name()));
            tab_widget->setCurrentWidget(new_tab);
        }
    }
}

void MainWindow::new_list() {
    // TODO: Change the default open directory to the Documents/qt-todo
    // directory
    QString new_file_list = QFileDialog::getSaveFileName(
        this,
        tr("Create List"),
        QDir::homePath(),
        tr("qt-todo Lists (*.list)")
    );
    // If it already exists, there will be a warning from the selection dialog
    // If a name was selected
    if (new_file_list != QString()) {
        
        // Get the name for the new TaskList, abort if no name is selected
        NameNewListDialog name_dlg(this);
        if (name_dlg.exec()) {

            // Check if this list is already open, and if so, close it (because
            // we are going to overwrite it)
            for (int i = 0; i < tab_widget->count(); i++) {
                try {
                    ListWidget * tab = dynamic_cast<ListWidget *>(
                        tab_widget->widget(i));
                    if (tab->get_file_name() == new_file_list.toStdString()) {
                        tab->deleteLater();
                        break;
                    }
                } catch (std::exception e) {
                    // TODO: This means something other than a normal TaskList
                    // has been added as a tab, consider crashing/resolving somehow?
                    continue;
                }
            }

            if (QFile(new_file_list).exists()) {
                // TODO: add error message if file can't be deleted
                QFile(new_file_list).remove();
            }

            ListWidget * new_tab;

            // Read the list file in and handle any exceptions appropriately
            try {
                new_tab = new ListWidget(
                    new_file_list.toStdString(),
                    setting.get(),
                    name_dlg.get_list_name(),
                    tab_widget
                );
            } catch (std::invalid_argument ia) {
                QMessageBox err_msg_box(
                    QMessageBox::Warning,
                    tr("List Writing Error"),
                    tr("Unable to create the file: ")
                    + new_file_list
                    + tr(" . Please make sure you have permission to create or "
                    "modify it. The new list was not created, but an old file "
                    "may have been deleted."),
                    QMessageBox::Ok,
                    this
                );
                err_msg_box.exec();
                new_tab = nullptr;
            }

            // Add the tab if reading went well
            if (new_tab != nullptr) {
                tab_widget->addTab(new_tab,
                    QString::fromStdString(new_tab->get_widget_name()));
                tab_widget->setCurrentWidget(new_tab);
            }
        }
    }
}

void MainWindow::about_qt() {
    QMessageBox::aboutQt(this, this->windowTitle());
}

void MainWindow::on_settings_act_triggered() {
    SettingsDialog settings_dialog(setting.get(), this);
    settings_dialog.exec();
}

}
