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

// TODO: Add a slot/method for updating text & text colour based off of expiry/
// completion status

private:
    Task * task;

public:
    TaskWidget(Task * task, QWidget * parent = nullptr);
};

} // qttodo

#endif
