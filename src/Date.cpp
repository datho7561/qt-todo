/**
 * \file Date.cpp
 * \author David Thompson
 * \brief Implementation of the Date class
 * \date 2019-06-14
 */

#include <ctime>
#include <stdexcept>
#include <string>

#include "Date.h"

Date::Date() {

    // Get seconds since 1970
    time_t * curr = new time_t;
    time(curr);

    // Convert to struct with info we want
    struct tm * curr_tm = localtime(curr);

    // Populate
    day = static_cast<unsigned int>(curr_tm->tm_mday);
    month = static_cast<unsigned int>(curr_tm->tm_mon);
    year = curr_tm->tm_year;

    // Avoid mem leaks
    delete curr_tm;
    delete curr;
}


Date::Date(unsigned int day, unsigned int month, int year) {

    if (day == 0 || day > 31) {
        throw std::invalid_argument("Day is out of range");
    }
    day = day;

    if (month == 0 ||  month > 12) {
        throw std::invalid_argument("Month is out of range");
    }

    month = month;

    year = year;
}


std::string Date::toString() const {

    std::string rep = "";

    rep += std::to_string(day);
    rep += getMonthString(month);
    rep += ", ";
    if (year < 0) {
        rep += std::to_string(-1 * year);
        rep += " BCE";
    } else {
        rep += std::to_string(year);
    }

    return rep;

}


bool Date::operator == (const Date & other) const {
    
    return (this->day == other.day
        && this->month == other.month
        && this->year == other.year);
}


bool Date::operator < (const Date & other) const {

    if (this->year < other.year) {
        return true;
    } else if (this->year == other.year) {
        if (this->month < other.month) {
            return true;
        } else if (this->month < other.month) {
            if (this->day < other.day) {
                return true;
            }
        }
    }

    return false;
}


bool Date::operator > (const Date & other) const {

    return !(*this < other) && !(*this == other);
}


bool Date::operator <= (const Date & other) const {

    return (*this < other) || (*this == other);
}


bool Date::operator >= (const Date & other) const {

    return (*this > other) || (*this == other);
}


std::string Date::getMonthString(unsigned int month) {

    switch (month) {
        case 1:
            return std::string("January");
        case 2:
            return std::string("February");
        case 3:
            return std::string("March");
        case 4:
            return std::string("April");
        case 5:
            return std::string("May");
        case 6:
            return std::string("June");
        case 7:
            return std::string("July");
        case 8:
            return std::string("August");
        case 9:
            return std::string("September");
        case 10:
            return std::string("October");
        case 11:
            return std::string("November");
        case 12:
            return std::string("Decemeber");
        default:
            throw std::invalid_argument("Month out of range");
    }
}
