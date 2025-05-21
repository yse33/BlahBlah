#include "IndividualChat.h"

IndividualChat::IndividualChat(MyVector<User*> participants) : Chat(std::move(participants)) {}

bool IndividualChat::isGroupChat() const {
    return false;
}