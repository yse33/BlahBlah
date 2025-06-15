#include "SendMessageCommand.h"

#include "../chat-system/ChatSystem.h"

SendMessageCommand::SendMessageCommand(ChatSystem* chatSystem, const Message& message)
    : Command(chatSystem), message(message) {}

void SendMessageCommand::execute() {
    if (!chatSystem->getSelectedChat()) {
        cout << "No chat selected!" << endl;
        return;
    }

    chatSystem->getSelectedChat()->addMessage(message);
}