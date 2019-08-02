/**
 * \file SettingsDialog.cpp
 * \author David Thompson
 * \brief Adds functionality to the Settings Dialog
 * \date 2019-07-25
 */

#include <QMessageBox>

#include "SettingsDialog.h"

namespace qttodo {

SettingsDialog::SettingsDialog(Setting * setting, QWidget* parent) :
    QDialog(parent), current_setting(setting), selected_setting(*setting) {

    setupUi(this);

    // Disable the cancel button if the Settings file doesn't exist
    buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(
        Setting::setting_file_exists());

    // Populate with the passed setting object
    defaultDeadlineBox->setCurrentIndex(
        deadline_to_id(selected_setting.get_default_date_policy()));
    completedItemsBox->setCurrentIndex(
        expiry_to_id(selected_setting.get_expiry_policy()));
    themeBox->setCurrentIndex(
        colour_to_id(selected_setting.get_colour_scheme()));
    defaultListField->setText(
        QString::fromStdString(selected_setting.get_default_list_file()));

    // Ok button triggers save attempt
    connect(buttonBox->button(QDialogButtonBox::Ok),
        SIGNAL(clicked()), this, SLOT(save_setting()));
    // Successful save attempt triggers exit
    connect(this, SIGNAL(setting_saved()), this, SLOT(accept()));
    // Cancel button triggers exit
    connect(buttonBox->button(QDialogButtonBox::Cancel),
        SIGNAL(clicked()), this, SLOT(reject()));
    // RestoreDefaults button restores defaults
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults),
        SIGNAL(clicked()), this, SLOT(restore_defaults()));

}

// SLOTS

void SettingsDialog::on_defaultDeadlineBox_currentIndexChanged() {

    // TODO: build unit tests to assert that this order is kept after
    // recompiling UI. If it isn't it isn't a big deal, but the switch statement
    // will have to be modified to reflect this.
    // Index reference:
    // Today 0
    // Tomorrow 1
    // Not set 2

    DefaultDatePolicy new_policy = selected_setting.get_default_date_policy();
    switch (defaultDeadlineBox->currentIndex()) {
        case 0:
            new_policy = DefaultDatePolicy::SET_TODAY;
            break;
        case 1:
            new_policy = DefaultDatePolicy::SET_TOMORROW;
            break;
        case 2:
            new_policy = DefaultDatePolicy::DONT_SET;
            break;
    }
    selected_setting.set_default_date_policy(new_policy);
}

void SettingsDialog::on_completedItemsBox_currentIndexChanged() {
    
    // TODO: Unit test as above
    // Index reference:
    // At end of day 0
    // At end of next day 1
    // Never 2

    ExpiryPolicy new_ep = selected_setting.get_expiry_policy();
    switch (completedItemsBox->currentIndex()) {
        case 0:
            new_ep = ExpiryPolicy::KEEP_TODAY;
            break;
        case 1:
            new_ep = ExpiryPolicy::KEEP_YESTERDAY;
            break;
        case 2:
            new_ep = ExpiryPolicy::KEEP_ALL;
            break;
    }
    selected_setting.set_expiry_policy(new_ep);
}

void SettingsDialog::on_themeBox_currentIndexChanged() {

    // TODO: Unit test as above
    // Index Reference
    // Default 0
    // Monokai 1
    // Solarized 2
    // High Contrast 3

    ColourScheme new_scheme = selected_setting.get_colour_scheme();
    switch (themeBox->currentIndex()) {
        case 0:
            new_scheme = ColourScheme::DEFAULT;
            break;
        case 1:
            new_scheme = ColourScheme::MONOKAI;
            break;
        case 2:
            new_scheme = ColourScheme::SOLARIZED;
            break;
        case 3:
            new_scheme = ColourScheme::HIGH_CONTRAST;
    }
    selected_setting.set_colour_scheme(new_scheme);
}

void SettingsDialog::save_setting() {

    try {
        // Write settings to file first, so that if a failure occurs,
        // then no change will occur, and the user will be using the settings
        // that are still on the disk. This means that the settings won't
        // suddenly change when they restart the application
        selected_setting.write_to_file();
        // Change application setting so the user can start using it now
        current_setting->set_default_date_policy(
            selected_setting.get_default_date_policy());
        current_setting->set_expiry_policy(
            selected_setting.get_expiry_policy());
        current_setting->set_colour_scheme(
            selected_setting.get_colour_scheme());
        current_setting->set_default_list_file(
            selected_setting.get_default_list_file());
        emit setting_saved();
    } catch (std::runtime_error) {
        // Get confirmation to try again or not
	    int try_again = QMessageBox::warning(this, tr("Settings"),
            tr("Unable to write settings to disk.\n"
            "Make sure that you have permission to read and write to "
            "the file.\n"
            "Try writing them again?\n"
            "(Selecting no means the application won't keep the settings "
            "after it closes)."),
            QMessageBox::Yes | QMessageBox::No);
        if (try_again == QMessageBox::Yes) {
            save_setting();
        }
    }
}

void SettingsDialog::restore_defaults() {

    selected_setting = Setting();

    defaultDeadlineBox->setCurrentIndex(
        deadline_to_id(selected_setting.get_default_date_policy()));
    completedItemsBox->setCurrentIndex(expiry_to_id(
            selected_setting.get_expiry_policy()));
    themeBox->setCurrentIndex(colour_to_id(
        selected_setting.get_colour_scheme()));
    defaultListField->setText(
        QString::fromStdString(selected_setting.get_default_list_file()));
}

// private static methods

int SettingsDialog::expiry_to_id(ExpiryPolicy policy) {
    switch (policy) {
        case ExpiryPolicy::KEEP_ALL:
            return 2;
            break;
        case ExpiryPolicy::KEEP_TODAY:
            return 0;
            break;
        case ExpiryPolicy::KEEP_YESTERDAY:
            return 1;
            break;
        default:
            throw std::logic_error("Given ExpiryPolicy not yet supported");
    }
}

int SettingsDialog::deadline_to_id(DefaultDatePolicy deadline) {
    switch (deadline) {
        case DefaultDatePolicy::SET_TODAY:
            return 0;
            break;
        case DefaultDatePolicy::SET_TOMORROW:
            return 1;
            break;
        case DefaultDatePolicy::DONT_SET:
            return 2;
            break;
        default:
            throw std::logic_error("Given DefaultDatePolicy not yet supported");
    }
}

int SettingsDialog::colour_to_id(ColourScheme colour) {
    switch (colour) {
        case ColourScheme::DEFAULT:
            return 0;
            break;
        case ColourScheme::MONOKAI:
            return 1;
            break;
        case ColourScheme::SOLARIZED:
            return 2;
            break;
        case ColourScheme::HIGH_CONTRAST:
            return 3;
            break;
        default:
            throw std::logic_error("Given ColourScheme not yet supported");
    }
}

} // qttodo
