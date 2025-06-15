#include "User.h"

User::User(MyString username, MyString password)
    : username(std::move(username)), password(std::move(password)) {}

User* User::clone() const {
    return new User(*this);
}

MyString User::getName() const {
    return username;
}

MyString User::getPassword() const {
    return password;
}

const Vector<unsigned int>& User::getChats() const {
    return chats;
}

void User::addChat(const unsigned int chatId) {
    chats.push(chatId);
}

void User::removeChat(const unsigned int chatId) {
    chats.remove(chatId);
}

void User::serialize(ostream &os, const bool binary) const {
    if (!binary) {
        os << "0" << endl;
        os << username << endl;
        os << password << endl;
        os << chats.getSize() << endl;
        for (size_t i = 0; i < chats.getSize(); i++) {
            os << chats[i] << endl;
        }
    }
    else {
        const int type = 0;
        os.write(reinterpret_cast<const char*>(&type), sizeof(type));

        const size_t usernameLength = username.getLength();
        os.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));
        os.write(username.getString(), static_cast<std::streamsize>(usernameLength));

        const size_t passwordLength = password.getLength();
        os.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
        os.write(password.getString(), static_cast<std::streamsize>(passwordLength));

        const size_t chatCount = chats.getSize();
        os.write(reinterpret_cast<const char*>(&chatCount), sizeof(chatCount));
        for (size_t i = 0; i < chatCount; i++) {
            os.write(reinterpret_cast<const char*>(&chats[i]), sizeof(chats[i]));
        }
    }
}

void User::deserialize(istream &is, const bool binary) {
    if (!binary) {
        is >> username;
        is >> password;
        size_t chatCount;
        is >> chatCount;
        for (size_t i = 0; i < chatCount; i++) {
            unsigned int chatId;
            is >> chatId;
            is.ignore();
            chats.push(chatId);
        }
    }
    else {
        size_t usernameLength;
        is.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));
        char* usernameBuffer = new char[usernameLength + 1];
        is.read(usernameBuffer, static_cast<std::streamsize>(usernameLength));
        usernameBuffer[usernameLength] = '\0';
        username = MyString(usernameBuffer);
        delete[] usernameBuffer;

        size_t passwordLength;
        is.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
        char* passwordBuffer = new char[passwordLength + 1];
        is.read(passwordBuffer, static_cast<std::streamsize>(passwordLength));
        passwordBuffer[passwordLength] = '\0';
        password = MyString(passwordBuffer);
        delete[] passwordBuffer;

        size_t chatCount;
        is.read(reinterpret_cast<char*>(&chatCount), sizeof(chatCount));
        for (size_t i = 0; i < chatCount; i++) {
            unsigned int chatId;
            is.read(reinterpret_cast<char*>(&chatId), sizeof(chatId));
            chats.push(chatId);
        }
    }
}

bool User::canExecute(Command* command) {
    return true;
}

bool User::canExecute(AdminCommand* command) {
    return false;
}