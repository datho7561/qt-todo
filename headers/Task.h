/**
 * \file Task.h
 * \author David Thompson
 * \brief Describes a task that the user wants to remember to complete
 * \date 2019-06-17
 */

#ifndef TASK_H
#define TASK_H

#include <string>

#include "Date.h"

class Task {

private:
    std::string name;
    Date deadline;
    Date completionDate;
    bool complete;

public:

    /**
     * \brief Construct a new Task object
     * 
     * \param name The name of the task
     * \param deadline When the task is intended to be completed by
     * \returns A new Task
     */
    Task(std::string name, Date deadline):
        name(name),
        deadline(deadline),
        complete(false) {}

    /**
     * \brief Get the name of the Task
     * 
     * \return The name of the Task
     */
    std::string get_name() const { return this->name; }

    /**
     * \brief Check if the Task is complete
     * 
     * \return true if the task sis complete, false otherwise
     */
    bool is_complete() const { return complete; }

    /**
     * \brief Returns if the deadline for this task has been passed
     * 
     */
    bool is_overdue() const;

    /**
     * \brief Set the Task to be completed
     */
    void set_complete() { this->complete = true; }

    /**
     * \brief Set the task to be incomplete
     * 
     */
    void set_incomplete() { this->complete = false; }

};

#endif // TASK_H
