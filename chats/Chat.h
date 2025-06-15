#pragma once

#include "../util/Container.hpp"
#include "../messages/Message.h"

class User;

class Chat {
protected:
    static unsigned int chatCount;
    unsigned int id = 0;
    Vector<MyString> participants;
    Vector<Message> messages;
public:
    Chat();
    explicit Chat(Vector<MyString> participants);

    virtual ~Chat() = default;

    virtual Chat* clone() const = 0;

    unsigned int getId() const;
    const Vector<MyString>& getParticipants() const;
    const Vector<Message>& getMessages() const;

    bool isParticipant(const MyString& username) const;
    void addMessage(const Message& message);
    void showMessages() const;

    virtual void addParticipant(const MyString& username) = 0;
    virtual MyString getName(const User* loggedUser) const = 0;
    virtual void serialize(ostream& file, bool binary) const = 0;
    virtual void deserialize(istream& file, bool binary) = 0;
};
