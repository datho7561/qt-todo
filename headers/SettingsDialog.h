
#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <map>

#include <QDialog>

#include "Setting.h"

#include "ui_SettingsDialog.h"

namespace qttodo {

class SettingsDialog : public QDialog, public Ui::SettingsDialog {

    Q_OBJECT

private:
    // Maps from the IDs to the enums TODO: recosider architecture?
    // static const std::map<int, DefaultDatePolicy> DATE_POLICY_MAP;
    // static const std::map<int, ExpiryPolicy> EXPIRY_POLICY_MAP;
    // static const std::map<int, ColourScheme> COLOUR_SCHEME_MAP;

    // Internal representation of the current setting selected
    Setting setting;

private slots:

    /** 
     * \brief Called when the combo box is changed.
     * \detail Modifies the SettingDialog's setting in order to reflect the new
     * default
     */
    void on_defaultDeadlineBox_currentIndexChanged();
    void on_completedItemsBox_currentIndexChanged();
    void on_themeBox_currentIndexChanged();

    /**
     * \brief Called when the Ok button is pressed
     * \detail Saves the current setting to file
     */
    void save_setting();

    /**
     * \brief Called when the restore defaults button is pressed.
     * \detail Restores the internal representation of the setting as well as
     * sets the GUI to that setting.
     */
    void restore_defaults();

public:
    SettingsDialog(QWidget * parent = nullptr);

};

} //qttodo

#endif // SETTINGS_DIALOG_H
