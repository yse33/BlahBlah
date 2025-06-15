#pragma once

#include "MyString.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Container;

template<typename T>
ostream& operator<<(ostream& os, const Container<T>& myVector);
template<typename T>
istream& operator>>(istream& is, Container<T>& myVector);

template<typename T>
class Container {
private:
    T** data = nullptr;
    size_t size = 0;
    size_t capacity = 8;

    void copyFrom(const Container& other);
    void moveFrom(Container&& other) noexcept;
    void free();
    void resize(size_t newCapacity);
public:
    Container();
    Container(const Container& other);
    Container(Container&& other) noexcept;

    Container& operator=(const Container& other);
    Container& operator=(Container&& other) noexcept;

    ~Container();

    size_t getSize() const;
    bool isEmpty() const;

    void push(const T& object);
    void push(T* pointer);
    T* peek();
    T* getById(size_t id) const;
    T* getByName(const MyString& name) const;
    void remove(size_t index);
    void removeById(size_t id);
    void removeByName(const MyString& name);
    void clear();

    T* operator[](size_t index);
    const T* operator[](size_t index) const;

    friend ostream& operator<< <>(ostream& os, const Container& myVector);
    friend istream& operator>> <>(istream& is, Container& myVector);
};

template<typename T>
void Container<T>::copyFrom(const Container& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T*[capacity]{};
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i]->clone();
    }
}

template<typename T>
void Container<T>::moveFrom(Container&& other) noexcept {
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

template<typename T>
void Container<T>::free() {
    for (size_t i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;

    data = nullptr;
    size = capacity = 0;
}

template<typename T>
void Container<T>::resize(const size_t newCapacity) {
    T** newData = new T*[newCapacity]{};
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;

    data = newData;
    capacity = newCapacity;
}

template<typename T>
Container<T>::Container() {
    data = new T*[capacity]{};
}

template<typename T>
Container<T>::Container(const Container& other) {
    copyFrom(other);
}

template<typename T>
Container<T>::Container(Container&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename T>
Container<T>& Container<T>::operator=(const Container& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Container<T>& Container<T>::operator=(Container&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
Container<T>::~Container() {
    free();
}

template<typename T>
size_t Container<T>::getSize() const {
    return size;
}

template<typename T>
bool Container<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void Container<T>::push(const T& object) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = object.clone();
}

template<typename T>
void Container<T>::push(T* pointer) {
    if (!pointer) throw invalid_argument("Cannot push a null pointer");

    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = pointer;
}

template<typename T>
T* Container<T>::peek() {
    if (size == 0) throw out_of_range("Vector is empty");
    return data[size - 1];
}

template<typename T>
T* Container<T>::getById(const size_t id) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i]->getId() == id) {
            return data[i];
        }
    }
    return nullptr;
}

template<typename T>
T* Container<T>::getByName(const MyString& name) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i]->getName() == name) {
            return data[i];
        }
    }
    return nullptr;
}

template<typename T>
void Container<T>::remove(const size_t index) {
    if (size == 0) throw out_of_range("Vector is empty");
    if (index >= size) throw out_of_range("Index out of range");
    delete data[index];

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    data[size - 1] = nullptr;
    size--;
}

template<typename T>
void Container<T>::removeById(const size_t id) {
    for (size_t i = 0; i < size; i++) {
        if (data[i]->getId() == id) {
            remove(i);
            return;
        }
    }
    throw invalid_argument("No element with the given ID found");
}

template<typename T>
void Container<T>::removeByName(const MyString& name) {
    for (size_t i = 0; i < size; i++) {
        if (data[i]->getName() == name) {
            remove(i);
            return;
        }
    }
    throw invalid_argument("No element with the given name found");
}

template<typename T>
void Container<T>::clear() {
    free();
    capacity = 8;
    data = new T*[capacity]{};
}

template<typename T>
T* Container<T>::operator[](size_t index) {
    if (index >= size) throw out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T* Container<T>::operator[](size_t index) const {
    if (index >= size) throw out_of_range("Index out of range");
    return data[index];
}

template<typename T>
ostream& operator<<(ostream& os, const Container<T>& myVector) {
    for (size_t i = 0; i < myVector.size; i++) {
        os << *myVector.data[i] << endl;
    }
    return os;
}

template<typename T>
istream& operator>>(istream& is, Container<T>& myVector) {
    for (size_t i = 0; i < myVector.size; i++) {
        is >> *myVector.data[i];
    }
    return is;
}