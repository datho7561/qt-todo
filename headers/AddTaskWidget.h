/**
 * \file AddTaskWidget.h
 * \author David Thompson
 * \brief A snippet of UI that allows for a new Task item to be described and
 * created
 * \date 2019-07-31
 */

#ifndef ADD_TASK_WIDGET_H
#define ADD_TASK_WIDGET_H

#include <QWidget>

#include "Task.h"
#include "ui_AddTaskWidget.h"

namespace qttodo {

class AddTaskWidget: public QWidget, public Ui::Form {

    Q_OBJECT

private slots:
    /**
     * \brief Process the clicking of the Add Task button
     * \detail Attempts to turn the current state of the widget into a Task,
     * then emits the task_created signal
     */
    void on_add_button_clicked();

signals:
    void task_created(Task task);

public:
    AddTaskWidget(QWidget * parent = nullptr);

};

} // qttodo

#endif // ADD_TASK_WIDGET_H
