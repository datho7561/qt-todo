/**
 * \file TaskList.cpp
 * \author David Thompson
 * \brief Implementation for the TaskList object
 * \date 2019-06-18
 */

#include <algorithm>

#include "TaskList.h"


namespace qttodo {

void TaskList::remove_expired(ExpiryPolicy expiry_policy) {

    std::vector<Task> * new_tasks = new std::vector<Task>;
    for (
        std::vector<Task>::iterator iter = tasks->begin();
        iter != tasks->end();
        iter++
        ) {
        // If its not expired, put it in the new list
        if (!iter->is_expired(expiry_policy)) {
            new_tasks->push_back(*iter);
        }
    }
    delete tasks;
    tasks = new_tasks;
}


void TaskList::add_new(Task task) {
    tasks->push_back(task);
    // The array order is preserved everywhere else; this is the only spot
    // where it may change. Sorting is excessive but I'm lazy TODO:
    std::stable_sort(tasks->begin(), tasks->end());
}


VectorForwardReadIterator<Task> TaskList::iterator() const {
    return VectorForwardReadIterator<Task>(tasks);
}


std::string TaskList::to_string() const {

    std::string rep = "";
    rep += name;
    rep += "\n";

    for (unsigned int i = 0; i < tasks->size(); i++) {

        rep += tasks->operator[](i).to_string();
        rep += '\n';

    }

    return rep;

}


TaskList TaskList::from_string(std::string string_rep) {

    std::vector<Task> tasks;
    int end = string_rep.find('\n');
    std::string name = string_rep.substr(0, end);
    string_rep = string_rep.substr(0, end + 1);
    end = string_rep.find('\n');

    while (end != -1) {
        tasks.push_back(Task::from_string(string_rep.substr(0, end)));
        string_rep = string_rep.substr(0, end + 1);
        end = string_rep.find('\n');
    }

    return TaskList(name, tasks);

}

} // qttodo
