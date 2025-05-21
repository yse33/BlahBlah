#pragma once
#include "Chat.h"

class IndividualChat : public Chat {
public:
    explicit IndividualChat(MyVector<User*> participants);

    bool isGroupChat() const override;
};