/**
 * \file ListWidget.cpp
 * \author David Thompson
 * \brief Implementation of the Widget that displays the list of Tasks
 * \date 2019-08-01
 */

#include <exception>
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

	update_list_widget();
}

// SLOTS

void ListWidget::add_new_task(Task task) {

    task_list->add_new(task);
    update_list_widget();
    rewrite_task_list();
}

void ListWidget::update_list_widget() {

	// Delete all the task widgets
	QObjectList list_children = list_contents->children();
	for (QObject * child : list_children) {
		child->deleteLater();
	}

    // Make a new layout TODO: Move into each constructor instead?
    // Need to find out if layout counts as a child
    QVBoxLayout * layout = new QVBoxLayout();

    task_list->remove_expired(setting->get_expiry_policy());

	// TODO: Make new ones
    for (Task * task : *task_list) {
        TaskWidget * task_widget = new TaskWidget(task, list_contents);
        layout->addWidget(task_widget);
        connect(task_widget, SIGNAL(task_updated()),
            this, SLOT(rewrite_task_list()));
    }
    layout->addStretch(1);

    list_contents->setLayout(layout);
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
