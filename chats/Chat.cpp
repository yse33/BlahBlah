#include "Chat.h"
#include "../users/User.h"

unsigned int Chat::chatCount = 0;

Chat::Chat(MyVector<User*> participants) : participants(std::move(participants)) {
    id = ++chatCount;
}

unsigned int Chat::getId() const {
    return id;
}

const MyVector<User*>& Chat::getParticipants() const {
    return participants;
}

void Chat::addMessage(const Message& message) {
    messages.push(message);
}

void Chat::showMessages() const {
    for (size_t i = 0; i < messages.getSize(); i++) {
        cout << messages[i];
    }
}