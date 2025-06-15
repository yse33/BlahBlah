#include "SetGroupAdminCommand.h"

#include <utility>

#include "../chat-system/ChatSystem.h"

SetGroupAdminCommand::SetGroupAdminCommand(ChatSystem* chatSystem, unsigned int groupId, MyString username)
    : Command(chatSystem), GroupChatCommand(chatSystem), groupId(groupId), username(std::move(username)) {}

void SetGroupAdminCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        cout << "Chat with ID " << groupId << " does not exist!" << endl;
        return;
    }

    chat->execute(this);
}

void SetGroupAdminCommand::executeWith(GroupChat* chat) {
    const User* user = chatSystem->getUsers().getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    if (!chat->isParticipant(user->getName())) {
        cout << "User is not a participant in this chat!" << endl;
        return;
    }

    if (chat->getAdmin() != chatSystem->getLoggedUser()->getName()) {
        cout << "Only the current admin can set a new admin!" << endl;
        return;
    }

    if (chat->getAdmin() == user->getName()) {
        cout << "User is already an admin!" << endl;
        return;
    }

    chat->setAdmin(username);
}

void SetGroupAdminCommand::executeWith(IndividualChat* chat) {
    cout << "Cannot set admin for an individual chat!" << endl;
}