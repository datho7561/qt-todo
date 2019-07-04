/**
 * \file VectorForwardReadIterator.cpp
 * \author David Thompson
 * \brief Implementation of a VectorForwardReadIterator
 * \date 2019-06-19
 */

#include "VectorForwardReadIterator.h"


template<class T>
const T VectorForwardReadIterator<T>::get() const {
    return vect_ptr->operator[](i);
}


template<class T>
void VectorForwardReadIterator<T>::next() {
    i++;
}


template<class T>
bool VectorForwardReadIterator<T>::has_next() const {
    return i < vect_ptr->size;
}
