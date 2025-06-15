#include "CreateChatCommand.h"

#include <utility>

#include "../chat-system/ChatSystem.h"

CreateChatCommand::CreateChatCommand(ChatSystem* chatSystem, MyString username)
    : Command(chatSystem), username(std::move(username)) {}

void CreateChatCommand::execute() {
    User* user = chatSystem->getUsers().getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    if (username == chatSystem->getLoggedUser()->getName()) {
        cout << "You cannot create a chat with yourself!" << endl;
        return;
    }

    for (size_t i = 0; i < chatSystem->getLoggedUser()->getChats().getSize(); i++) {
        Chat* chat = chatSystem->getChats().getById(chatSystem->getLoggedUser()->getChats()[i]);
        if (chat->getParticipants().getSize() == 2 && chat->isParticipant(username)) {
            cout << "Chat with " << username << " already exists!" << endl;
            return;
        }
    }

    Vector<MyString> participants;
    participants.push(chatSystem->getLoggedUser()->getName());
    participants.push(username);

    chatSystem->getChats().push(new IndividualChat(participants));

    chatSystem->getLoggedUser()->addChat(chatSystem->getChats().peek()->getId());
    user->addChat(chatSystem->getChats().peek()->getId());

    cout << "Chat with " << username << " created!" << endl;
}