
#include "SettingsDialog.h"

namespace qttodo {

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent) {
    setupUi(this);

    // TODO: try to read the setting from file, otherwise create
    // default

    // Connect Ok/Cancel/RestoreDefault buttons
    connect(buttonBox->button(QDialogButtonBox::Ok),
        SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel),
        SIGNAL(clicked()), this, SLOT(reject()));
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults),
        SIGNAL(clicked()), this, SLOT(restore_defaults()));

}

// SLOTS

void SettingsDialog::on_completedItemsBox_currentIndexChanged() {
    // TODO: modify the internal setting
}

void SettingsDialog::on_defaultDeadlineBox_currentIndexChanged() {
    // TODO: modify internal setting
}

void SettingsDialog::on_themeBox_currentIndexChanged() {
    // TODO: modify internal setting
}

void SettingsDialog::restore_defaults() {
    setting = Setting();
    // TODO: adjust the UI to reclect changes to setting
}

} // qttodo
