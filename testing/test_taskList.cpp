
#include <iostream>

#include "catch.hpp"

#include "TaskList.h"

namespace qttodo {

// TODO: could use a bit more test cases, definitely needs more edge cases
TEST_CASE("TaskList") {

    std::vector<Task> tasks;
    Task task1 = Task("Task One", Date());
    Task task2 = Task("Task Two", Date().yesterday());
    tasks.push_back(task1);
    tasks.push_back(task2);

    TaskList empty_list("Empty List");
    TaskList prepopulated("Prepopulated", tasks);

    SECTION("Iterator") {
        REQUIRE(empty_list.begin() == empty_list.end());
        auto pop_iter = prepopulated.begin();
        REQUIRE(*(*pop_iter) == task1);
        pop_iter++;
        REQUIRE(*(*pop_iter) == task2);
        pop_iter++;
        REQUIRE(pop_iter == prepopulated.end());

        // Test to make sure range-based for syntax works
        for (Task * task: prepopulated) {
            task->get_name();
        }
    }

    SECTION("To/From String") {
        // Directly cehcking string
        REQUIRE(empty_list.to_string() == std::string("Empty List\n"));
        REQUIRE(prepopulated.to_string()
            == std::string("Prepopulated\n"
            + task1.to_string()
            + "\n"
            + task2.to_string())
            +"\n");

        // Roundabout way of checking from_string
        REQUIRE(empty_list.to_string()
            == TaskList::from_string(empty_list.to_string()).to_string());
        REQUIRE(prepopulated.to_string()
            == TaskList::from_string(prepopulated.to_string()).to_string());

        // Running it through twice to see if it still is the same
        REQUIRE(empty_list.to_string()
            == TaskList::from_string(TaskList::from_string(empty_list.to_string()).to_string()).to_string());
        REQUIRE(prepopulated.to_string()
            == TaskList::from_string(TaskList::from_string(prepopulated.to_string()).to_string()).to_string());
        
        // Other ways to check if they have changed
        TaskList rehydrated_empty = TaskList::from_string(empty_list.to_string());
        TaskList rehydrated_pop = TaskList::from_string(prepopulated.to_string());
        REQUIRE(rehydrated_empty.begin() == rehydrated_empty.end());
        unsigned int pop_count = 0;
        for (Task * t: rehydrated_pop) {
            pop_count++;
        }
        REQUIRE(pop_count == 2);
    }

}

} // qttodo
