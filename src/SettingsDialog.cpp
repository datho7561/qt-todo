/**
 * \file SettingsDialog.cpp
 * \author David Thompson
 * \brief Adds functionality to the Settings Dialog
 * \date 2019-07-25
 */

#include <iostream>

#include "SettingsDialog.h"

namespace qttodo {

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent) {
    setupUi(this);

    // TODO: try to read the setting from file, otherwise create
    // default

    // Populate

    // Connect Ok/Cancel/RestoreDefault buttons
    connect(buttonBox->button(QDialogButtonBox::Ok),
        SIGNAL(clicked()), this, SLOT(save_setting()));
    connect(buttonBox->button(QDialogButtonBox::Ok),
        SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox->button(QDialogButtonBox::Cancel),
        SIGNAL(clicked()), this, SLOT(reject()));
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

    DefaultDatePolicy new_policy = setting.get_default_date_policy();
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
    setting = Setting(
        new_policy,
        setting.get_expiry_policy(),
        setting.get_colour_scheme(),
        setting.get_default_list_file());
}

void SettingsDialog::on_completedItemsBox_currentIndexChanged() {
    
    // TODO: Unit test as above
    // Index reference:
    // At end of day 0
    // At end of next day 1
    // Never 2

    ExpiryPolicy new_ep = setting.get_expiry_policy();
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
    setting = Setting(
        setting.get_default_date_policy(),
        new_ep,
        setting.get_colour_scheme(),
        setting.get_default_list_file());
}

void SettingsDialog::on_themeBox_currentIndexChanged() {

    // TODO: Unit test as above
    // Index Reference
    // Default 0
    // Monokai 1
    // Solarized 2
    // High Contrast 3

    ColourScheme new_scheme = setting.get_colour_scheme();
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
    setting = Setting(
        setting.get_default_date_policy(),
        setting.get_expiry_policy(),
        new_scheme,
        setting.get_default_list_file());
}

void SettingsDialog::save_setting() {
    
    // TODO: implement
}

void SettingsDialog::restore_defaults() {

    setting = Setting();

    // By design, the default settings should be first.
    // TODO: figure out a way to unit test this?
    defaultDeadlineBox->setCurrentIndex(0);
    completedItemsBox->setCurrentIndex(0);
    themeBox->setCurrentIndex(0);
    defaultListField->setText(
        QString::fromStdString(setting.get_default_list_file()));
}

} // qttodo
