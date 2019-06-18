

#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <vector>
#include <string>

#include "Task.h"
#include "ExpiryPolicy.h"

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
     * \brief Remove all expired items from the TaskList
     * 
     * \param expiry_policy The policy to determine if an item is expired
     */
    void remove_expired(ExpiryPolicy expiry_policy);

};

#endif // TASK_LIST_H
