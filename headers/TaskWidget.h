/**
 * \file TaskWidget.h
 * \author David Thompson
 * \brief A widget designed to represent a TODO list Task
 * \date 2019-07-31
 */

#ifndef TASK_WIDHET_H
#define TASK_WIDGET_H

#include <QCheckBox>

#include "Task.h"

namespace qttodo {

class TaskWidget: public QCheckBox {

	Q_OBJECT

// TODO: Add a slot/method for updating text & text colour based off of expiry/
// completion status

private:
    Task * task;

private slots:

	/**
	 * \brief Update the text of the widget
	 * \detail Apply colouring and formatting to the name of the text
	 */
	void update_text();

	/**
	 * \brief Called when the checkbox is clicked
	 * \detail Sets the completed status of the Task, and updates the text
	 */
	void on_clicked();

public:
    TaskWidget(Task * task, QWidget * parent = nullptr);
};

} // qttodo

#endif
