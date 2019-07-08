/**
 * \file test_date.cpp
 * \author David Thompson
 * \brief Unit tests the Date class
 * \date 2019-07-08
 */

#include "catch.hpp"

#include "Date.h"


namespace qttodo {

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


}
