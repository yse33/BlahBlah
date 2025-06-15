#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 8;

    void resize(size_t newCapacity);
    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other) noexcept;
    void free();
public:
    Vector();
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    size_t getSize() const;
    bool isEmpty() const;
    void clear();

    void push(const T& value);
    void remove(const T& value);
    void removeAt(size_t index);
    bool contains(const T& value) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
};

template<typename T>
void Vector<T>::resize(const size_t newCapacity) {
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other) noexcept {
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

template<typename T>
void Vector<T>::free() {
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template<typename T>
Vector<T>::Vector() {
    data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    free();
}

template<typename T>
size_t Vector<T>::getSize() const {
    return size;
}

template<typename T>
bool Vector<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void Vector<T>::clear() {
    free();
    capacity = 8;
    data = new T[capacity];
}

template<typename T>
void Vector<T>::push(const T& value) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

template<typename T>
void Vector<T>::remove(const T& value) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == value) {
            removeAt(i);
            return;
        }
    }
    throw std::invalid_argument("Value not found in vector");
}

template<typename T>
void Vector<T>::removeAt(const size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
bool Vector<T>::contains(const T& value) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}