#include "container.hpp"

template <typename T>
Container<T>::Container(const int size, const int stepIncreasing) {
    this->size = size;
    this->stepIncreasing = stepIncreasing;
    this->elements = new T[size];
    this->count = 0;
}