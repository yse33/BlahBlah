#include "Admin.h"

unsigned int Admin::adminCount = 0;

Admin::Admin(MyString username, MyString password)
    : User(std::move(username), std::move(password)) {
    id = adminCount++;
}

User* Admin::clone() const {
    return new Admin(*this);
}

unsigned int Admin::getId() const {
    return id;
}

void Admin::serialize(ostream& os, const bool binary) const {
    if (!binary) {
        os << "1" << endl;
        os << id << endl;
        os << username << endl;
        os << password << endl;
        os << chats.getSize() << endl;
        for (size_t i = 0; i < chats.getSize(); i++) {
            os << chats[i] << endl;
        }
    }
    else {
        const int type = 1;
        os.write(reinterpret_cast<const char*>(&type), sizeof(type));

        os.write(reinterpret_cast<const char*>(&id), sizeof(id));

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

void Admin::deserialize(istream& is, const bool binary) {
    if (!binary) {
        is >> id;
        is.ignore();
        getline(is, username);
        getline(is, password);
        size_t chatCount;
        is >> chatCount;
        is.ignore();
        for (size_t i = 0; i < chatCount; i++) {
            unsigned int chatId;
            is >> chatId;
            is.ignore();
            chats.push(chatId);
        }
    }
    else {
        is.read(reinterpret_cast<char*>(&id), sizeof(id));

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