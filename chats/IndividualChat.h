#pragma once
#include "Chat.h"

class IndividualChat : public Chat {
public:
    explicit IndividualChat(MyVector<User> participants);

    Chat* clone() const override;

    MyString getFullName() const;

    bool isGroupChat() const override;
    MyString getName(const User& loggedUser) const override;
};