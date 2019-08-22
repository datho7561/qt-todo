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

    // TODO: this is a quick fix but something more robust would be better
    // Prevent angle brackets and ampersand to avoid Qt side effects
    // (i.e. creating html tags and adding shortcuts)
    QRegExp regExp("[^<>&]+");
    task_name_field->setValidator(new QRegExpValidator(regExp, this));

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
    task_date_editor->setDate(to_qdate(Date()));
    
    emit task_created(task);
}

void AddTaskWidget::on_task_name_field_textChanged() {

    add_button->setEnabled(task_name_field->hasAcceptableInput());
}

} // qttodo
