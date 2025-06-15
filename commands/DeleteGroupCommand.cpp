#include "DeleteGroupCommand.h"

#include "../chat-system/ChatSystem.h"

DeleteGroupCommand::DeleteGroupCommand(ChatSystem* chatSystem, const unsigned int groupId)
    : Command(chatSystem), AdminCommand(chatSystem), ChatCommand(chatSystem), groupId(groupId) {}

void DeleteGroupCommand::execute() {
    if (!chatSystem->getLoggedUser()->canExecute(this)) {
        cout << "You do not have permission to execute this command!" << endl;
        return;
    }

    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        cout << "Chat with ID " << groupId << " does not exist!" << endl;
        return;
    }

    chat->execute(this);
}

void DeleteGroupCommand::executeWith(IndividualChat* chat) {
    cout << "Chat with ID " << groupId << " is not a group chat!" << endl;
}

void DeleteGroupCommand::executeWith(GroupChat* chat) {
    for (size_t i = 0; i < chat->getParticipants().getSize(); i++) {
        User* user = chatSystem->getUsers().getByName(chat->getParticipants()[i]);
        if (user) {
            user->removeChat(groupId);
        }
    }
    chatSystem->getChats().removeById(groupId);
}