#pragma once

#include "Command.h"
#include "../util/MyString.h"

class CreateChatCommand : public Command {
private:
    MyString username;
public:
    CreateChatCommand(ChatSystem* chatSystem, MyString username);

    void execute() override;
};
