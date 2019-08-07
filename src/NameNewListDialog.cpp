/**
 * \file NameNewListDialog.cpp
 * \author David Thompson
 * \brief Implementation for a dialog used for setting the name of a newly
 * created TaskList
 * \date 2019-08-06
 */

#include <QDialog>
#include <QPushButton>

#include "NameNewListDialog.h"

namespace qttodo {

NameNewListDialog::NameNewListDialog(QWidget * parent):
	QDialog(parent) {

	setupUi(this);

	if (parent != nullptr)
		setWindowTitle(parent->windowTitle());

	// TODO: make less restrictive
	QRegExp reg_exp("[A-Za-z0-9 _]+");
	list_name_field->setValidator(new QRegExpValidator(reg_exp, this));

	connect(button_box, SIGNAL(accepted()),
		this, SLOT(accept()));
	connect(button_box, SIGNAL(rejected()),
		this, SLOT(reject()));
}

// SLOTS

void NameNewListDialog::on_list_name_field_textChanged() {
	button_box->button(QDialogButtonBox::Ok)->setEnabled(list_name_field->hasAcceptableInput());
}

} // qttodo
