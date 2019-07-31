/**
 * \file TaskWidget.cpp
 * \author David Thompson
 * \brief Implementation of TaskWidget
 * \date 2019-07-31
 */

#include QString

#include "TaskWidget.h"

namespace qttodo {

TaskWidget::TaskWidget(Task * task, QWidget * parent = nullptr):
    task(task),
    QCheckBox(parent) {
}

} // qttodo
