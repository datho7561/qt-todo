
#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>

#include "Setting.h"

#include "ui_SettingsDialog.h"

namespace qttodo {

class SettingsDialog : public QDialog, public Ui::SettingsDialog {

	Q_OBJECT

private:
	Setting setting;

private slots:
	// For when combo box values are changed
	void on_defaultDeadlineBox_currentIndexChanged();
	void on_completedItemsBox_currentIndexChanged();
	void on_themeBox_currentIndexChanged();

	// For when the reset button is pressed
	void restore_defaults();

public:
	SettingsDialog(QWidget * parent = nullptr);

};

} //qttodo

#endif // SETTINGS_DIALOG_H
