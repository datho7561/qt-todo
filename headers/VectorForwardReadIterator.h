/**
 * \file VectorForwardReadIterator.h
 * \author David Thompson
 * \brief The definition for an implementation of a ForwardReadIterator using
 * a std::vector as the collection
 * \date 2019-06-19
 */

#ifndef VECTOR_FORWARD_READ_ITERATOR
#define VECTOR_FORWARD_READ_ITERATOR

#include <vector>

#include "ForwardReadIterator.h"

template <typename T>
class VectorForwardReadIterator: ForwardReadIterator<T> {

private:
    std::vector<T> * vect_ptr;
    int i;

public:

    /**
     * \brief Make a new VectorForwardReadIterator
     * 
     * \param vect_ptr A pointer to the vector to use for thi
     * VectorForwardReadIterator
     */
    VectorForwardReadIterator(std::vector<T> * vect_ptr): vect_ptr(vect_ptr) {}
    
    // These are inherited from ForwardReadIterator
    virtual T get() const;
    virtual void next();
    virtual bool has_next();

};

#endif // VECTOR_FORWARD_READ_ITERATOR
