/**
 * \file test_setting.cpp
 * \author David Thompson
 * \brief Tests the Setting class
 * \date 2019-07-10
 */


#include "catch.hpp"

#include "Setting.h"


namespace qttodo {


TEST_CASE("Constructor/accessor test") {

    Setting default_setting;
    Setting custom_setting(
        DefaultDatePolicy::DONT_SET,
        ExpiryPolicy::KEEP_ALL,
        ColourScheme::MONOKAI,
        "/home/david/potate");

    REQUIRE(default_setting.get_default_date_policy()
        == DefaultDatePolicy::SET_TOMORROW);
    REQUIRE(default_setting.get_colour_scheme() == ColourScheme::DEFAULT);
    REQUIRE(default_setting.get_expiry_policy()
        == ExpiryPolicy::KEEP_YESTERDAY);
    REQUIRE(default_setting.get_default_list_file()
        == std::string("/home/david/Documents/qt-todo/default.list"));

}


// TODO: write some tests after I have implemented it
TEST_CASE("Writing/Reading from file") {

}


} //qttodo
