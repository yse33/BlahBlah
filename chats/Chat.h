#pragma once

#include "../util/MyVector.hpp"
#include "Message.h"

class User;

class Chat {
protected:
    static unsigned int chatCount;
    unsigned int id = 0;
    MyVector<User> participants;
    MyVector<Message> messages;
public:
    explicit Chat(MyVector<User> participants);

    virtual ~Chat() = default;

    virtual Chat* clone() const = 0;

    unsigned int getId() const;
    const MyVector<User>& getParticipants() const;

    void addMessage(const Message& message);
    void showMessages() const;

    virtual bool isGroupChat() const = 0;
    virtual MyString getName(const User& loggedUser) const = 0;
};
