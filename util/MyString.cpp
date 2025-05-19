#include "MyString.h"

#include <cstring>
#include <algorithm>
#include <stdexcept>

void MyString::copyFrom(const MyString& other) {
    size = other.size;
    capacity = other.capacity;
    str = new char[capacity];
    strcpy(str, other.str);
}

void MyString::moveFrom(MyString&& other) noexcept {
    str = other.str;
    size = other.size;
    capacity = other.capacity;

    other.str = nullptr;
    other.size = 0;
    other.capacity = 0;
}

void MyString::free() {
    delete[] str;
    str = nullptr;
    size = 0;
    capacity = 0;
}

void MyString::resize(const size_t newCapacity) {
    if (newCapacity <= capacity) return;

    char* newStr = new char[newCapacity];
    if (str) {
        strcpy(newStr, str);
        delete[] str;
    }
    str = newStr;
    capacity = newCapacity;
}

MyString::MyString(const char* str) {
    if (str) {
        size = strlen(str);
        capacity = size + 1;
        this->str = new char[capacity];
        strcpy(this->str, str);
    }
}

MyString::MyString(const MyString& other) {
    copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept {
    moveFrom(move(other));
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(move(other));
    }
    return *this;
}

MyString::~MyString() {
    free();
}

ostream& operator<<(ostream& os, const MyString& myString) {
    os << (myString.str ? myString.str : "");
    return os;
}

istream& operator>>(istream& is, MyString& myString) {
    char buffer[1024];
    is >> buffer;
    myString.free();
    myString = move(MyString(buffer));
    return is;
}

size_t MyString::getLength() const {
    return size;
}

const char* MyString::getString() const {
    return str ? str : "";
}

MyString MyString::operator+(const MyString& other) const {
    MyString result;
    result.size = size + other.size;
    result.capacity = result.size + 1;
    result.str = new char[result.capacity];
    if (str) strcpy(result.str, str);
    if (other.str) strcat(result.str, other.str);
    return result;
}

MyString MyString::operator+(const char* other) const {
    MyString result;
    result.size = size + strlen(other);
    result.capacity = result.size + 1;
    result.str = new char[result.capacity];
    if (str) strcpy(result.str, str);
    if (other) strcat(result.str, other);
    return result;
}

char& MyString::operator[](const size_t index) {
    if (index >= size) throw out_of_range("Index out of range");
    return str[index];
}

char MyString::operator[](const size_t index) const {
    if (index >= size) throw out_of_range("Index out of range");
    return str[index];
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    return strcmp(lhs.getString(), rhs.getString()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
    return !(lhs == rhs);
}