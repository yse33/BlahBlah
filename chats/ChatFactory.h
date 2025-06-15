#pragma once

#include "Chat.h"
#include "IndividualChat.h"
#include "GroupChat.h"

class ChatFactory {
public:
    ChatFactory() = default;

    static Chat* getChat(int chatType);
};