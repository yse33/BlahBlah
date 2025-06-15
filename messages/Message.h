#pragma once

#include "../util/MyString.h"
#include <ctime>

class User;

class Message {
private:
    MyString sender;
    MyString text;
    time_t timestamp = time(nullptr);
public:
    Message() = default;
    Message(MyString sender, MyString text, time_t timestamp = time(nullptr));

    ~Message() = default;

    MyString getSender() const;

    void serialize(ostream& os, bool binary) const;
    void deserialize(istream& is, bool binary);

    friend ostream& operator<<(ostream& os, const Message& message);
};
