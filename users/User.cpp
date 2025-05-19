#include "User.h"

User::User(MyString username, MyString password)
    : username(std::move(username)), password(std::move(password)) {}

MyString User::getUsername() const {
    return username;
}

void User::receiveMessage(const MyString& message) {
    messages.push(message);
}