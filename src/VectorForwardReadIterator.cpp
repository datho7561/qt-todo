/**
 * \file VectorForwardReadIterator.cpp
 * \author David Thompson
 * \brief Implementation of a VectorForwardReadIterator
 * \date 2019-06-19
 */

#include "VectorForwardReadIterator.h"


namespace qttodo {

template <typename T>
const T VectorForwardReadIterator<T>::get() const {
    return vect_ptr->operator[](i);
}


template <typename T>
void VectorForwardReadIterator<T>::next() {
    i++;
}


template <typename T>
bool VectorForwardReadIterator<T>::has_next() const {
    return i < vect_ptr->size();
}

} // qttodo
