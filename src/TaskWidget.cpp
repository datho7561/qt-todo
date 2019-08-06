/**
 * \file TaskWidget.cpp
 * \author David Thompson
 * \brief Implementation of TaskWidget
 * \date 2019-07-31
 */

#include <QString>

#include "TaskWidget.h"

namespace qttodo {

TaskWidget::TaskWidget(Task * task, QWidget * parent):
    task(task),
    QCheckBox(parent) {

}

// TODO: Test this code
void TaskWidget::update_text() {
    QString new_text = "";
    if (task->is_complete()) {
        new_text += "<s>";
    }

    if (task->is_overdue()) {
        new_text += "<span style=\"font-color: red\">";
    }

    if (task->is_overdue()) {
        new_text += "</span>";
    }

    if (task->is_complete()) {
        new_text += "</s>";
    }
}

// SLOTS

void TaskWidget::on_clicked() {
    QString output_string;
}

} // qttodo
