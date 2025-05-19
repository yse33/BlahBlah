#pragma once

#include <iostream>

using namespace std;

class MyString {
private:
    char* str = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void copyFrom(const MyString& other);
    void moveFrom(MyString&& other) noexcept;
    void free();
    void resize(size_t newCapacity);
public:
    MyString() = default;

    explicit MyString(const char* str);

    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;

    ~MyString();

    friend ostream& operator<<(ostream& os, const MyString& myString);
    friend istream& operator>>(istream& is, MyString& myString);

    MyString operator+(const MyString& other) const;
    MyString operator+(const char* other) const;
    char& operator[](size_t index);
    char operator[](size_t index) const;

    size_t getLength() const;
    const char* getString() const;
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);