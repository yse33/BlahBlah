#pragma once

#include "FileSystem.h"
#include "../users/User.h"
#include "../users/Admin.h"
#include "../chats/Chat.h"
#include "../chats/GroupChat.h"

class ChatSystem {
private:
    FileSystem fileSystem;
    Container<Chat> chats;
    Container<User> users;
    User* loggedUser = nullptr;
    Chat* selectedChat = nullptr;
    const bool binary;

    Vector<unsigned int> getUserChatIds() const;
    void load();
    void save() const;

    void getCommand();
    void executeCommand(const MyString& commandLine);

    void login(const MyString& username, const MyString& password);
    void handleAccountCreation(const MyString& username, const MyString& password);
    void registerAccount(const MyString& username, const MyString& password);
    void logout();
public:
    explicit ChatSystem(MyString filepath, bool binary);

    ~ChatSystem() = default;

    Container<Chat>& getChats();
    Container<User>& getUsers();
    User* getLoggedUser() const;
    Chat* getSelectedChat() const;
    void setLoggedUser(User* user);
    void setSelectedChat(Chat* chat);;
};
