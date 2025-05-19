#pragma once

#include "../util/MyString.h"
#include <ctime>

class User;

class Message {
private:
    User* sender = nullptr;
    MyString text;
    time_t timestamp = time(nullptr);
public:
    Message() = default;
    Message(User* sender, MyString text, time_t timestamp = time(nullptr));

    friend ostream& operator<<(ostream& os, const Message& message);

    ~Message() = default;
};
