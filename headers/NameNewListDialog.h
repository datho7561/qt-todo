/**
 * \file NameNewListDialog.h
 * \author David Thompson
 * \brief A dialog that prompts the user for the name of a new TaskList
 * \date 2019-08-06
 */

#ifndef NAME_NEW_LIST_DIALOG_H
#define NAME_NEW_LIST_DIALOG_H

#include <string>

#include "ui_NameNewListDialog.h"

namespace qttodo {

class NameNewListDialog : public QDialog, public Ui::NameNewListDialog {

	Q_OBJECT

private slots:

	void on_list_name_field_changed();

public:

	/**
	 * \brief Make a new NameNewList Dialog
	 */
	NameNewListDialog(QWidget * parent = nullptr);

	/**
	 * \brief Gets the task name that was selected
	 *
	 * \returns The selected name for the task
	 */
	std::string get_task_name() const {
		return list_name_field->text().toStdString();
	}
};

} // qttodo

#endif // NAME_NEW_LIST_DIALOG_H
