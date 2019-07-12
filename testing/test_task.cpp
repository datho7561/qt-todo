/**
 * \file test_task.cpp
 * \author David Thompson
 * \brief Unit test the Task class
 * \date 2019-07-10
 */

#include "catch.hpp"

#include "Task.h"


namespace qttodo {


TEST_CASE("Task") {

    Task past_its_prime("Make salad", Date(1, 1, 1970));
    Task yesterdays_task("Test Date Class", Date().yesterday());
    Task todays_task("Finish Date Tests", Date());
    Task far_future("", Date(1, 1, 0xFFFFFFF));
    Task extrordinary(".", Date(31, 12, 0xFFFFFFF));
    Task identical1("Identical", Date(27, 2, 2008));
    Task identical2("Identical", Date(27, 2, 2008));

    Task complete_yesterday(
        "Complete yesterday",
        true,
        Date(1, 1, 1970),
        Date().yesterday()
    );

    Task complete_2_ago(
        "Complete 2 days ago",
        true,
        Date(1, 1, 1970),
        Date().yesterday().yesterday()
    );

    SECTION("Overdue") {

        REQUIRE(past_its_prime.is_overdue());
        REQUIRE(yesterdays_task.is_overdue());
        REQUIRE(!todays_task.is_overdue());
        REQUIRE(!far_future.is_overdue());

    }

    SECTION("Expiry") {

        REQUIRE(complete_yesterday.is_expired(ExpiryPolicy::KEEP_TODAY));
        REQUIRE(!complete_yesterday.is_expired(ExpiryPolicy::KEEP_YESTERDAY));
        REQUIRE(!complete_yesterday.is_expired(ExpiryPolicy::KEEP_ALL));

        REQUIRE(complete_2_ago.is_expired(ExpiryPolicy::KEEP_TODAY));
        REQUIRE(complete_2_ago.is_expired(ExpiryPolicy::KEEP_YESTERDAY));
        REQUIRE(!complete_2_ago.is_expired(ExpiryPolicy::KEEP_ALL));

        todays_task.set_complete();

        REQUIRE(!todays_task.is_expired(ExpiryPolicy::KEEP_TODAY));
        REQUIRE(!todays_task.is_expired(ExpiryPolicy::KEEP_YESTERDAY));
        REQUIRE(!todays_task.is_expired(ExpiryPolicy::KEEP_ALL));

    }

    SECTION("Ordering") {

        REQUIRE(complete_yesterday < past_its_prime);
        REQUIRE(complete_yesterday < yesterdays_task);
        REQUIRE(complete_yesterday < todays_task);
        REQUIRE(complete_yesterday < far_future);
        REQUIRE(complete_yesterday < extrordinary);

        // 2 is less in lexicographical ordering than y, so it should be first
        REQUIRE(complete_2_ago < complete_yesterday);

        // Check lexicographical ordering of incomplete tasks
        REQUIRE(extrordinary < todays_task);
        REQUIRE(extrordinary < yesterdays_task);
        REQUIRE(extrordinary < past_its_prime);
        REQUIRE(todays_task < past_its_prime);
        REQUIRE(todays_task < yesterdays_task);
        REQUIRE(past_its_prime < yesterdays_task);
        REQUIRE(far_future < extrordinary);

        // Equivalence checks
        REQUIRE(identical1 == identical2);
        REQUIRE(identical1 <= identical2);
        REQUIRE(identical2 <= identical1);
        REQUIRE(identical1 >= identical2);
        REQUIRE(identical2 >= identical1);
        REQUIRE(!(identical1 < identical2));

    }

    SECTION("Serializing") {
        
        REQUIRE(past_its_prime
            == Task::from_string(past_its_prime.to_string()));
        REQUIRE(yesterdays_task
            == Task::from_string(yesterdays_task.to_string()));
        REQUIRE(todays_task
            == Task::from_string(todays_task.to_string()));
        REQUIRE(far_future
            == Task::from_string(far_future.to_string()));
        REQUIRE(extrordinary
            == Task::from_string(extrordinary.to_string()));
        REQUIRE(identical2
            == Task::from_string(identical1.to_string()));
        
    }

}


} // qttodo
