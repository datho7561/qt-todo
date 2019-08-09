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
#include "ui_TaskWidget.h"

namespace qttodo {

// TODO: Work into a custom widget so I can style the text properly
class TaskWidget: public QWidget, public Ui::TaskWidget {

    Q_OBJECT

private:
    Task * task;

signals:

    /**
     * \brief Send signal that this TaskWidget has been updated
     * \detail This can be interpreted to figure out if the list needs to be
     * rewritten.
     */
    void task_updated();

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
