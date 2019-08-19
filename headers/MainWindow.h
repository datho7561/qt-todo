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
#include "TaskList.h"
#include "ui_MainWindow.h"

namespace qttodo {

class MainWindow: public QMainWindow, public Ui::MainWindow {

    Q_OBJECT

private:
    std::unique_ptr<Setting> setting;

private slots:

    /**
     * \brief Called when an existing list is to be opened
     * \detail Brings up a file selection dialog to select the list file, then
     * opens up a new tab with the list displayed
     */
    void open_list();

    /**
     * \brief Called when a new list is to be created
     * \detail Brings up a dialog to enter the name and list file location, then
     * opens up a new tab with the list displayed
     */
    void new_list();
    
    /**
     * \brief Open the About Qt Dialog
     */
    void about_qt();

    /**
     * \brief Called when the user requests to edit settings.
     * \detail Brings up the settings dialog, allowing the user to modify their
     * settings. This prevents interaction with the main window
     */
    void on_settings_act_triggered();

    /**
     * \brief Adds a the specified task to the list in the currently selected
     * tab
     * 
     * \param task The task to add to the list
     */
    void add_task_to_current_tab(Task task);

	/**
	 * \brief Close the tab with the specified index
	 *
	 * \param index The index of the tab to close
	 */
	void close_tab(int index) {
		tab_widget->removeTab(index);
	}

	/**
	 * \brief Close the tab that is currently open
	 */
	void close_current_tab() {
		tab_widget->removeTab(tab_widget->currentIndex());
	}

public:
    MainWindow();

};

}

#endif // MAIN_WINDOW_H
