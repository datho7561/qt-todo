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
    QWidget(parent),
    task(task) {

    setupUi(this);
    
    connect(check_box, SIGNAL(released()),
        this, SLOT(on_clicked()));

    check_box->setChecked(task->is_complete());
    update_text();
}


void TaskWidget::update_text() {

    std::string new_text = "";
    if (task->is_complete()) {
        new_text += "<s><span style=\"color: gray\">";
    }
    // TODO: I don't think that the overdue works properly, make an example
    if (task->is_overdue()) {
        new_text += "<span style=\"color: red\">";
    }
    new_text += task->get_name();
    if (task->is_overdue()) {
        new_text += "</span>";
    }
    if (task->is_complete()) {
        new_text += "</span></s>";
    }
    task_label->setText(QString::fromStdString(new_text));
    this->repaint();
}

// SLOTS

void TaskWidget::on_clicked() {
    
    if (check_box->isChecked()) {
        task->set_complete();
        task->is_complete();
    } else {
        task->set_incomplete();
        !task->is_complete();
    }
    update_text();
    // emit task_updated();
}

} // qttodo
