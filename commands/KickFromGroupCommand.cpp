#include "KickFromGroupCommand.h"

#include "../chat-system/ChatSystem.h"

KickFromGroupCommand::KickFromGroupCommand(ChatSystem* chatSystem, const unsigned int groupId, MyString username)
    : Command(chatSystem), GroupChatCommand(chatSystem), groupId(groupId), username(std::move(username)) {}

void KickFromGroupCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        std::cout << "Chat with ID " << groupId << " does not exist!" << std::endl;
        return;
    }

    chat->execute(this);
}

void KickFromGroupCommand::executeWith(GroupChat* chat) {
    User* user = chatSystem->getUsers().getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    if (!chat->isParticipant(user->getName())) {
        cout << "User is not a participant in this chat!" << endl;
        return;
    }

    if (chat->getAdmin() == user->getName()) {
        cout << "Cannot kick the admin of the group!" << endl;
        return;
    }

    if (chat->getAdmin() != chatSystem->getLoggedUser()->getName()) {
        cout << "Only the admin can kick participants!" << endl;
        return;
    }

    chat->kickParticipant(username);
    user->removeChat(chat->getId());
}

void KickFromGroupCommand::executeWith(IndividualChat* chat) {
    std::cout << "Cannot kick a user from an individual chat!" << std::endl;
}