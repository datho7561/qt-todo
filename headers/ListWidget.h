/**
 * \file ListWidget.h
 * \author David Thompson
 * \brief Describes ListWidget, a QWidget that holds all the TaskWidgets
 * for a particular task. This is a graphical representation of a
 * TaskList
 * \date 2019-08-01
 */

#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include <memory>
#include <string>
#include <QWidget>

#include "TaskList.h"
#include "Setting.h"

namespace qttodo {

class ListWidget : public QWidget {

    Q_OBJECT

private:

    /**
     * \brief The TaskList that this ListWidget represents
     * \detail This ListWidget owns this TaskList
     */
    std::unique_ptr<TaskList> task_list;

    /**
     * \brief The filepath (styled as a Unix path) to the TaskList file
     */
    std::string list_path;

    /**
     * \brief A pointer to the application's current setting.
     * \detail This pointer is non-owning (the ListWidget does not own
     * this Setting object).
     */
    Setting * setting;

private slots:

    /**
	 * \brief Add a new Task to be displayed to this ListWidget
	 * \detail Adds it to the internal representation and adds it graphically
	 */
    void add_new_task(Task task);

    /**
     * \brief Redraws the widget's task list, adding new tasks and updating
     * existing ones.
     * TODO: implement
     */
    void update_list_widget();

    /**
     * \brief Write the TaskList to file
     * TODO: implement
     */
    void rewrite_task_list();

public:

    /**
     * \brief Makes a new ListWidget with a new TaskList
     * \detail This is the "create" constructor. It makes a new TaskList
     * and associated file at the specified location with the specifed name.
     * The assumption is that the given file doesn't yet exist, because this
     * ListWidget will create it.
     *
     * \param list_path The filepath of the list file to be created
     * \param setting A pointer to the application's current setting
     * \param list_name The name for the new TaskList
     * \param parent The parent widget for this ListWidget
     * \throws std::invalid_argument If the file exists already
     */
    ListWidget(std::string list_path, Setting * setting,
        std::string list_name, QWidget * parent = nullptr);

    /**
     * \brief Makes a new ListWidget given an existing TaskList file
     * \detail This is the "open" constructor. It reads the given TaskList file
     * and populates itself with the information. The function assumes that
     * the file exists and is in the correct format.
     *
     * \param list_path The filepath (stylized as a unix path) to the list file
     * to open
     * \param setting A pointer to the application's current setting
     * \param parent The parent Widget for this Widget
     * \throws std::invalid_argument If the file does not exist
     * \throws std::runtime_error If the file is not able to be read, or the
     * file is able to be read but not parsed as a TaskList file
     */
    ListWidget(std::string list_path, Setting * setting,
        QWidget * parent = nullptr);

    // TODO: Write a destructor? To force a write before closing?
    // consider how frequently you want to write

	/**
	 * \brief Gets the name of this widget
	 * \detail The name of this widget is the name of the list it is working with
	 * 
	 * \returns The name of this widget
	 */
	std::string get_widget_name() const {
		return task_list->get_name();
	}

};

} // qttodo

#endif // LIST_WIDGET_H
