#include "AddUserToGroupCommand.h"

#include "../chat-system/ChatSystem.h"

AddUserToGroupCommand::AddUserToGroupCommand(ChatSystem* chatSystem, unsigned int groupId, MyString username)
    : Command(chatSystem), GroupChatCommand(chatSystem), groupId(groupId), username(std::move(username)) {}

void AddUserToGroupCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        cout << "Chat with ID " << groupId << " does not exist!" << endl;
        return;
    }

    chat->execute(this);
}

void AddUserToGroupCommand::executeWith(GroupChat* chat) {
    User* user = chatSystem->getUsers().getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    if (chat->isParticipant(user->getName())) {
        cout << "User is already a participant in this chat!" << endl;
        return;
    }

    chat->addParticipant(user->getName());
    user->addChat(chat->getId());
}
void AddUserToGroupCommand::executeWith(IndividualChat* chat) {
    cout << "Cannot add a user to an individual chat using a group command." << endl;
}