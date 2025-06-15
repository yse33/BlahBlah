#include "DeleteUserCommand.h"

#include <utility>

#include "../chat-system/ChatSystem.h"

DeleteUserCommand::DeleteUserCommand(ChatSystem* chatSystem, MyString username)
    : Command(chatSystem), AdminCommand(chatSystem), ChatCommand(chatSystem), username(std::move(username)) {
}

void DeleteUserCommand::execute() {
    if (!chatSystem->getLoggedUser()->canExecute(this)) {
        cout << "You do not have permission to execute this command!" << endl;
        return;
    }

    const User* user = chatSystem->getUsers().getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    for (size_t i = 0; i < user->getChats().getSize(); i++) {
        Chat* chat = chatSystem->getChats().getById(user->getChats()[i]);
        chat->execute(this);
    }
    chatSystem->getUsers().removeByName(user->getName());
}

void DeleteUserCommand::executeWith(GroupChat* chat) {
    chat->kickParticipant(username);
}

void DeleteUserCommand::executeWith(IndividualChat* chat) {
    chatSystem->getChats().removeById(chat->getId());
}
