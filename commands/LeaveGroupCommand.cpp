#include "LeaveGroupCommand.h"

#include "../chat-system/ChatSystem.h"

LeaveGroupCommand::LeaveGroupCommand(ChatSystem* chatSystem, const unsigned int groupId)
    : Command(chatSystem), GroupChatCommand(chatSystem), groupId(groupId) {}

void LeaveGroupCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        cout << "Chat with ID " << groupId << " does not exist!" << endl;
        return;
    }

    chat->execute(this);
}

void LeaveGroupCommand::executeWith(GroupChat* chat) {
    if (!chat->isParticipant(chatSystem->getLoggedUser()->getName())) {
        cout << "You are not a participant in this chat!" << endl;
        return;
    }

    chat->kickParticipant(chatSystem->getLoggedUser()->getName());
    chatSystem->getLoggedUser()->removeChat(chat->getId());
}

void LeaveGroupCommand::executeWith(IndividualChat* chat) {
    cout << "Cannot leave an individual chat using a group command." << endl;
}