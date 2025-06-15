#include "FileSystem.h"
#include "../users/User.h"
#include <fstream>
#include <sstream>

#include "../chats/ChatFactory.h"
#include "../users/UserFactory.h"

FileSystem::FileSystem(const char* path) : filePath(path) {}

FileSystem::FileSystem(MyString path) : filePath(std::move(path)) {}

void FileSystem::checkFiles(const bool binary) const {
    if (!binary) {
        ifstream usersFile((filePath + "users.txt").getString());
        if (!usersFile.is_open()) {
            ofstream createUsersFile((filePath + "users.txt").getString());
            if (!createUsersFile.is_open()) {
                throw std::runtime_error("Could not create users file!");
            }
            createUsersFile << "0" << endl;
            createUsersFile.close();
        } else {
            usersFile.close();
        }
    } else {
        ifstream usersFile((filePath + "users.bin").getString(), ios::binary);
        if (!usersFile.is_open()) {
            ofstream createUsersFile((filePath + "users.bin").getString(), ios::binary);
            if (!createUsersFile.is_open()) {
                throw std::runtime_error("Could not create binary users file!");
            }
            size_t size = 0;
            createUsersFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            createUsersFile.close();
        } else {
            usersFile.close();
        }
    }
}

void FileSystem::writeChat(const Chat& chat, const bool binary) const {
    ostringstream filePathStream;
    filePathStream << filePath << "chats_" << chat.getId();
    if (!binary) {
        filePathStream << ".txt";
        ofstream file(filePathStream.str());
        if (file.is_open()) {
            chat.serialize(file, binary);
            file.close();
        } else {
            throw std::runtime_error("Could not open file for writing!");
        }
    }
    else {
        filePathStream << ".bin";
        ofstream file(filePathStream.str(), ios::binary);
        if (file.is_open()) {
            chat.serialize(file, binary);
            file.close();
        } else {
            throw std::runtime_error("Could not open file for writing!");
        }
    }
}

void FileSystem::writeUsers(const Container<User>& users, const bool binary) const {
    if (!binary) {
        ofstream file((filePath + "users.txt").getString());
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing!");
        }

        file << users.getSize() << endl;
        for (size_t i = 0; i < users.getSize(); i++) {
            users[i]->serialize(file, binary);
        }
        file.close();
    }
    else {
        ofstream file((filePath + "users.bin").getString(), ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open binary file for writing!");
        }

        size_t size = users.getSize();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; i++) {
            users[i]->serialize(file, binary);
        }
        file.close();
    }
}

void FileSystem::writeChats(const Container<Chat>& chats, const bool binary) const {
    for (size_t i = 0; i < chats.getSize(); i++) {
        writeChat(*chats[i], binary);
    }
}

void FileSystem::readUsers(Container<User>& users, const bool binary) const {
    if (!binary) {
        ifstream file((filePath + "users.txt").getString());
        if (!file.is_open()) {
            throw std::runtime_error("Could not open users file for reading!");
        }

        size_t size;
        file >> size;
        file.ignore();

        for (size_t i = 0; i < size; i++) {
            int type;
            file >> type;
            file.ignore();

            User* user = UserFactory::getUser(type);
            if (!user) {
                throw std::runtime_error("Unknown user type in file!");
            }

            user->deserialize(file, binary);
            users.push(user);
        }
        file.close();
    }
    else {
        ifstream file((filePath + "users.bin").getString(), ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open binary users file for reading!");
        }

        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; i++) {
            int type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));

            User* user = UserFactory::getUser(type);
            if (!user) {
                throw std::runtime_error("Unknown user type in binary file!");
            }

            user->deserialize(file, binary);
            users.push(user);
        }
        file.close();
    }
}

void FileSystem::readChats(Container<Chat>& chats, Vector<unsigned int> &chatIds, const bool binary) const {
    for (size_t i = 0; i < chatIds.getSize(); i++) {
        ostringstream filePathStream;
        filePathStream << filePath << "chats_" << chatIds[i];
        if (!binary) {
            filePathStream << ".txt";
            ifstream file(filePathStream.str());
            if (!file.is_open()) {
                throw std::runtime_error("Could not open chat file for reading!");
            }

            int type;
            file >> type;
            file.ignore();

            Chat* chat = ChatFactory::getChat(type);
            if (!chat) {
                throw std::runtime_error("Failed to create chat from file!");
            }

            chat->deserialize(file, binary);
            chats.push(chat);

            file.close();
        }
        else {
            filePathStream << ".bin";
            ifstream file(filePathStream.str(), ios::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open binary chat file for reading!");
            }

            int type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));

            Chat* chat = ChatFactory::getChat(type);
            if (!chat) {
                throw std::runtime_error("Failed to create chat from binary file!");
            }

            chat->deserialize(file, binary);
            chats.push(chat);

            file.close();
        }
    }
}
