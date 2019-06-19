/**
 * \file TaskList.cpp
 * \author David Thompson
 * \brief Implementation for the TaskList object
 * \date 2019-06-18
 */

#include "TaskList.h"

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