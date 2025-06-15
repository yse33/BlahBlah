#include "MyString.h"

#include <cstring>
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
    moveFrom(std::move(other));
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
        moveFrom(std::move(other));
    }
    return *this;
}

MyString::~MyString() {
    free();
}

MyString* MyString::clone() const {
    return new MyString(*this);
}

size_t MyString::getLength() const {
    return size;
}

bool MyString::isEmpty() const {
    return size == 0;
}

const char* MyString::getString() const {
    return str ? str : "";
}

MyString MyString::substring(const size_t start, const size_t length) const {
    if (start >= size) throw out_of_range("Start index out of range");
    if (start + length > size) throw out_of_range("Substring exceeds string length");

    MyString result;
    result.size = length;
    result.capacity = length + 1;
    result.str = new char[result.capacity];
    strncpy(result.str, str + start, length);
    result.str[length] = '\0';
    return result;
}

Vector<MyString> MyString::split(const char delimiter) const {
    Vector<MyString> result;
    size_t start = 0;

    for (size_t i = 0; i < size; i++) {
        if (str[i] == delimiter) {
            if (i > start) {
                result.push(substring(start, i - start));
            }
            start = i + 1;
        }
    }

    if (start < size) {
        result.push(substring(start, size - start));
    }

    return result;
}

void MyString::lowercase() const {
    if (!str) return;

    for (size_t i = 0; i < size; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}

MyString MyString::toLowercase() const {
    MyString result(*this);
    result.lowercase();
    return result;
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

ostream& operator<<(ostream& os, const MyString& myString) {
    os << (myString.str ? myString.str : "");
    return os;
}

istream& operator>>(istream& is, MyString& myString) {
    char buffer[1024];
    is >> buffer;
    myString.free();
    myString = std::move(MyString(buffer));
    return is;
}

istream& getline(istream& is, MyString& myString) {
    char buffer[1024];
    is.getline(buffer, sizeof(buffer));
    myString.free();
    myString = std::move(MyString(buffer));
    return is;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    return strcmp(lhs.getString(), rhs.getString()) == 0;
}

bool operator==(const MyString& lhs, const char* rhs) {
    return strcmp(lhs.getString(), rhs) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
    return !(lhs == rhs);
}

bool operator!=(const MyString& lhs, const char* rhs) {
    return !(lhs == rhs);
}