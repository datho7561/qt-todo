/**
 * \file TaskList.h
 * \author David Thompson
 * \brief Defines the TaskList class
 * \date 2019-06-18
 */

#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <vector>
#include <string>
#include <memory>

#include "Task.h"
#include "ExpiryPolicy.h"

namespace qttodo {

class TaskList {

private:
    std::string name;
    std::unique_ptr<std::vector<std::unique_ptr<Task>>> tasks;

    /**
     * \brief This is the vector that allows TaskList to be treated as an
     * iterator
     * \detail begin() recalculates this vector, and end() uses the existing
     * end of the vector. It is expected that begin will be called first.
     * TODO: maybe make a bool variable to prevent this from breaking programs
     * that want/need to access this way?
     */
    mutable std::vector<Task *> iter_vect;

public:

    /**
     * \brief Construct a new TaskList given its name
     * 
     * \param name The name of the TaskList
     */
    TaskList(std::string name):
        name(name),
        tasks(new std::vector<std::unique_ptr<Task>>) {}

    /**
     * \brief Construct a new TaskList given its name and an array of its
     * elements
     * 
     * \param name The name of the TaskList
     * \param tasks A vector of the Tasks in the TaskList
     */
    TaskList(std::string name, std::vector<Task> initial_tasks);

    /**
     * \brief Make a copy of a TaskList
     * 
     * \param task_list The TaskList to copy
     */
    TaskList(const TaskList & task_list);

    /**
     * \brief Delete a TaskList
     */
    ~TaskList() {}

    /**
     * \brief Remove all expired items from the TaskList
     * 
     * \param expiry_policy The policy to determine if an item is expired
     */
    void remove_expired(ExpiryPolicy expiry_policy);

    /**
     * \brief Add a new task to this TaskList
     * 
     * \param task The Task to add
     */
    void add_new(Task task);

    /**
     * \brief Returns a read iterator at the beginning of the list of tasks
     * 
     * \returns A read iterator at the beginning of the list of tasks
     */
    std::vector<Task *>::const_iterator begin() const;

    /**
     * \brief Returns a read iterator past the end of the list of tasks
     * 
     * \returns A read iterator past the end of the list of tasks
     */
    std::vector<Task *>::const_iterator end() const;

    /**
     * \brief Convert this TaskList to a computer readable string
     * 
     * \returns The TaskList represented as a computer readable string
     */
    std::string to_string() const;

    /**
     * \brief Make a TaskList from a computer readable TaskList string
     * 
     * \returns The TaskList that the string represents
     * \throws invalid_argument if the string is not in the expected format
     */
    static TaskList from_string(std::string string_rep);

    /**
     * \brief Gets the name of this TaskList
     * 
     * \returns The name of the TaskList
     */
    std::string get_name() const {
        return name;
    }

};

} // qttodo

#endif // TASK_LIST_H
