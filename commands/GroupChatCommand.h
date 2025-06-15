#pragma once

#include "ChatCommand.h"

class GroupChatCommand : public ChatCommand {
public:
    explicit GroupChatCommand(ChatSystem* chatSystem) : ChatCommand(chatSystem) {}
};