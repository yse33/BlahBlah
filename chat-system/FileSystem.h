#pragma once

#include "../util/MyString.h"
#include "../util/Container.hpp"
#include "../chats/IndividualChat.h"

class FileSystem {
private:
    MyString filePath;

    void writeChat(const Chat& chat, bool binary) const;
public:
    explicit FileSystem(const char* path);
    explicit FileSystem(MyString path);

    void checkFiles(bool binary) const;
    void writeUsers(const Container<User>& users, bool binary) const;
    void writeChats(const Container<Chat>& chats, bool binary) const;
    void readUsers(Container<User>& users, bool binary) const;
    void readChats(Container<Chat>& chats, Vector<unsigned int>& chatIds, bool binary) const;
};
