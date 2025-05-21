#pragma once

#include "../util/MyString.h"
#include "../util/MyVector.hpp"

class Chat;

class User {
protected:
    MyString username;
    MyString password;
    MyVector<Chat*> chats;
public:
    User() = default;
    User(MyString username, MyString password);

    MyString getUsername() const;

    void addChat(Chat* chat);
    void removeChat(const Chat* chat);

    virtual ~User() = default;
};