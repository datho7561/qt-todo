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
#include <QTimer>
#include <iostream> // DEBUG

#include "Setting.h"
#include "TaskList.h"
#include "ui_MainWindow.h"

namespace qttodo {

class MainWindow: public QMainWindow, public Ui::MainWindow {

    Q_OBJECT

private:
    std::unique_ptr<Setting> setting;

    /**
     * \brief Used to signal the lists to refresh every hour
     */
    std::unique_ptr<QTimer> timer;

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
     * \brief Open the AboutQtTodoDialog
     */
    void about_qt_todo();

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

    /**
     * \brief Switch to the indicated tab
     */
    void switch_tab_1() {
        if (tab_widget->count() > 0) {
            tab_widget->setCurrentIndex(0);
        }
    }
    void switch_tab_2() {
        if (tab_widget->count() > 1) {
            tab_widget->setCurrentIndex(1);
        }
    }
    void switch_tab_3() {
        if (tab_widget->count() > 2) {
            tab_widget->setCurrentIndex(2);
        }
    }
    void switch_tab_4() {
        if (tab_widget->count() > 3) {
            tab_widget->setCurrentIndex(3);
        }
    }
    void switch_tab_5() {
        if (tab_widget->count() > 4) {
            tab_widget->setCurrentIndex(4);
        }
    }
    void switch_tab_6() {
        if (tab_widget->count() > 5) {
            tab_widget->setCurrentIndex(5);
        }
    }
    void switch_tab_7() {
        if (tab_widget->count() > 6) {
            tab_widget->setCurrentIndex(6);
        }
    }
    void switch_tab_8() {
        if (tab_widget->count() > 7) {
            tab_widget->setCurrentIndex(7);
        }
    }
    void switch_tab_9() {
        if (tab_widget->count() > 8) {
            tab_widget->setCurrentIndex(8);
        }
    }
    void switch_tab_10() {
        if (tab_widget->count() > 9) {
            tab_widget->setCurrentIndex(9);
        }
    }

public:
    MainWindow();

};

}

#endif // MAIN_WINDOW_H
