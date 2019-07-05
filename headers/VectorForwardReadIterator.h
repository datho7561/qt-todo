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
#include "Task.h"

namespace qttodo {

template <typename T>
class VectorForwardReadIterator: public ForwardReadIterator<T> {

private:
    const std::vector<T> * vect_ptr;
    int i;

public:

    /**
     * \brief Make a new VectorForwardReadIterator
     * 
     * \param vect_ptr A pointer to the vector to use for thi
     * VectorForwardReadIterator
     */
    VectorForwardReadIterator(const std::vector<T> * vector_pointer):
        vect_ptr(vector_pointer),
        i(0) {}
    
    // These are inherited from ForwardReadIterator
    virtual const T get() const;
    virtual void next();
    virtual bool has_next() const;

};

template class VectorForwardReadIterator<Task>;

} // qttodo

#endif // VECTOR_FORWARD_READ_ITERATOR
