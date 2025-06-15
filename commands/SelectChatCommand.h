#pragma once

#include "Command.h"

class SelectChatCommand : public Command {
private:
    unsigned int chatId;
public:
    SelectChatCommand(ChatSystem* chatSystem, unsigned int chatId);

    void execute() override;
};