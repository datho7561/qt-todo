/**
 * \file AddTaskWidget.cpp
 * \author David Thompson
 * \brief Implements functionality of the AddTaskWidget
 * \date 2019-07-31
 */

#include <iostream>
#include <string>

#include "AddTaskWidget.h"
#include "DateConversion.h"

namespace qttodo {

AddTaskWidget::AddTaskWidget(QWidget * parent):
    QWidget(parent) {

    setupUi(this);
    // TODO: use settings
    task_date_editor->setDate(to_qdate(Date()));
}

// SLOTS

void AddTaskWidget::on_add_button_clicked() {

    QDate selected_date = task_date_editor->date();

    Task task(
        task_name_field->text().toStdString(),
        to_qttodo_date(selected_date)
    );

    task_name_field->setText("");

    emit task_created(task);
}

} // qttodo
