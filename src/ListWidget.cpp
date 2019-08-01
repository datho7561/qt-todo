/**
 * \file ListWidget.cpp
 * \author David Thompson
 * \brief Implementation of the Widget that displays the list of Tasks
 * \date 2019-08-01
 */

#include <QFile>

#include "ListWidget.h"

namespace qttodo {

ListWidget::ListWidget(std::string list_path, Setting* setting, QWidget * parent) :
	list_path(list_path),
	setting(setting),
	QWidget(parent) {
	// TODO: try to read the file
	QFile list_file(QString(list_path));
	if (list_file.exists()) {
		// Read it

	} else {
		// Write to it

	}
}

// SLOTS

void ListWidget::add_new_task(Task task) {
	task_list->add_new(task);
	update_list_widget();
}

} // qttodo
