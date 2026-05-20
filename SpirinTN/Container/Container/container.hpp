#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

template<typename T>
class Container {
private:
    T* elements;
    int size;
    int count;
    int stepIncreasing;

	void reallocContainer(const int newSize);
public:
    Container() noexcept : elements(nullptr), size(0), count(0), stepIncreasing(1) {};
    Container(const int size, const int stepIncreasing = 1);
    Container(const Container<T>& c);
    ~Container();

    int getSize();
    int getCount();   

    int findElement(const T& elem) const;
    void addElement(const T& elem, int pos = -1);
    void removeAt(const int pos);
    void removeElement(const T& elem);

    T operator[](int pos) const;
    const Container<T>& operator= (const Container<T>& c);
};

template<typename T>
class Container<T*> {
private:
    T** elements;
    int size;
    int count;
    int stepIncreasing;
public:
    Container() noexcept : elements(nullptr), size(0), count(0), stepIncreasing(1) {};
    Container(const int size, const int stepIncreasing = 1);
    Container(const Container<T*>& c);
    ~Container();

    int getSize();
    int getCount();

    void reallocContainer(const int newSize);

    int findElement(const T& elem) const;
    void addElement(const T* elem, int pos = -1);
    void removeAt(const int pos);
    void removeElement(const T& elem);

    T* operator[](int pos) const;
    const Container<T*>& operator= (const Container<T*>& c);
};

template <typename T>
Container<T>::Container(const int size, const int stepIncreasing) {
    if (stepIncreasing <= 0) {
        throw std::runtime_error("step increasing must be greater than 0!");
    }
    this->size = size;
    this->stepIncreasing = stepIncreasing;
    this->elements = new T[size];
    this->count = 0;
}

template <typename T>
Container<T>::Container(const Container<T>& c) {
    this->size = c.size;
    this->stepIncreasing = c.stepIncreasing;
    this->elements = new T[this->size];
    this->count = c.count;
    for (int i = 0; i < this->count; i++) {
        this->elements[i] = c.elements[i];
    }
}

template <typename T>
Container<T>::~Container() {
    delete[](this->elements);
}

template <typename T>
int Container<T>::getSize() {
    return this->size;
}

template <typename T>
int Container<T>::getCount() {
    return this->count;
}

template <typename T>
void Container<T>::reallocContainer(const int newSize) {
    if (newSize < 0) {
        throw std::runtime_error("the size of the container cannot be negative!");
    }
    T* newElements = new T[newSize];
    for (int i = 0; i < this->count && i < newSize; i++) {
        newElements[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newElements;
    this->size = newSize;
    if (newSize < this->count) {
        this->count = newSize;
    }
}

template <typename T>
int Container<T>::findElement(const T& elem) const {
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == elem) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Container<T>::addElement(const T& elem, int pos) {
    if (pos > count || pos < -1) {
        throw std::out_of_range("out of range");
    }
    else if (pos == -1) {
        pos = count;
    }

    if (this->size == this->count) {
        this->reallocContainer(this->size + this->stepIncreasing);
    }

    for (int i = count; i > pos; i--) {
        this->elements[i] = this->elements[i - 1];
    }
    this->elements[pos] = elem;
    this->count++;
}

template <typename T>
void Container<T>::removeAt(const int pos) {
    if (pos < 0 || pos > this->count - 1) {
        throw std::out_of_range("out of range");
    }

    for (int i = pos; i < this->count - 1; i++) {
        this->elements[i] = this->elements[i + 1];
    }
    this->elements[this->count - 1].~T();
    this->count--;
}

template <typename T>
void Container<T>::removeElement(const T& elem) {
    const int pos = this->findElement(elem);
    if (pos == -1) {
        throw std::runtime_error("there is no such element in the container!");
    }
    this->removeAt(pos);
}

template <typename T>
T Container<T>::operator[](int pos) const {
    if (pos < 0 || pos > this->count - 1) {
        throw std::out_of_range("out of range");
    }
    return this->elements[pos];
}

template <typename T>
const Container<T>& Container<T>::operator= (const Container<T>& c) {
    if (this == &c) return *this;

    this->size = c.size;
    this->stepIncreasing = c.stepIncreasing;
    this->count = c.count;
    this->elements = new T[c.size];
    for (int i = 0; i < this->count; i++) {
        this->elements[i] = c.elements[i];
    }

    return *this;
}

template <typename T>
Container<T*>::Container(const int size, const int stepIncreasing) {
    if (stepIncreasing <= 0) {
        throw std::runtime_error("step increasing must be greater than 0!");
    }
    this->size = size;
    this->stepIncreasing = stepIncreasing;
    this->elements = new T*[size];
    this->count = 0;
}

template <typename T>
Container<T*>::Container(const Container<T*>& c) {
    this->size = c.size;
    this->stepIncreasing = c.stepIncreasing;
    this->count = c.count;
    this->elements = new T * [this->size];

    int i;
    try {
        for (i = 0; i < this->count; i++) {
            this->elements[i] = new T(*c.elements[i]);
        }
    }
    catch (...) {
        for (int j = 0; j < i; j++) {
            delete this->elements[j];
        }
        delete this->elements;
        throw std::bad_alloc();
    }
}

template<typename T>
Container<T*>::~Container() {
    for (int i = 0; i < this->count; i++) {
        delete this->elements[i];
    }
    delete[] this->elements;
}

template <typename T>
int Container<T*>::getSize() {
    return this->size;
}

template <typename T>
int Container<T*>::getCount() {
    return this->count;
}

template <typename T>
void Container<T*>::reallocContainer(const int newSize) {
    if (newSize < 0) {
        throw std::runtime_error("the size of the container cannot be negative!");
    }
    T** newElements = new T*[newSize];
    int i;
    try {
        for (i = 0; i < this->count && i < newSize; i++) {
            newElements[i] = new T(*this->elements[i]);
        }
    }
    catch (...) {
        for (int j = 0; j < i; j++) {
            delete newElements[i];
        }
        delete newElements;
        throw std::bad_alloc();
    }

    delete[] this->elements;
    this->elements = newElements;
    this->size = newSize;
    if (newSize < this->count) {
        this->count = newSize;
    }
}

template<typename T>
int Container<T*>::findElement(const T& elem) const {
    for (int i = 0; i < this->count; i++) {
        if (*(this->elements[i]) == elem) {
            return i;
        }
    }
    return -1;
}

template<typename T>
void Container<T*>::addElement(const T* elem, int pos) {
    if (pos > count || pos < -1) {
        throw std::out_of_range("out of range");
    }
    else if (pos == -1) {
        pos = count;
    }

    if (this->size == this->count) {
        this->reallocContainer(this->size + this->stepIncreasing);
    }

    for (int i = count; i > pos; i--) {
        this->elements[i] = this->elements[i - 1];
    }
    this->elements[pos] = new T(*elem);
    this->count++;
}

template<typename T>
void Container<T*>::removeElement(const T& elem) {
    const int pos = this->findElement(elem);
    if (pos == -1) {
        throw std::runtime_error("there is no such element in the container!");
    }
    this->removeAt(pos);
}

template<typename T>
void Container<T*>::removeAt(const int pos) {
    if (pos < 0 || pos > this->count - 1) {
        throw std::out_of_range("out of range");
    }

    delete this->elements[pos];
    for (int i = pos; i < this->count - 1; i++) {
        this->elements[i] = this->elements[i + 1];
    }
    this->elements[this->count - 1] = nullptr;

    this->count--;
}

template <typename T>
T* Container<T*>::operator[](int pos) const {
    if (pos < 0 || pos > this->count - 1) {
        throw std::out_of_range("out of range");
    }
    return this->elements[pos];
}

template <typename T>
const Container<T*>& Container<T*>::operator= (const Container<T*>& c) {
    if (this == &c) return *this;

    T** newElements = new T*[c.size];
    int i;
    try {
        for (i = 0; i < c.count; i++) {
            newElements[i] = new T(*(c.elements[i]));
        }
    }
    catch (...) {
        for (int j = 0; j < i; j++) {
            delete newElements[j];
        }
        delete[] newElements;
        throw std::bad_alloc();
    }

    for (int i = 0; i < this->count; i++) {
        delete this->elements[i];
    }
    delete[] this->elements;
    this->elements = newElements;
    this->size = c.size;
    this->stepIncreasing = c.stepIncreasing;
    this->count = c.count;

    return *this;
}
#endif