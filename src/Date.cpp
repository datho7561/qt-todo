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

namespace qttodo {

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
    delete curr;
}


Date::Date(unsigned int day, unsigned int month, int year) {

    if (month == 0 ||  month > 12) {
        throw std::invalid_argument("Month is out of range");
    }

    if (day == 0 || day > get_month_days(month, year)) {
        throw std::invalid_argument("Day is out of range");
    }

    this->day = day;
    this->month = month;
    this->year = year;
}


// NOTE TO SELF: I do not need to reuse the keyword static here
Date Date::from_string(std::string source_string) {

    std::string readValue = "";
    unsigned int i = 0;
    int the_year;
    unsigned int the_month;
    unsigned int the_day;

    // Read up until tab
    for (; source_string[i] != '\t'; i++) {
        readValue.push_back(source_string[i]);
    }

    // Parse month
    the_year = std::stoi(readValue);

    // Skip past the tab character
    i++;

    // Reset string
    readValue = "";

    // Rinse & repeat
    for (; source_string[i] != '\t'; i++) {
        readValue.push_back(source_string[i]);
    }
    the_month = std::stoi(readValue);
    i++;
    readValue = "";

    for (; i < source_string.length(); i++) {
        readValue.push_back(source_string[i]);
    }
    the_day = std::stoi(readValue);

    return Date(the_day, the_month, the_year);

}


std::string Date::to_string() const {

    std::string rep = "";

    rep += std::to_string(day);
    rep += " ";
    rep += get_month_string(month);
    rep += ", ";
    if (year < 0) {
        rep += std::to_string(-1 * year);
        rep += " BCE";
    } else {
        rep += std::to_string(year);
    }

    return rep;

}


std::string Date::to_computer_string() const {

    std::string rep = "";

    rep += std::to_string(year);
    rep += '\t';
    rep += std::to_string(month);
    rep += '\t';
    rep += std::to_string(day);
    return rep;
}


Date Date::yesterday() const {
    if (day - 1 > 0) {
        return Date(day - 1, month, year);
    }
    if (month - 1 > 0) {
        return Date(get_month_days(month - 1, year), month - 1, year);
    }
    // We know it has to be last day of December of year before
    return Date(31, 12, year - 1);
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
        } else if (this->month == other.month) {
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


bool Date::operator != (const Date & other) const {

    return !(*this == other);
}


unsigned int Date::get_month_days(unsigned int month, int year) {

    switch (month) {
        case 1:
            return 31;
        case 2:
            // Convoluted leap year rules that I may have gotten incorrect
            if (year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0)) {
                return 29;
            }
            return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            throw std::invalid_argument("Month value out of range");
    }
}


std::string Date::get_month_string(unsigned int month) {

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
            return std::string("December");
        default:
            throw std::invalid_argument("Month out of range");
    }
}

} // qttodo
