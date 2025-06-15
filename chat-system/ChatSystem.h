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

    void viewChats() const;
    void selectChat(unsigned int chatId);
    void sendMessage(const Message& message) const;
    void createIndividualChat(const MyString& username);
    void createGroupChat(const MyString& name, Vector<MyString>& participants);
    void addToGroupChat(unsigned int chatId, const MyString& username) const;
    void leaveGroupChat(unsigned int chatId) const;
    void kickFromGroupChat(unsigned int chatId, const MyString& username) const;
    void setGroupChatAdmin(unsigned int chatId, const MyString& username) const;
    void viewGroupChatStats(unsigned int chatId) const;

    void deleteUser(const MyString& username);
    void deleteGroupChat(unsigned int chatId);
    void viewAllChats() const;
public:
    explicit ChatSystem(MyString filepath, bool binary);

    ~ChatSystem() = default;
};
