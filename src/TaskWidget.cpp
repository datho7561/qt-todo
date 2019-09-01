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
    std::string new_date_text = "";

    if (task->is_complete()) {
        new_text += "<s><span style=\"color: gray\">";
        new_date_text += "<s><span style=\"color: gray\">";
    }
    if (task->is_overdue()) {
        new_text += "<span style=\"color: red\">";
        new_date_text += "<span style=\"color: red\">";
    }
    
    new_text += task->get_name();

    if (task->get_deadline() == Date()) {
        new_date_text += tr("Today").toStdString();
    } else if (task->get_deadline() == Date().yesterday()) {
        new_date_text += tr("Yesterday").toStdString();
    } else if (task->get_deadline().yesterday() == Date()) {
        new_date_text += tr("Tomorrow").toStdString();
    } else {
        new_date_text += task->get_deadline().to_string();
    }

    if (task->is_overdue()) {
        new_text += "</span>";
        new_date_text += "</span>";
    }
    if (task->is_complete()) {
        new_text += "</span></s>";
        new_date_text += "</span></s>";
    }
    task_label->setText(QString::fromStdString(new_text));
    date_label->setText(QString::fromStdString(new_date_text));
    this->repaint();
}

// SLOTS

void TaskWidget::on_clicked() {
    
    if (check_box->isChecked()) {
        task->set_complete();
    } else {
        task->set_incomplete();
    }
    update_text();
    emit task_updated();
}

} // qttodo

