#ifndef MEMUTILS_H
#define MEMUTILS_H

template<typename T>
void swap(T& t1, T& t2) {
    T tmp(t1); // call copy constructor
    t1 = t2; // call copy operator
    t2 = tmp; // call copy operator
}

#endif // MEMUTILS_H
