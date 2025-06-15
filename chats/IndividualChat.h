#pragma once
#include "Chat.h"

class IndividualChat : public Chat {
public:
    IndividualChat() = default;
    explicit IndividualChat(Vector<MyString> participants);

    Chat* clone() const override;

    MyString getFullName() const;

    void addParticipant(const MyString& username) override;
    MyString getName(const User* loggedUser) const override;
    void serialize(ostream& os, bool binary) const override;
    void deserialize(istream& is, bool binary) override;
};