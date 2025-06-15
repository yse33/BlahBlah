#include "ViewChatsCommand.h"

#include "../chat-system/ChatSystem.h"

ViewChatsCommand::ViewChatsCommand(ChatSystem* chatSystem) : Command(chatSystem) {}

void ViewChatsCommand::execute() {
    const Vector<unsigned int>& chatIds = chatSystem->getLoggedUser()->getChats();
    if (chatIds.isEmpty()) {
        cout << "No chats available!" << endl;
        return;
    }

    cout << "Chats:" << endl;
    for (size_t i = 0; i < chatIds.getSize(); i++) {
        const Chat* chat = chatSystem->getChats().getById(chatIds[i]);
        cout << chat->getId() << " | " << chat->getName(chatSystem->getLoggedUser()) << endl;
    }
}