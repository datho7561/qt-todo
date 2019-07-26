/**
 * \file Setting.cpp
 * \author David Thompson
 * \brief implmentation of functions for the Setting class
 * \date 2019-07-05
 */

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
        if (QDir::home().mkpath(config_folder_str)){
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
    for (auto i = str_rep.begin(); i < str_rep.end(); i++) {
        // HACK: There should be a better way to convert than this
        char * convert = new char[2]{*i, '\0'};
        settings_file.write(convert);
        delete convert;
    }

    // Flush the buffer, file gets closed on stack frame exit
    settings_file.close();
}


Setting Setting::read_setting_file() {

    // TODO:

    Q_ASSERT(Setting::setting_file_exists());

    return Setting();

}


bool Setting::setting_file_exists()  {
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
