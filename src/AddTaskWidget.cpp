/**
 * \file AddTaskWidget.cpp
 * \author David Thompson
 * \brief Implements functionality of the AddTaskWidget
 * \date 2019-07-31
 */

#include <iostream>
#include <string>

#include "AddTaskWidget.h"

namespace qttodo {

AddTaskWidget::AddTaskWidget(QWidget * parent):
    QWidget(parent) {

    setupUi(this);
}

// SLOTS

void AddTaskWidget::on_add_button_clicked() {
	// TODO: send signal up and process this information correctly
    std::cout << "Huzzah!" << task_name_field->text().toStdString() << "\n";
}

} // qttodo
