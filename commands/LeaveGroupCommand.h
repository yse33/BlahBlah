#pragma once

#include "GroupChatCommand.h"

class LeaveGroupCommand : public GroupChatCommand {
private:
    unsigned int groupId;
public:
    LeaveGroupCommand(ChatSystem* chatSystem, unsigned int groupId);

    void execute() override;
    void executeWith(GroupChat *chat) override;
    void executeWith(IndividualChat *chat) override;
};