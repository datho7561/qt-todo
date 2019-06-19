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

#include "Task.h"
#include "ExpiryPolicy.h"
#include "ForwardReadIterator.h"

class TaskList {

private:
    std::string name;
    std::vector<Task> tasks;

public:

    /**
     * \brief Construct a new TaskList given its name
     * 
     * \param name The name of the TaskList
     */
    TaskList(std::string name):
        name(name),
        tasks() {}

    /**
     * \brief Construct a new TaskList given its name and an array of its
     * elements
     * 
     * \param name The name of the TaskList
     * \param tasks A vector of the Tasks in the TaskList
     */
    TaskList(std::string name, std::vector<Task> tasks):
        name(name),
        tasks(tasks) {}

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
     * \brief Get an ForwardReadIterator that allows iterating through the
     * Tasks
     * 
     * \returns A ForwardReadIterator over this TaskList's Tasks
     */
    VectorForwardReadIterator<Task> iterator() const;

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

};

#endif // TASK_LIST_H
