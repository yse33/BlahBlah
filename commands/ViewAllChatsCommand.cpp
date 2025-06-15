#include "ViewAllChatsCommand.h"

#include "../chat-system/ChatSystem.h"

ViewAllChatsCommand::ViewAllChatsCommand(ChatSystem* chatSystem)
    : Command(chatSystem), AdminCommand(chatSystem) {}

void ViewAllChatsCommand::execute() {
    if (!chatSystem->getLoggedUser()->canExecute(this)) {
        cout << "You do not have permission to execute this command!" << endl;
        return;
    }

    for (size_t i = 0; i < chatSystem->getChats().getSize(); i++) {
        cout << chatSystem->getChats()[i]->getName(chatSystem->getLoggedUser()) << endl;
    }
}