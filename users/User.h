#pragma once

#include "../util/MyString.h"
#include "../util/MyVector.hpp"

class User {
protected:
    MyString username;
    MyString password;
    //TODO: Replace vector with a Chat class
    MyVector<MyString> messages;
public:
    User() = default;
    User(MyString username, MyString password);

    virtual ~User() = default;

    MyString getUsername() const;

    void receiveMessage(const MyString& message);
};