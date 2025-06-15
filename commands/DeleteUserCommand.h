#pragma once

#include "AdminCommand.h"
#include "ChatCommand.h"
#include "../util/MyString.h"

class DeleteUserCommand : public AdminCommand, public ChatCommand {
private:
    MyString username;
public:
    DeleteUserCommand(ChatSystem* chatSystem, MyString username);

    void execute() override;
    void executeWith(GroupChat* chat) override;
    void executeWith(IndividualChat* chat) override;
};
