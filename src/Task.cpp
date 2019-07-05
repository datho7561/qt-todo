/**
 * \file Task.cpp
 * \author David Thompson
 * \brief Implementation of the Task class
 * \date 2019-06-18
 */

#include "Task.h"


namespace qttodo {

bool Task::is_overdue() const {
    return deadline < Date();
}


void Task::set_complete() {
    completion_date = Date();
}


bool Task::is_expired(ExpiryPolicy expiry_policy) const {

    if (!complete) {
        return false;
    }

    switch (expiry_policy) {
        case ExpiryPolicy::KEEP_ALL:
            return false;
        case ExpiryPolicy::KEEP_TODAY:
            return completion_date < Date();
        case ExpiryPolicy::KEEP_YESTERDAY:
            return completion_date < Date().yesterday();
        default:
            return false;
    }
}


std::string Task::to_string() const {

    std::string rep = "";
    rep += name;
    rep += "\t";
    rep += complete? "1" : "0";
    rep += "\t";
    rep += deadline.to_computer_string();
    rep += "\t";
    rep += completion_date.to_computer_string();
    return rep;
}


Task Task::from_string(std::string str_rep) {

    // TODO:
    // reading a Task from string is not a linear algorithm (Dates must be read
    // twice in order to process). Perhaps consider a refactor in order to
    // make it linear time
    std::string the_name = "";
    std::string the_deadline = "";
    std::string the_completion_date = "";

    unsigned int i = 0;

    for (; str_rep[i] != '\t'; i++) {
        the_name +=  str_rep[i];
    }

    // Skip over tab
    i++;

    bool the_completion = str_rep[i] == '1';

    // Skip to tab then to next character
    i += 2;

    // TODO: this is a very poor algorithm
    // Read the deadline
    for (int c = 0; c < 3; c++) {
        for (; str_rep[i] != '\t'; i++) {
            the_deadline += str_rep[i];
        }
        i++;
        if (c != 2) {
            the_deadline += '\t';
        }
    }

    // The completion date is stored in the rest of the string
    the_completion_date = str_rep.substr(i);

    return Task(
        the_name,
        the_completion,
        Date::from_string(the_deadline),
        Date::from_string(the_completion_date));

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

bool Task::operator >= (const Task & other) const {
    return other < *this || *this == other;
}

} // qttodo
