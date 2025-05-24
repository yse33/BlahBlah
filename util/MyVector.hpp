#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class MyVector;

template<typename T>
ostream& operator<<(ostream& os, const MyVector<T>& myVector);
template<typename T>
istream& operator>>(istream& is, MyVector<T>& myVector);

template<typename T>
class MyVector {
private:
    T** data = nullptr;
    size_t size = 0;
    size_t capacity = 8;

    void copyFrom(const MyVector& other);
    void moveFrom(MyVector&& other) noexcept;
    void free();
    void resize(size_t newCapacity);
public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;

    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;

    ~MyVector();

    size_t getSize() const;

    void push(const T& object);
    void push(T* pointer);
    void remove(size_t index);
    bool isEmpty() const;

    T* operator[](size_t index);
    const T* operator[](size_t index) const;

    friend ostream& operator<< <>(ostream& os, const MyVector& myVector);
    friend istream& operator>> <>(istream& is, MyVector& myVector);
};

template<typename T>
void MyVector<T>::copyFrom(const MyVector& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T*[capacity]{};
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i]->clone();
    }
}

template<typename T>
void MyVector<T>::moveFrom(MyVector&& other) noexcept {
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

template<typename T>
void MyVector<T>::free() {
    for (size_t i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;

    data = nullptr;
    size = capacity = 0;
}

template<typename T>
void MyVector<T>::resize(const size_t newCapacity) {
    if (newCapacity <= capacity) return;

    T** newData = new T*[newCapacity]{};
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
MyVector<T>::MyVector() {
    data = new T*[capacity]{};
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) {
    copyFrom(other);
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
MyVector<T>::~MyVector() {
    free();
}

template<typename T>
void MyVector<T>::push(const T& object) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = object.clone();
}

template<typename T>
void MyVector<T>::push(T* pointer) {
    if (!pointer) throw invalid_argument("Cannot push a null pointer");

    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = pointer;
}

template<typename T>
void MyVector<T>::remove(const size_t index) {
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
size_t MyVector<T>::getSize() const {
    return size;
}


template<typename T>
bool MyVector<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
T* MyVector<T>::operator[](size_t index) {
    if (index >= size) throw out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T* MyVector<T>::operator[](size_t index) const {
    if (index >= size) throw out_of_range("Index out of range");
    return data[index];
}

template<typename T>
ostream& operator<<(ostream& os, const MyVector<T>& myVector) {
    for (size_t i = 0; i < myVector.size; i++) {
        os << *myVector.data[i] << endl;
    }
    return os;
}

template<typename T>
istream& operator>>(istream& is, MyVector<T>& myVector) {
    for (size_t i = 0; i < myVector.size; i++) {
        is >> *myVector.data[i];
    }
    return is;
}