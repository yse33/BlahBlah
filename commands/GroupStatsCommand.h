#pragma once

#include "ChatCommand.h"

class GroupStatsCommand : public ChatCommand {
private:
    unsigned int groupId;
public:
    GroupStatsCommand(ChatSystem* chatSystem, unsigned int groupId);

    void execute() override;
    void executeWith(IndividualChat* chat) override;
    void executeWith(GroupChat* chat) override;
};