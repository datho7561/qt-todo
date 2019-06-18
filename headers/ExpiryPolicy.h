/**
 * \file ExpiryPolicy.h
 * \author David Thompson
 * \brief Condtains the definition of the ExpiryPolicy enum
 * \date 2019-06-18
 */

#ifndef EXPIRY_POLICY_H
#define EXPIRY_POLICY_H

/**
 * \brief Defines different policies for when completed items should be
 * considered expired
 * \detail Expired items will be marked for deletion
 */
enum class ExpiryPolicy {

    KEEP_ALL, KEEP_TODAY, KEEP_YESTERDAY

};

#endif // EXPIRY_POLICY_H
