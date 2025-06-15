#pragma once

#include "AdminCommand.h"

class ViewAllChatsCommand : public AdminCommand {
public:
    explicit ViewAllChatsCommand(ChatSystem* chatSystem);

    void execute() override;
};