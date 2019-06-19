/**
 * \file ForwardReadIterator.h
 * \author David Thompson
 * \brief An interface for iterating over a collection
 * \date 2019-06-19
 */

#ifndef FORWARD_READ_ITERATOR
#define FORWARD_READ_ITERATOR

template <typename T>
class ForwardReadIterator {
public:

    /**
     * \brief Get the current item in the ForwardReadIterator
     * 
     * \returns The current item in the ForwardReadIterator
     */
    virtual T get() const = 0;

    /**
     * \brief Move to the next item in the ForwardReadIterator
     * 
     * \throws out_of_range if there is no next item
     */
    virtual void next() = 0;

    /**
     * \brief Checks if the ForwardReadIterator has a next item
     * 
     * \returns true if there is a next item, false otherwise
     */
    virtual bool has_next() const = 0;

};

#endif // FORWARD_READ_ITERATOR
