/**
 * \file ListWidget.cpp
 * \author David Thompson
 * \brief Implementation of the Widget that displays the list of Tasks
 * \date 2019-08-01
 */

#include <exception>
#include <iostream> // DEBUG
#include <QFile>

#include "ListWidget.h"
#include "TaskWidget.h"

namespace qttodo {

ListWidget::ListWidget(std::string list_path, Setting * setting,
    std::string list_name, QWidget * parent) :
    QWidget(parent),
    list_path(list_path),
    setting(setting) {
    
    QFile list_file(QString::fromStdString(list_path));

    // If the file exists, throw std::invalid_argument
    if (list_file.exists()) {
        throw std::invalid_argument("The file specified already exists, so it "
            "can't be used for a TaskList file");
    }

    // Make the TaskList object
    task_list.reset(new TaskList(list_name));

    // Write the TaskList object to file
    rewrite_task_list();

	setupUi(this);

    list_contents->setLayout(new QVBoxLayout);

}

ListWidget::ListWidget(std::string list_path, Setting * setting,
    QWidget * parent) :
    QWidget(parent),
    list_path(list_path),
    setting(setting) {

    QFile list_file(QString::fromStdString(list_path));

    if (!list_file.exists()) {
        throw std::invalid_argument("The TaskList file does not exist, so it "
            "can't be opened");
    }

    // Read it from file
    if (list_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString data = "";
        while (!list_file.atEnd()) {
            data += list_file.readLine();
        }
        try {
            task_list.reset(
                new TaskList(TaskList::from_string(data.toStdString())));
        } catch (std::invalid_argument e) {
            throw std::runtime_error("Cannot parse file as a TaskList");
        }
    } else {
        throw std::runtime_error("Cannot open file for reading");
    }

	setupUi(this);

    list_contents->setLayout(new QVBoxLayout);

	update_list_widget();
}

// SLOTS

void ListWidget::add_new_task(Task task) {

    task_list->add_new(task);
    update_list_widget();
    rewrite_task_list();
}

void ListWidget::update_list_widget() {


    QVBoxLayout * layout = dynamic_cast<QVBoxLayout *>(list_contents->layout());
	
    // Remove widgets
    while (layout->count() > 0) {
        QWidget * to_remove = layout->itemAt(0)->widget();
        layout->removeWidget(to_remove);
        delete to_remove;
    }

    // Remove outdated tasks
    task_list->remove_expired(setting->get_expiry_policy());

    // Add new widgets
    for (Task * task : *task_list) {
        TaskWidget * task_widget = new TaskWidget(task, list_contents);
        layout->addWidget(task_widget);
        // TODO: connect buttons to task_updated?
        connect(task_widget, SIGNAL(task_updated()),
            this, SLOT(rewrite_task_list()));
    }
    layout->addStretch(1);
}

void ListWidget::rewrite_task_list() {

    QFile list_file(QString::fromStdString(list_path));
    QDir list_dir(QFileInfo(list_file).absoluteDir());
    // Make the directory path if it doesn't exist
    if (!list_dir.exists()) {
        list_dir.mkpath(list_dir.absolutePath());
    }
    if (list_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        list_file.write(task_list->to_string().c_str());
    }
}

} // qttodo
