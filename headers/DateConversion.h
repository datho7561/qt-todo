/**
 * \file DateConversion.h
 * \author David Thompson
 * \brief Contains functions for converting Date objects
 * \date 14-08-2019
 */

#ifndef DATE_CONVERISON_H
#define DATE_CONVERSION_H

#include <QDate>

#include "Date.h"

namespace qttodo {

/**
 * \brief Converts from QDate to qttodo::Date
 * 
 * \param date the QDate
 * \returns the qttodo::Date
 */
static Date to_qttodo_date(QDate date) {
    return Date(date.day(), date.month(), date.year());
}

/**
 * \brief Converts from qttodo::Date to QDate
 * 
 * \param date qttodo::Date
 * \returns The QDate
 */
static QDate to_qdate(Date date) {
    return QDate(date.get_year(), date.get_month(), date.get_day());
}

} // qttodo

#endif // DATE_CONVERSION_H