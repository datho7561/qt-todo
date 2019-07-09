/**
 * \file test_date.cpp
 * \author David Thompson
 * \brief Unit tests the Date class
 * \date 2019-07-08
 */

#include <iostream>

#include "catch.hpp"

#include "Date.h"


namespace qttodo {


// TODO: do a case where the odd leap year rules play a factor
TEST_CASE("Only valid dates") {

    SECTION("Zero day invalid") {
        REQUIRE_THROWS_AS(Date(0, 1, 0), std::invalid_argument);
    }

    SECTION("Zero month invalid") {
        REQUIRE_THROWS_AS(Date(1, 0, 200), std::invalid_argument);
    }

    SECTION("Months past December invalid") {
        Date(1, 12, 2019);
        REQUIRE_THROWS_AS(Date(1, 13, 1970), std::invalid_argument);
    }

    SECTION("32 March invalid") {
        Date(31, 3, 2019);
        REQUIRE_THROWS_AS(Date(32, 3, 2019), std::invalid_argument);
    }

    SECTION("No 30th February") {
        REQUIRE_THROWS_AS(Date(30, 2, 1970), std::invalid_argument);
    }

    SECTION("No 29th February on non-leap year") {
        REQUIRE_THROWS_AS(Date(29, 2, 2019), std::invalid_argument);
    }

    SECTION("29 days in February on leap year") {
        Date(29, 2, 2012);
    }

}


TEST_CASE("Yesterday") {

    Date yesterday_generic_day = Date(20, 3, 2019).yesterday();
    Date yesterday_jan1 = Date(1, 1, 2019).yesterday();
    Date yesterday_mar1_leap = Date(1, 3, 2012).yesterday();
    Date yesterday_mar1_non_leap = Date(1, 3, 2013).yesterday();
    Date yesterday_begin_month = Date(1, 5, 1984).yesterday();

    SECTION("Yesterday on generic date") {
        REQUIRE(yesterday_generic_day.get_day() == 19);
        REQUIRE(yesterday_generic_day.get_month() == 3);
        REQUIRE(yesterday_generic_day.get_year() == 2019);
    }

    SECTION("Yesterday on month beginning") {
        REQUIRE(yesterday_begin_month.get_day() == 30);
        REQUIRE(yesterday_begin_month.get_month() == 4);
        REQUIRE(yesterday_begin_month.get_year() == 1984);
    }

    SECTION("Yesterday on Jan 1st") {
        REQUIRE(yesterday_jan1.get_day() == 31);
        REQUIRE(yesterday_jan1.get_month() == 12);
        REQUIRE(yesterday_jan1.get_year() == 2018);
    }

    SECTION("Yesterday on leap year") {
        REQUIRE(yesterday_mar1_leap.get_day() == 29);
        REQUIRE(yesterday_mar1_leap.get_month() == 2);
        REQUIRE(yesterday_mar1_leap.get_year() == 2012);
    }

    SECTION("Yesterday on non-leap year") {
        REQUIRE(yesterday_mar1_non_leap.get_day() == 28);
        REQUIRE(yesterday_mar1_non_leap.get_month() == 2);
        REQUIRE(yesterday_mar1_non_leap.get_year() == 2013);
    }

}


TEST_CASE("To String") {

    Date my_date = Date(9, 7, 2019);
    Date epoch = Date(1, 1, 1970);
    Date end_of_year = Date(31, 12, 2000);

    Date feb = Date(2, 2, 2077);
    Date mar = Date(2, 3, 2077);
    Date apr = Date(2, 4, 2077);
    Date may = Date(2, 5, 2077);
    Date jun = Date(2, 6, 2077);
    Date aug = Date(2, 8, 2077);
    Date sept = Date(2, 9, 2077);
    Date oct = Date(2, 10, 2077);
    Date nov = Date(2, 11, 2077);

    Date bce_0 = Date(1, 1, 0);
    Date bce_1 = Date(15, 4, -100);
    Date bce_2 = Date(20, 6, -2000);

    SECTION("General cases") {
        REQUIRE(my_date.to_string() == std::string("9 July, 2019"));
        REQUIRE(epoch.to_string() == std::string("1 January, 1970"));
        REQUIRE(end_of_year.to_string() == std::string("31 December, 2000"));
    }

    SECTION("Months") {
        REQUIRE(feb.to_string() == std::string("2 February, 2077"));
        REQUIRE(mar.to_string() == std::string("2 March, 2077"));
        REQUIRE(apr.to_string() == std::string("2 April, 2077"));
        REQUIRE(may.to_string() == std::string("2 May, 2077"));
        REQUIRE(jun.to_string() == std::string("2 June, 2077"));
        REQUIRE(aug.to_string() == std::string("2 August, 2077"));
        REQUIRE(sept.to_string() == std::string("2 September, 2077"));
        REQUIRE(oct.to_string() == std::string("2 October, 2077"));
        REQUIRE(nov.to_string() == std::string("2 November, 2077"));
    }

    SECTION("BCE") {
        REQUIRE(bce_0.to_string() == std::string("1 January, 0"));
        REQUIRE(bce_1.to_string() == std::string("15 April, 100 BCE"));
        REQUIRE(bce_2.to_string() == std::string("20 June, 2000 BCE"));
    }

}


TEST_CASE("Computer String") {

    Date my_date = Date(9, 7, 2019);
    Date epoch = Date(1, 1, 1970);
    Date end_of_year = Date(31, 12, 2000);

    Date feb = Date(2, 2, 2077);
    Date mar = Date(2, 3, 2077);
    Date apr = Date(2, 4, 2077);
    Date may = Date(2, 5, 2077);
    Date jun = Date(2, 6, 2077);
    Date aug = Date(2, 8, 2077);
    Date sept = Date(2, 9, 2077);
    Date oct = Date(2, 10, 2077);
    Date nov = Date(2, 11, 2077);

    Date bce_0 = Date(1, 1, 0);
    Date bce_1 = Date(15, 4, -100);
    Date bce_2 = Date(20, 6, -2000);

    REQUIRE(my_date == Date::from_string(my_date.to_computer_string()));
    REQUIRE(epoch == Date::from_string(epoch.to_computer_string()));
    REQUIRE(end_of_year == Date::from_string(end_of_year.to_computer_string()));
    REQUIRE(feb == Date::from_string(feb.to_computer_string()));
    REQUIRE(mar == Date::from_string(mar.to_computer_string()));
    REQUIRE(apr == Date::from_string(apr.to_computer_string()));
    REQUIRE(may == Date::from_string(may.to_computer_string()));
    REQUIRE(jun == Date::from_string(jun.to_computer_string()));
    REQUIRE(aug == Date::from_string(aug.to_computer_string()));
    REQUIRE(sept == Date::from_string(sept.to_computer_string()));
    REQUIRE(oct == Date::from_string(oct.to_computer_string()));
    REQUIRE(nov == Date::from_string(nov.to_computer_string()));
    REQUIRE(bce_0 == Date::from_string(bce_0.to_computer_string()));
    REQUIRE(bce_1 == Date::from_string(bce_1.to_computer_string()));
    REQUIRE(bce_2 == Date::from_string(bce_2.to_computer_string()));

}


// TODO: check comparison operators


}
