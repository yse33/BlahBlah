#pragma once

#include "Command.h"
#include "../messages/Message.h"

class SendMessageCommand : public Command {
private:
    Message message;
public:
    SendMessageCommand(ChatSystem* chatSystem, const Message& message);

    void execute() override;
};