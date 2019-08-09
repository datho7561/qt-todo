/**
 * \file TaskList.cpp
 * \author David Thompson
 * \brief Implementation for the TaskList object
 * \date 2019-06-18
 */

#include <algorithm>

#include "TaskList.h"


namespace qttodo {

TaskList::TaskList(const TaskList & task_list):
    tasks(new std::vector<std::unique_ptr<Task>>) {

    // Copy in the name and list of the other TaskList
    name = task_list.name;
    for (Task * t : task_list) {
        tasks->push_back(std::unique_ptr<Task>(new Task(*t)));
    }
}


TaskList::TaskList(std::string name, std::vector<Task> initial_tasks):
    name(name),
    tasks() {

    // Copy the provided tasks into the internal list of tasks
    // Put on heap to share with others
    for (Task t : initial_tasks) {
        tasks->push_back(std::unique_ptr<Task>(new Task(t)));
    }
}


void TaskList::remove_expired(ExpiryPolicy expiry_policy) {

    std::vector<std::unique_ptr<Task>> * new_tasks =
        new std::vector<std::unique_ptr<Task>>;
    for (
        std::vector<std::unique_ptr<Task>>::iterator iter = tasks->begin();
        iter != tasks->end();
        iter++
        ) {
        // If its not expired, put it in the new list
        if (!(*iter)->is_expired(expiry_policy)) {
            // Use move semantics in order to move the unique_ptr to the new
            // version of the list without destroying/copying the underlying
            // object
            new_tasks->push_back(std::unique_ptr<Task>(std::move(*iter)));
        }
    }
    // Set the tasks to the new value. The original vector gets autodeleted, and
    // any Tasks not transfered to the list get autodeleted
    tasks.reset(new_tasks);
}


void TaskList::add_new(Task task) {

    // The array order is preserved everywhere else, so all that's needed is an
    // insert
    tasks->push_back(std::unique_ptr<Task>(new Task(task)));

    std::vector<std::unique_ptr<Task>>::reverse_iterator iter = tasks->rbegin();

    // While the task belongs before ones that are currently before it
    while (iter != tasks->rend() && *iter < *(iter+1)) {
        // Swaps ownership of the Task downwards
        (*iter).swap(*(iter+1));
    }
}


std::string TaskList::to_string() const {

    std::string rep = "";
    rep += name;
    rep += "\n";

    for (unsigned int i = 0; i < tasks->size(); i++) {
        rep += tasks->operator[](i)->to_string();
        rep += '\n';
    }

    return rep;
}


TaskList TaskList::from_string(std::string string_rep) {

    std::vector<Task> read_tasks;
    int end = string_rep.find('\n');
    std::string name = string_rep.substr(0, end);
    string_rep = string_rep.substr(end + 1);
    end = string_rep.find('\n');

    while (end != -1) {
        // TODO: Maybe make this more legible?
        read_tasks.push_back(Task::from_string(string_rep.substr(0, end)));
        string_rep = string_rep.substr(end + 1);
        end = string_rep.find('\n');
    }

    return TaskList(name, read_tasks);
}


std::vector<Task *>::const_iterator TaskList::begin() const {
    std::vector<Task *> iter_vect;
    for (
        std::vector<std::unique_ptr<Task>>::iterator i = tasks->begin();
        i != tasks->end();
        i++) {
        iter_vect.push_back(i->get());
    }
    return iter_vect.begin();
}


std::vector<Task *>::const_iterator TaskList::end() const {
    return iter_vect.end();
}

} // qttodo
