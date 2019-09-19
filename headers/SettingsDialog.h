
#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <map>

#include <QDialog>

#include "Setting.h"

#include "ui_SettingsDialog.h"

namespace qttodo {

// TODO: Actually implement the select file button
class SettingsDialog : public QDialog, public Ui::SettingsDialog {

    Q_OBJECT

private:

    /**
     * \brief The current setting for the application
     * \detail The SettingDialog does not own this resource. It is given full
     * access to this resource in order to write to it when the selected
     * setting is saved.
     */
    Setting * current_setting;

    /**
     * \brief Internal representation of the current setting selected
     * \detail This is only held in this SettingsDialog until the setting is
     * saved.
     */
    Setting selected_setting;

    // HACK: This is sort of messy but I'm not sure how else to structure this

    static int expiry_to_id(ExpiryPolicy ep);
    static int deadline_to_id(DefaultDatePolicy deadline);
    static int colour_to_id(ColourScheme colour);

signals:
    
    /**
     * \brief Signals that the setting was saved successfully.
     * \detail Connected to the accept slot in order to close the dialog.
     */
    void setting_saved();

private slots:

    /** 
     * \brief Called when the combo box is changed.
     * \detail Modifies the SettingDialog's setting in order to reflect the new
     * default
     */
    void on_defaultDeadlineBox_currentIndexChanged(int);
    void on_completedItemsBox_currentIndexChanged(int);
    void on_themeBox_currentIndexChanged(int);
    
    /**
     * \brief called when the list input box is modified
     */
    void on_defaultListField_textChanged(const QString & text);

    /**
     * \brief Called when the select default list button is pressed
     */
    void on_selectFileButton_clicked(bool);

    /**
     * \brief Called when the Ok button is pressed
     * \detail Saves the setting to file, then changes the application's
     * current setting. Prompts the user to try again if writing to file fails.
     * It performs the default accept() action after the file is saved.
     */
    virtual void accept();

    /**
     * \brief Called when the restore defaults button is pressed.
     * \detail Restores the internal representation of the setting as well as
     * sets the GUI to that setting.
     */
    void restore_defaults();

public:

    /**
     * \brief Makes a SettingsDialog
     * 
     * \param setting A pointer to the application's global setting. This
     * setting will be modified if the Ok button is pressed in the dialog
     * \param parent The parent widget for this dialog.
     */
    SettingsDialog(Setting * setting, QWidget * parent = nullptr);

};

} //qttodo

#endif // SETTINGS_DIALOG_H
