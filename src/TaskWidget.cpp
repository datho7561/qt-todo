/**
 * \file TaskWidget.cpp
 * \author David Thompson
 * \brief Implementation of TaskWidget
 * \date 2019-07-31
 */

#include <iostream>
#include <string>
#include <QString>

#include "TaskWidget.h"

namespace qttodo {

TaskWidget::TaskWidget(Task * task, QWidget * parent):
    QCheckBox(parent),
    task(task) {
    
    connect(this, SIGNAL(released()),
        this, SLOT(on_clicked()));

    this->setChecked(task->is_complete());
    this->setText(QString::fromStdString(task->get_name()));
}

// TODO: Test this code
// void TaskWidget::update_text() {

//     std::string new_text = "";
//     if (task->is_complete()) {
//         new_text += "<s>";
//     }
//     if (task->is_overdue()) {
//         new_text += "<span style=\"font-color: red\">";
//     }
//     new_text += task->get_name();
//     if (task->is_overdue()) {
//         new_text += "</span>";
//     }
//     if (task->is_complete()) {
//         new_text += "</s>";
//     }
//     // DEBUG
//     std::cout << new_text << "\n";
//     // setText(new_text);
// }

// SLOTS

void TaskWidget::on_clicked() {

    if (task->is_complete()) {
        task->set_incomplete();
    } else {
        task->set_complete();
    }
    // update_text();
}

} // qttodo
