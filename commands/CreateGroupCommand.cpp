#include "CreateGroupCommand.h"

#include "../chat-system/ChatSystem.h"

CreateGroupCommand::CreateGroupCommand(ChatSystem* chatSystem, MyString groupName, Vector<MyString> participants)
    : Command(chatSystem), groupName(std::move(groupName)), participants(std::move(participants)) {}

void CreateGroupCommand::execute() {
    if (participants.getSize() < 2) {
        cout << "At least two participants are required to create a group chat!" << endl;
        return;
    }

    for (size_t i = 0; i < participants.getSize(); i++) {
        const User* user = chatSystem->getUsers().getByName(participants[i]);
        if (!user) {
            cout << "User with username " << participants[i] << " does not exist!" << endl;
            return;
        }
        if (user->getName() == chatSystem->getLoggedUser()->getName()) {
            cout << "You cannot add yourself to a group chat!" << endl;
            return;
        }
    }

    participants.push(chatSystem->getLoggedUser()->getName());
    chatSystem->getChats().push(new GroupChat(groupName, participants, chatSystem->getLoggedUser()->getName()));

    for (size_t i = 0; i < participants.getSize(); i++) {
        User* user = chatSystem->getUsers().getByName(participants[i]);
        user->addChat(chatSystem->getChats().peek()->getId());
    }

    cout << "Group chat " << chatSystem->getChats().peek()->getName(chatSystem->getLoggedUser()) << " created!" << endl;
}