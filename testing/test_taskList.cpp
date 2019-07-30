
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
        auto empty_list_iter = empty_list.iterator();
        REQUIRE(empty_list_iter.begin() == empty_list_iter.end());
        
        auto pop_list_iter = prepopulated.iterator();
        // TODO: I should either rename this method or not
        REQUIRE(pop_list_iter[0] == task1);
        REQUIRE(pop_list_iter[1] == task2);
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
        REQUIRE(TaskList::from_string(empty_list.to_string()).iterator().size() == 0);
        REQUIRE(TaskList::from_string(prepopulated.to_string()).iterator().size() == 2);
    }

}

} // qttodo
