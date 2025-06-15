#pragma once

#include "AdminCommand.h"
#include "ChatCommand.h"

class DeleteGroupCommand : public AdminCommand, public ChatCommand {
private:
    unsigned int groupId;
public:
    DeleteGroupCommand(ChatSystem* chatSystem, unsigned int groupId);

    void execute() override;
    void executeWith(IndividualChat *chat) override;
    void executeWith(GroupChat *chat) override;
};
