#pragma once

#include "Command.h"

class IndividualChat;
class GroupChat;

class ChatCommand : public virtual Command {
public:
    explicit ChatCommand(ChatSystem* chatSystem) : Command(chatSystem) {}
    virtual void executeWith(IndividualChat* chat) = 0;
    virtual void executeWith(GroupChat* chat) = 0;
};
