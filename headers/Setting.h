/**
 * \file Setting.h
 * \author David Thompson
 * \brief Defines the Setting class, which represents the configuration of the
 * application
 * \date 2019-07-05
 */

#ifndef SETTING_H
#define SETTING_H

#include <string>

#include <QDir>
#include <QFile>

#include "DefaultDatePolicy.h"
#include "ExpiryPolicy.h"
#include "ColourScheme.h"

namespace qttodo {

class Setting {

private:

    DefaultDatePolicy default_date_policy;
    ExpiryPolicy expiry_policy;
    ColourScheme colour_scheme;
    std::string default_list_file;

    /**
     * \brief Make a string representation of this Setting
     * \detail
     * Each line is seperated by a linefeed '\n'
     * First line: default_date_policy converted into an unsigned integer based
     *  on the ordering in the hedaer definition starting at zero
     * Second line: expiry_policy converted into an unsigned integer based
     *  on the ordering in the header definition starting at zero
     * Third line: colour_scheme converted into an unsigned integer based
     *  on the ordering in the header definition starting at zero
     * Fourth line: The default_list_file
     * 
     * \returns A string representation of this Setting
     */
    std::string to_string() const;

public:

    /**
     * \brief Construct a new Setting object given all the settings
     * 
     * \param default_date_policy The policy for when new items should be due by default
     * \param expiry_policy The policy for when completed items will be removed from the list
     * \param colour_scheme The colour scheme to use for the UI
     * \param default_list_file The path to the default list file. This path is
     * formatted as a Unix path according to the Qt's method of storing paths
     */
    Setting(DefaultDatePolicy default_date_policy,
            ExpiryPolicy expiry_policy,
            ColourScheme colour_scheme,
            std::string default_list_file):
        default_date_policy(default_date_policy),
        expiry_policy(expiry_policy),
        colour_scheme(colour_scheme),
        default_list_file(default_list_file) {}

    /**
     * \brief Constructs a setting object with the default settings
     * 
     * \returns A Setting object with the default settings
     */
    Setting():
        default_date_policy(DefaultDatePolicy::SET_TOMORROW),
        expiry_policy(ExpiryPolicy::KEEP_YESTERDAY),
        colour_scheme(ColourScheme::DEFAULT),
        default_list_file(QDir::homePath()
            .append("/Documents/qt-todo/default.list")
            .toStdString()) {}

    /**
     * \brief Get the setting that tells which day items should be due by
     * default
     * 
     * \returns The DefaultDatePolicy indicating when items should be
     * due by default
     */
    DefaultDatePolicy get_default_date_policy() const {
        return default_date_policy;
    }

    /**
     * \brief Get the setting that tells how many days after completion
     * completed items should be removed from the list
     * 
     * \returns The ExpiryPolicy indicating when completed items should be
     * removed from the list
     */
    ExpiryPolicy get_expiry_policy() const {
        return expiry_policy;
    }

    /**
     * \brief Get the setting indicating which theme to use for the application
     * 
     * \returns The ColourScheme setting, which indicates which theme should be
     * used for the application
     */
    ColourScheme get_colour_scheme() const {
        return colour_scheme;
    }

    /**
     * \brief Gets the path to the default list file to be used, as a Unix-style
     * path
     * 
     * \returns The Unix-style path to the default list file
     */
    std::string get_default_list_file() const {
        return default_list_file;
    }

    void set_default_date_policy(DefaultDatePolicy new_default_date_policy) {
        default_date_policy = new_default_date_policy;
    }

    void set_expiry_policy(ExpiryPolicy new_expiry_policy) {
        expiry_policy = new_expiry_policy;
    }

    void set_colour_scheme(ColourScheme new_colour_scheme) {
        colour_scheme = new_colour_scheme;
    }

    void set_default_list_file(std::string new_default_list_file) {
        default_list_file = new_default_list_file;
    }

    /**
     * \brief Write this setting to the default setting file.
     * \detail This setting file is placed under ~/.config/qt-todo as a plain
     * text file that is computer readable. It is also placed in the
     * corresponding location under Windows
     * (i.e. C:\Users\<username>\.config\todo).
     * The format for the settings file is documented aboe in the declaration
     * of the private to_string() method
     * 
     * \exception std::runtime_error if in any way the file couldn't be written
     */
    void write_to_file() const;

    /**
     * \brief Makes a Setting object by reading the Setting file
     * \detail Please refer to the documentation for Setting::write_to_file()
     * and the private method Setting::to_string() for the location and format
     * of the setting file.
     * 
     * \throws std::runtime_error if the settings file does not exist or is not
     * able to be read as a settings file.
     * \returns A new Setting object representing the Setting in the file
     */
    static Setting read_setting_file();

    /**
     * \brief Checks if there is a Setting file
     * \detail This can be used to verify if the application has ever been
     * launched
     * 
     * \returns true if the Setting file exists, false otherwise
     */
    static bool setting_file_exists();

};

} // qttodo

#endif // SETTING_H
