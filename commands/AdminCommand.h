#pragma once

#include "Command.h"

class AdminCommand : public virtual Command {
public:
    explicit AdminCommand(ChatSystem* chatSystem) : Command(chatSystem) {}
};