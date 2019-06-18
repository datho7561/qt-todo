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
#include "ExpiryPolicy.h"

class Task {

private:
    std::string name;
    Date deadline;
    Date completion_date;
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
    std::string get_name() const { return name; }

    /**
     * \brief Get the Task's deadline
     * 
     * \return The deadline of the task
     */
    Date get_deadline() const { return deadline; }

    /**
     * \brief Check if the Task is complete
     * 
     * \return true if the task is complete, false otherwise
     */
    bool is_complete() const { return complete; }

    /**
     * \brief Returns if the deadline for this task has been passed
     */
    bool is_overdue() const;

    /**
     * \brief Checks if this Task is expired, i.e. it has been complete for
     * the amount of time specified by the expiry policy.
     * 
     * \param expiryPolicy The policy to be used to check if this is considered
     * expired
     * \return true if this Task is expired, false otherwise
     */
    bool is_expired(ExpiryPolicy expiry_policy) const;

    /**
     * \brief Set the Task to be completed
     */
    void set_complete();

    /**
     * \brief Set the task to be incomplete
     */
    void set_incomplete() { this->complete = false; }

    /**
     * \brief Checks if this Task should be ordered before another one
     * \detail Orders by deadline first, then if the date is the same,
     * orders by name lexicographially. Returns false if the Tasks are
     * equivalent.
     * 
     * \param other The other Task to check the ordering against
     * \return true if this task should be placed before the other
     */
    bool operator < (const Task & other) const;

    /**
     * \brief Checks if two Tasks are equivalent
     * \detail Checks if the name and deadline are identical
     * 
     * \param other The other Task to check against
     * \return true if the Tasks are equivalent, false otherwise
     */
    bool operator == (const Task & other) const;

    /**
     * \brief Checks if this Task should be ordered after another one
     * \detail Orders by deadline first, then if the date is the same,
     * orders by name lexicographially. Returns false if the Tasks are
     * equivalent.
     * 
     * \param other The other Task to check the ordering against
     * \return true if this task should be placed after the other
     */
    bool operator > (const Task & other) const;

    /**
     * \brief Check if this Task should be placed before another or if it is
     * equivalent to another
     * 
     * \param other The Task to compare against
     * \return true if either this Task should be placed before the other or
     * the tasks are equivalent, false otherwise
     */
    bool operator <= (const Task & other) const;

    /**
     * \brief Check if this Task should be placed after another or if it is
     * equivalent to another
     * 
     * \param other The Task to compare against
     * \return true if either this Task should be placed after the other or
     * the tasks are equivalent, false otherwise
     */
    bool operator >= (const Task & other) const;

};



#endif // TASK_H
