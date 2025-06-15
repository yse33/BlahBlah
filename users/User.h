#pragma once

#include "../util/MyString.h"
#include "../util/Container.hpp"
#include "../chats/Chat.h"
#include "../commands/AdminCommand.h"
#include "../commands/Command.h"

class User {
protected:
    MyString username;
    MyString password;
    Vector<unsigned int> chats;
public:
    User() = default;
    User(MyString username, MyString password);

    virtual ~User() = default;

    virtual User* clone() const;

    MyString getName() const;
    MyString getPassword() const;
    const Vector<unsigned int>& getChats() const;

    void addChat(unsigned int chatId);
    void removeChat(unsigned int chatId);

    virtual void serialize(ostream& os, bool binary) const;
    virtual void deserialize(istream& is, bool binary);
    virtual bool canExecute(Command* command);
    virtual bool canExecute(AdminCommand* command);
};
