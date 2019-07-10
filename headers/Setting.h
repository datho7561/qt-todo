/**
 * \file Setting.h
 * \author David Thompson
 * \brief Defines the Setting class, which represents the
 * configuration of the application
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

public:

    /**
     * \brief Construct a new Setting object given all the settings
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
     * \returns The DefaultDatePolicy indicating when items should be
     * due by default
     */
    DefaultDatePolicy get_default_date_policy() const {
        return default_date_policy;
    }

    /**
     * \brief Get the setting that tells how many days after completion
     * completed items should be removed from the list
     * \returns The ExpiryPolicy indicating when completed items should be
     * removed from the list
     */
    ExpiryPolicy get_expiry_policy() const {
        return expiry_policy;
    }

    /**
     * \brief Get the setting indicating which theme to use for the application
     * \returns The ColourScheme setting, which indicates which theme should be
     * used for the application
     */
    ColourScheme get_colour_scheme() const {
        return colour_scheme;
    }

    std::string get_default_list_file() const {
        return default_list_file;
    }

    /**
     * \brief Write this setting to the default setting file.
     * \detail This setting file is placed under ~/.config/qt-todo as a plain
     * text file that is computer readable. It is also placed in the
     * corresponding location under Windows
     * (i.e. C:\Users\<username>\.config\todo)
     * TODO: document the format so that it can be user changeable
     */
    void write_to_file() const;

};

} // qttodo

#endif // SETTING_H
