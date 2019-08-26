/**
 * \file Setting.cpp
 * \author David Thompson
 * \brief implmentation of functions for the Setting class
 * \date 2019-07-05
 */

#include <QTextStream>

#include "Setting.h"

namespace qttodo {


std::string Setting::to_string() const {

    std::string str_rep = "";

    // DefaultDatePolicy
    switch (default_date_policy) {

        case DefaultDatePolicy::SET_TODAY:
            str_rep += "0";
            break;

        case DefaultDatePolicy::SET_TOMORROW:
            str_rep += "1";
            break;

        case DefaultDatePolicy::DONT_SET:
            str_rep += "2";
            break;
        
        default:
            throw std::invalid_argument("DefaultDatePolicy not recognized");
    }

    str_rep += "\n";

    // ExpiryPolicy
    switch (expiry_policy) {

        case ExpiryPolicy::KEEP_ALL:
            str_rep += "0";
            break;

        case ExpiryPolicy::KEEP_TODAY:
            str_rep += "1";
            break;

        case ExpiryPolicy::KEEP_YESTERDAY:
            str_rep += "2";
            break;
        
        default:
            throw std::invalid_argument("ExpiryPolicy not recognized");
    }

    str_rep += "\n";

    // ColourScheme
    switch (colour_scheme) {

        case ColourScheme::DEFAULT:
            str_rep += "0";
            break;

        case ColourScheme::MONOKAI:
            str_rep += "1";
            break;

        case ColourScheme::SOLARIZED:
            str_rep += "2";
            break;
        
        case ColourScheme::HIGH_CONTRAST:
            str_rep += "3";
            break;
        
        default:
            throw std::invalid_argument("ColourScheme not recognized");
    }

    str_rep += "\n";
    str_rep += default_list_file;
    str_rep += "\n";

    return str_rep;
}


void Setting::write_to_file() const {

    // Build string rep of file object
    std::string str_rep = to_string();

    const QString config_folder_str = ".config/qt-todo";
    QDir config_folder(QDir::homePath() + "/" + config_folder_str);
    if (!config_folder.exists()) {
        if (!config_folder.mkpath(".")){
            throw std::runtime_error("Unable to create config folder");
        }
    }
    QFile settings_file(
        QDir::homePath()
        + "/"
        + config_folder_str
        + "/"
        + "settings");

    // Write/Overwrite settings file
    if (!settings_file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Unable to open settings file for writting");
    }

    // Write the generated text to the file
    settings_file.write(str_rep.c_str());

    // Flush the buffer, file gets closed on stack frame exit
    settings_file.close();
}


Setting Setting::read_setting_file() {

    if (!Setting::setting_file_exists()) {
        throw std::runtime_error("Settings file does not exist. Please check "
            "that it exists before attempting to read it.");
    }

    int default_date_num;
    int expiry_policy_num;
    int colour_scheme_num;
    std::string default_list_file;

    QFile settings_file(QDir::homePath() + "/.config/qt-todo/settings");
    settings_file.open(QIODevice::ReadOnly);
    QTextStream in(&settings_file);

    in >> default_date_num;
    in >> expiry_policy_num;
    in >> colour_scheme_num;
    in.readLine();  // Finish reading line with last number on it
    default_list_file = in.readLine().toStdString();

    DefaultDatePolicy default_date_policy;
    ExpiryPolicy expiry_policy;
    ColourScheme colour_scheme;

    switch (default_date_num) {
        case 0:
            default_date_policy = DefaultDatePolicy::SET_TODAY;
            break;
        case 1:
            default_date_policy = DefaultDatePolicy::SET_TOMORROW;
            break;
        case 2:
            default_date_policy = DefaultDatePolicy::DONT_SET;
            break;
        default:
            throw std::runtime_error("Invalid settings file");
    }

    switch (expiry_policy_num) {
        case 0:
            expiry_policy = ExpiryPolicy::KEEP_ALL;
            break;
        case 1:
            expiry_policy = ExpiryPolicy::KEEP_TODAY;
            break;
        case 2:
            expiry_policy = ExpiryPolicy::KEEP_YESTERDAY;
            break;
        default:
            throw std::runtime_error("Invalid settings file");
    }

    switch (colour_scheme_num) {
        case 0:
            colour_scheme = ColourScheme::DEFAULT;
            break;
        case 1:
            colour_scheme = ColourScheme::MONOKAI;
            break;
        case 2:
            colour_scheme = ColourScheme::SOLARIZED;
            break;
        case 3:
            colour_scheme = ColourScheme::HIGH_CONTRAST;
            break;
        default:
            throw std::runtime_error("Invalid settings file");
    }

    return Setting(
        default_date_policy,
        expiry_policy,
        colour_scheme,
        default_list_file
    );

}


bool Setting::setting_file_exists() {

    const QString config_folder_str = ".config/qt-todo";
    QDir config_folder(QDir::homePath() + "/" + config_folder_str);
    if (!config_folder.exists()) {
        return false;
    }
    QFile settings_file(
        QDir::homePath()
        + "/"
        + config_folder_str
        + "/"
        + "settings");
    return settings_file.exists();
}


} // qttodo
