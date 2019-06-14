/**
 * \file Date.h
 * \author David Thompson
 * \brief Represents day, month, and year for a particular day
 * \date 2019-06-14
 */

#ifndef DATE_H
#define DATE_H

#include <string>

class Date {

private:

    /**
     * \brief The day of the month that this Date represents
     * \detail 1 represents the first day of the month, 2 the 2nd. etc.
     */
    unsigned int day;

    /**
     * \brief The month that this Date represents
     * \detail January is 1, February is 2, etc.
     */
    unsigned int month;
    
    /**
     * \brief The year that this Date represents
     * \detail Dates AD are positive and dates BCE are negative
     */
    int year;

    /**
     * \brief Get the string representation of this month
     * 
     * \param month The month to get the string representation of
     * \return The string representation of this month
     */
    static std::string getMonthString(unsigned int month);

public:

    /**
     * \brief Make a new Date object which represents the current day
     * \returns A new Date object representing the current day
     */
    Date();

    // TODO: implement a more rigourous version of date verificatio (leap
    // years, days in a month)
    /**
     * \brief Construct a new Date object with a give day, month, and year
     * 
     * \param day 
     * \param month 
     * \param year 
     * 
     * \throws invalid_argument if the day is > 31, the month is > 12, the day
     * 0, or the month is zero
     */
    Date(unsigned int day, unsigned int month, int year);

    /**
     * \brief Destroy a Date object
     */
    ~Date() {};

    /**
     * \brief Get the day of this Date
     * 
     * \return The day of the Date
     */
    unsigned int getDay() const { return day; }

    /**
     * \brief Get the month of this Date
     * 
     * \return The month of this Date
     */
    unsigned int getMonth() const { return month; }

    /**
     * \brief Get the year of this Date
     * 
     * \return The year of this Date
     */
    int getYear() const { return year; }

    /**
     * \brief Get a human-legible string representation of this Date
     * 
     * \return A human-legible string representation of this Date
     */
    std::string toString() const;

    /**
     * \brief Check if two Dates are the same
     * 
     * \param other The other date to chck against
     * \return true If the dates are equal, false otherwise
     */
    bool operator == (const Date & other) const;

    /**
     * \brief Check if this Date is before another
     * 
     * \param other The other Date to check
     * \return true if this date is before the other, false otherwise
     */
    bool operator < (const Date & other) const;

    /**
     * \brief Checks if this Date is after another
     * 
     * \param other The other date fto check against
     * \return true If this date is after the other, false otherwise
     */
    bool operator > (const Date & other) const;

    /**
     * \brief Checks if this Date is before or equal to another
     * 
     * \param other The other Date to check against
     * \return true If the date is before or equal to other, false otherwise
     */
    bool operator <= (const Date & other) const;

    /**
     * \brief Checks if the Date is after or equal to another
     * 
     * \param other The other Date to check against
     * \return true If the date is before or equal to other, false otherwise
     */
    bool operator >= (const Date & other) const;

};

#endif // DATE_H
