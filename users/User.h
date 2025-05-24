#pragma once

#include "../util/MyString.h"
#include "../chats/Chat.h"

class User {
protected:
    MyString username;
    MyString password;
    MyVector<Chat> chats;
public:
    User() = default;
    User(MyString username, MyString password);

    virtual ~User() = default;

    virtual User* clone() const;

    MyString getUsername() const;
    MyString getPassword() const;
    MyVector<Chat> getChats() const;

    void addChat(Chat* chat);
    void removeChat(const Chat* chat);
};