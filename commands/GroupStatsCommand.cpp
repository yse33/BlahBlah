#include "GroupStatsCommand.h"

#include "../chat-system/ChatSystem.h"

GroupStatsCommand::GroupStatsCommand(ChatSystem* chatSystem, unsigned int groupId)
    : Command(chatSystem), ChatCommand(chatSystem), groupId(groupId) {}

void GroupStatsCommand::execute() {
    Chat* chat = chatSystem->getChats().getById(groupId);
    if (!chat) {
        cout << "Chat with ID " << groupId << " does not exist!" << endl;
        return;
    }

    chat->execute(this);
}

void GroupStatsCommand::executeWith(IndividualChat* chat) {
    cout << "Chat with ID " << groupId << " is not a group chat!" << endl;
}

void GroupStatsCommand::executeWith(GroupChat* chat) {
    cout << chat->getName(chatSystem->getLoggedUser()) << ":" << endl;
    cout << chat->getParticipants().getSize() << " members" << endl;
    cout << chat->getMessages().getSize() << " messages" << endl;
}