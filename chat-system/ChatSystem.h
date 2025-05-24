#pragma once

#include "../users/User.h"
#include "../users/Admin.h"
#include "../chats/Chat.h"

class ChatSystem {
private:
    MyVector<Chat> chats;
    MyVector<User> users;
    MyVector<Admin> admins;
    User* loggedUser = nullptr;
    Chat* selectedChat = nullptr;

    void getCommand();
    void executeCommand(const MyString& choice);
    void handleAccountCreation(const MyString& username, const MyString& password);
public:
    ChatSystem() = default;
    ChatSystem(const MyVector<Chat>& chats, const MyVector<User>& users, const MyVector<Admin>& admins);

    ~ChatSystem() = default;

    User* getUserByUsername(const MyString &username);

    void login(const MyString& username, const MyString& password);
    void registerAccount(const MyString& username, const MyString& password);
    void logout();

    void viewChats() const;
    void selectChat(unsigned int id);
    void sendMessage(const Message& message) const;
    void createGroupChat(const MyString& name, const MyVector<User>& participants);
    void addToGroupChat(unsigned int id, const MyString& username);
    void leaveGroupChat(unsigned int id);
    void kickFromGroupChat(unsigned int id, const MyString& username);
    void setGroupChatAdmin(unsigned int id, const MyString& username);
    void viewGroupChatStats(unsigned int id) const;

    void deleteUser(const MyString& username);
    void deleteGroupChat(unsigned int id);
    void viewAllChats();
};
