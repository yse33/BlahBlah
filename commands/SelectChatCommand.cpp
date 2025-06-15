#include "SelectChatCommand.h"

#include "../chat-system/ChatSystem.h"

SelectChatCommand::SelectChatCommand(ChatSystem* chatSystem, const unsigned int chatId) : Command(chatSystem), chatId(chatId) {}

void SelectChatCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    if (!chat->isParticipant(chatSystem->getLoggedUser()->getName())) {
        cout << "You are not a participant in this chat!" << endl;
        return;
    }

    chatSystem->setSelectedChat(chat);
    cout << "Chat " << chatSystem->getSelectedChat()->getName(chatSystem->getLoggedUser()) << ":" << endl;
    chatSystem->getSelectedChat()->showMessages();
}