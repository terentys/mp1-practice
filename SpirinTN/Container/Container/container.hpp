#ifndef CONTAINER_H
#define CONTAINER_H

template<typename T>
class Container {
private:
    T* elements;
    int size;
    int count;
    int stepIncreasing;

    void _copyFrom(const Container<T>& c);
public:
    Container() noexcept : elements(nullptr), size(0), count(0), stepIncreasing(0) {};
    Container(const int size, const int stepIncreasing);
    Container(const Container<T>& c);
    ~Container();

    int findElement(const T& elem) const;
    void addElement(const T& elem, const int pos);
    void addElement(const T& elem);
    void removeElement(const T& elem);
    void removeElement(const int pos);

    void realloc(const int newSize);

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

    void _copyFrom(const Container<T*>& c);
public:
    Container() noexcept : elements(nullptr), size(0), count(0), stepIncreasing(0) {};
    Container(const int size, const int stepIncreasing);
    Container(const Container<T*>& c);
    ~Container();

    int findElement(const T* elem) const;
    void addElement(const T* elem, const int pos);
    void addElement(const T* elem);
    void removeElement(const T* elem);
    void removeElement(const int pos);

    void realloc(const int newSize);

    T* operator[](int pos) const;
    const Container<T*>& operator= (const Container<T*>& c);
};

#endif