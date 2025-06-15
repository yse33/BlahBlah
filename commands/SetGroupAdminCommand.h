#pragma once

#include "GroupChatCommand.h"
#include "../util/MyString.h"

class SetGroupAdminCommand : public GroupChatCommand {
private:
    unsigned int groupId;
    MyString username;
public:
    SetGroupAdminCommand(ChatSystem* chatSystem, unsigned int groupId, MyString username);

    void execute() override;
    void executeWith(GroupChat* chat) override;
    void executeWith(IndividualChat* chat) override;
};
