/**
 * \file Task.cpp
 * \author David Thompson
 * \brief Implementation of the Task class
 * \date 2019-06-18
 */

#include "Task.h"


bool Task::is_overdue() const {
    return deadline < Date();
}


bool Task::operator < (const Task & other) const {

    if (deadline < other.deadline) {
        return true;
    }

    if (name < other.name) {
        return true;
    }

    return false;
}


bool Task::operator == (const Task & other) const {
    return deadline == other.deadline && name == other.name;
}

bool Task::operator > (const Task & other) const {
    return other < *this;
}

bool Task::operator <= (const Task & other) const {
    return *this < other || *this == other;
}

bool Task::operator <= (const Task & other) const {
    return other < *this || *this == other;
}