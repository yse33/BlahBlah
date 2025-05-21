#pragma once

#include "../util/MyVector.hpp"
#include "../users/User.h"
#include "Message.h"

class Chat {
protected:
    static unsigned int chatCount;
    unsigned int id = 0;
    MyVector<User*> participants;
    MyVector<Message> messages;
public:
    explicit Chat(MyVector<User*> participants);

    unsigned int getId() const;
    const MyVector<User*>& getParticipants() const;

    void addMessage(const Message& message);
    void showMessages() const;

    virtual bool isGroupChat() const = 0;

    virtual ~Chat() = default;
};
