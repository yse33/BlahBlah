#pragma once

#include "GroupChatCommand.h"
#include "../util/MyString.h"

class AddUserToGroupCommand : public GroupChatCommand {
private:
    unsigned int groupId;
    MyString username;
public:
    AddUserToGroupCommand(ChatSystem* chatSystem, unsigned int groupId, MyString username);

    void execute() override;
    void executeWith(IndividualChat* chat) override;
    void executeWith(GroupChat* chat) override;
};
