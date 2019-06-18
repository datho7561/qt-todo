

#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <vector>
#include <string>

#include "Task.h"
#include "ExpiryPolicy.h"

class TaskList {

private:
    std::vector<Task> tasks;
    std::string name;

public:

    /**
     * \brief Construct a new TaskList given its name
     * 
     * \param name The name of the TaskList
     */
    TaskList(std::string name):
        name(name),
        tasks() {}

    void remove_expired(ExpiryPolicy expiryPolicy) {
        
    }
    

};

#endif // TASK_LIST_H
