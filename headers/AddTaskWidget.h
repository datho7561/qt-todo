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

#include "ui_AddTaskWidget.h"

namespace qttodo {

class AddTaskWidget: public QWidget, public Ui::Form {

    Q_OBJECT

private slots:
    // TODO: This actually shouldn't be a slot here. The signal should be
    // connected to the main window.
    void on_add_button_clicked();

public:
    AddTaskWidget(QWidget * parent = nullptr);

};

} // qttodo

#endif // ADD_TASK_WIDGET_H
