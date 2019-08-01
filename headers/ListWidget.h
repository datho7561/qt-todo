/**
 * \file ListWidget.h
 * \author David Thompson
 * \brief Describes the Widget that holds all the TaskWidgets for a particular
 * task
 * \date 2019-08-01
 */

#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include <memory>
#include <QWidget>

#include "TaskList.h"
#include "Setting.h"

namespace qttodo {

class ListWidget : public QWidget {

	Q_OBJECT

private:
	std::unique_ptr<TaskList> task_list;
	std::string list_path;
	Setting * setting;

private slots:
	void add_new_task(Task task);

	/**
	 * \brief Remakes
	 */
	void update_list_widget();

public:
	/**
	 * \brief Constructs a new ListWidget
	 * \detail A ListWidget is used to graphically display a TaskList
	 *
	 * \param list_path 
	 * \param setting
	 * \param parent The parent widget for this ListWidget
	 * \throws std::runtime_exception If the file exists but can't be opened
	 * for reading, or the file exists and its not of the correct format.
	 */
	ListWidget(std::string list_path, Setting* setting, QWidget * parent = nullptr);

};

} // qttodo

#endif // LIST_WIDGET_H
