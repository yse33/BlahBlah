#pragma once

#include "Command.h"

class ViewChatsCommand : public Command {
public:
    explicit ViewChatsCommand(ChatSystem* chatSystem);

    void execute() override;
};