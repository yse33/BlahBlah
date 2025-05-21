#include "User.h"
#include "../chats/Chat.h"

User::User(MyString username, MyString password)
    : username(std::move(username)), password(std::move(password)) {}

MyString User::getUsername() const {
    return username;
}

void User::addChat(Chat* chat) {
    for (size_t i = 0; i < chats.getSize(); ++i) {
        if (chats[i]->getId() == chat->getId()) {
            return;
        }
    }
    chats.push(chat);
}

void User::removeChat(const Chat* chat) {
    for (size_t i = 0; i < chats.getSize(); ++i) {
        if (chats[i]->getId() == chat->getId()) {
            chats.remove(i);
            return;
        }
    }
    cout << "Chat not found." << endl;
}