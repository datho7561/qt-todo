/**
 * \file TaskList.cpp
 * \author David Thompson
 * \brief Implementation for the TaskList object
 * \date 2019-06-18
 */

#include "TaskList.h"
#include "VectorForwardReadIterator.h"

void TaskList::remove_expired(ExpiryPolicy expiry_policy) {

    std::vector<Task> new_tasks;
    for (
        std::vector<Task>::iterator iter = tasks.begin();
        iter != tasks.end();
        iter++
        ) {
        // If its not expired, put it in the new list
        if (!iter->is_expired(expiry_policy)) {
            new_tasks.push_back(*iter);
        }
    }
    tasks = new_tasks;
}


std::string TaskList::to_string() const {

    std::string rep = "";
    rep += name;
    rep += "\n";

    for (int i = 0; i < tasks.size(); i++) {

        rep += tasks[i].to_string();
        rep += '\n';

    }

    return rep;

}


TaskList TaskList::from_string(std::string string_rep) {

    std::vector<Task> tasks;
    unsigned int end = string_rep.find('\n');
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


VectorForwardReadIterator<Task> TaskList::iterator() const {
    return VectorForwardReadIterator<Task>(&tasks);
}
