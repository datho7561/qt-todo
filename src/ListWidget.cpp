/**
 * \file ListWidget.cpp
 * \author David Thompson
 * \brief Implementation of the Widget that displays the list of Tasks
 * \date 2019-08-01
 */

#include <exception>
#include <QFile>

#include "ListWidget.h"

namespace qttodo {

ListWidget::ListWidget(std::string list_path, Setting* setting,
	std::string list_name, QWidget * parent) :
	QWidget(parent),
	list_path(list_path),
	setting(setting) {

	// TODO: try to read the file
	QFile list_file(QString::fromStdString(list_path));

	if (list_file.exists()) {
		// Read it from file
		if (list_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QString data = "";
			while (!list_file.atEnd()) {
				data += list_file.readLine();
			}
			task_list.reset(new TaskList(TaskList::from_string(data.toStdString())));
		} else {
			throw std::runtime_error("Cannot open file for reading");
		}
	} else {
		// Make it and write it to file
		task_list.reset(new TaskList(list_name));
	}
}

// SLOTS

void ListWidget::add_new_task(Task task) {
	task_list->add_new(task);
	update_list_widget();
}

} // qttodo
