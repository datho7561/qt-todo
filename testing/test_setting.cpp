/**
 * \file test_setting.cpp
 * \author David Thompson
 * \brief Tests the Setting class
 * \date 2019-07-10
 */


#include "catch.hpp"

#include "Setting.h"


namespace qttodo {


TEST_CASE("Setting") {

    Setting default_setting;
    Setting custom_setting(
        DefaultDatePolicy::DONT_SET,
        ExpiryPolicy::KEEP_ALL,
        ColourScheme::MONOKAI,
        "/home/david/potate");

    SECTION("Constructor/accessor test") {

        REQUIRE(default_setting.get_default_date_policy()
            == DefaultDatePolicy::SET_TOMORROW);
        REQUIRE(default_setting.get_colour_scheme() == ColourScheme::DEFAULT);
        REQUIRE(default_setting.get_expiry_policy()
            == ExpiryPolicy::KEEP_YESTERDAY);
        REQUIRE(default_setting.get_default_list_file()
            == std::string("/home/david/Documents/qt-todo/default.list"));

    }

    SECTION("Writing/Reading from file") {

        // TODO: More thorough tests, maybe test reading invalid files for
        // the expected exception

        default_setting.write_to_file();
        Setting current = Setting::read_setting_file();
        REQUIRE(default_setting.get_default_date_policy()
            == current.get_default_date_policy());
        REQUIRE(default_setting.get_expiry_policy()
            == current.get_expiry_policy());
        REQUIRE(default_setting.get_colour_scheme()
            == current.get_colour_scheme());
        REQUIRE(default_setting.get_default_list_file()
            == current.get_default_list_file());

        custom_setting.write_to_file();
        current = Setting::read_setting_file();
        REQUIRE(custom_setting.get_default_date_policy()
            == current.get_default_date_policy());
        REQUIRE(custom_setting.get_expiry_policy()
            == current.get_expiry_policy());
        REQUIRE(custom_setting.get_colour_scheme()
            == current.get_colour_scheme());
        REQUIRE(custom_setting.get_default_list_file()
            == current.get_default_list_file());
    }

}


} //qttodo
