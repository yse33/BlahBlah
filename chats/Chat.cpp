#include "Chat.h"
#include "../users/User.h"

unsigned int Chat::chatCount = 0;

Chat::Chat() {
    id = chatCount++;
}

Chat::Chat(Vector<MyString> participants) : participants(std::move(participants)) {
    id = chatCount++;
}

unsigned int Chat::getId() const {
    return id;
}

const Vector<MyString>& Chat::getParticipants() const {
    return participants;
}

const Vector<Message>& Chat::getMessages() const {
    return messages;
}

bool Chat::isParticipant(const MyString& username) const {
    for (size_t i = 0; i < participants.getSize(); i++) {
        if (participants[i] == username) {
            return true;
        }
    }
    return false;
}

void Chat::addMessage(const Message& message) {
    messages.push(message);
}

void Chat::showMessages() const {
    if (messages.isEmpty()) {
        cout << "No messages in this chat." << endl;
    } else {
        for (size_t i = 0; i < messages.getSize(); i++) {
            cout << messages[i] << endl;
        }
    }
}