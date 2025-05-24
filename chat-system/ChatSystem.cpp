#include "ChatSystem.h"

#include "../chats/GroupChat.h"
#include "../chats/IndividualChat.h"

ChatSystem::ChatSystem(const MyVector<Chat>& chats, const MyVector<User>& users, const MyVector<Admin>& admins)
    : chats(chats), users(users), admins(admins) {
    getCommand();
}

void ChatSystem::getCommand() {
    while (true) {
        MyString input;
        getline(cin, input);

        if (input == "exit") {
            cout << "Exiting..." << endl;
            break;
        }

        executeCommand(input);
    }
}

void ChatSystem::executeCommand(const MyString& choice) {
    MyVector commands(choice.split(' '));
    if (commands.getSize() == 0) {
        cout << "Invalid command!" << endl;
        return;
    }

    if (*commands[0] == "login") {
        if (commands.getSize() != 3) {
            cout << "Usage: login <username> <password>" << endl;
            return;
        }
        login(*commands[1], *commands[2]);
    } else if (*commands[0] == "logout") {
        if (commands.getSize() != 1) {
            cout << "Usage: logout" << endl;
            return;
        }
        logout();
    } else if (*commands[0] == "viewChats") {
        if (commands.getSize() != 1) {
            cout << "Usage: viewChats" << endl;
            return;
        }
        viewChats();
    } else if (*commands[0] == "selectChat") {
        if (commands.getSize() != 2) {
            cout << "Usage: selectChat <chat_id>" << endl;
            return;
        }
        selectChat(stoi(commands[1]->getString()));
    }
    else if (*commands[0] == "sendMessage") {
        if (commands.getSize() != 2) {
            cout << "Usage: sendMessage <message>" << endl;
            return;
        }
        sendMessage(Message(loggedUser, *commands[1]));
    } else if (*commands[0] == "createGroupChat") {
        if (commands.getSize() < 3) {
            cout << "Usage: createGroupChat <name> <user1> <user2> ..." << endl;
            return;
        }
        MyVector<User> participants;
        for (size_t i = 2; i < commands.getSize(); i++) {
            participants.push(getUserByUsername(*commands[i]));
        }
        createGroupChat(*commands[1], participants);
    } else if (*commands[0] == "addToGroupChat") {
        if (commands.getSize() != 3) {
            cout << "Usage: addToGroupChat <chat_id> <username>" << endl;
            return;
        }
        addToGroupChat(stoi(commands[1]->getString()), *commands[2]);
    } else if (*commands[0] == "leaveGroupChat") {
        if (commands.getSize() != 2) {
            cout << "Usage: leaveGroupChat <chat_id>" << endl;
            return;
        }
        leaveGroupChat(stoi(commands[1]->getString()));
    } else if (*commands[0] == "kickFromGroupChat") {
        if (commands.getSize() != 3) {
            cout << "Usage: kickFromGroupChat <chat_id> <username>" << endl;
            return;
        }
        kickFromGroupChat(stoi(commands[1]->getString()), *commands[2]);
    } else if (*commands[0] == "setGroupChatAdmin") {
        if (commands.getSize() != 3) {
            cout << "Usage: setGroupChatAdmin <chat_id> <username>" << endl;
            return;
        }
        setGroupChatAdmin(stoi(commands[1]->getString()), *commands[2]);
    } else if (*commands[0] == "deleteUser") {
        if (commands.getSize() != 2) {
            cout << "Usage: deleteUser <username>" << endl;
            return;
        }
        deleteUser(*commands[1]);
    } else if (*commands[0] == "deleteGroupChat") {
        if (commands.getSize() != 2) {
            cout << "Usage: deleteGroupChat <chat_id>" << endl;
            return;
        }
        deleteGroupChat(stoi(commands[1]->getString()));
    } else if (*commands[0] == "viewAllChats") {
        if (commands.getSize() != 1) {
            cout << "Usage: viewAllChats" << endl;
            return;
        }
        viewAllChats();
    } else {
        cout << "Invalid command!" << endl;
    }
}

User* ChatSystem::getUserByUsername(const MyString &username) {
    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i]->getUsername() == username) {
            return users[i];
        }
    }
    return nullptr;
}

void ChatSystem::login(const MyString& username, const MyString& password) {
    if (loggedUser) {
        cout << "You are already logged in as " << loggedUser->getUsername() << "." << endl;
        return;
    }

    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i]->getUsername() == username) {
            if (users[i]->getPassword() != password) {
                cout << "Invalid password!" <<  endl;
                return;
            }

            loggedUser = users[i];
            cout << "Welcome, " << loggedUser->getUsername() << "!" << endl;
            return;
        }
    }
    handleAccountCreation(username, password);
}

void ChatSystem::handleAccountCreation(const MyString& username, const MyString& password) {
    char choice;
    while (true) {
        cout << "Account not found. Create? (y/n)" << endl;
        cin >> choice;
        switch (choice) {
            case 'y':
            case 'Y':
                registerAccount(username, password);
                return;
            case 'n':
            case 'N':
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void ChatSystem::registerAccount(const MyString& username, const MyString& password) {
    if (getUserByUsername(username)) {
        cout << "Username already exists. Please choose a different one." << endl;
        return;
    }

    users.push(User(username, password));
    cout << "Account created!" << endl;
}

void ChatSystem::logout() {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    cout << "Goodbye, " << loggedUser->getUsername() << "!" << endl;
    loggedUser = nullptr;
}

void ChatSystem::viewChats() const {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    const size_t chatCount = loggedUser->getChats().getSize();

    if (chatCount == 0) {
        cout << "No chats available." << endl;
        return;
    }

    cout << "Chats:" << endl;
    for (size_t i = 0; i < chatCount; i++) {
        cout << loggedUser->getChats()[i]->getName(*loggedUser) << endl;
    }
}

void ChatSystem::selectChat(const unsigned int id) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    for (size_t i = 0; i < loggedUser->getChats().getSize(); i++) {
        if (loggedUser->getChats()[i]->getId() == id) {
            selectedChat = loggedUser->getChats()[i];
            cout << "Chat " << selectedChat->getName(*loggedUser) << ":" << endl;
            selectedChat->showMessages();
            return;
        }
    }

    cout << "Chat not found." << endl;
}

void ChatSystem::sendMessage(const Message& message) const {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    if (!selectedChat) {
        cout << "No chat selected." << endl;
        return;
    }

    selectedChat->addMessage(message);
}

void ChatSystem::createGroupChat(const MyString& name, const MyVector<User>& participants) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    if (name == "") {
        cout << "Chat name cannot be empty." << endl;
        return;
    }

    if (participants.getSize() < 2) {
        cout << "At least two participants are required to create a group chat." << endl;
        return;
    }

    chats.push(new GroupChat(name, participants, loggedUser));
    cout << "Group chat created!" << endl;
}

void ChatSystem::addToGroupChat(const unsigned int id, const MyString& username) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    if (!selectedChat) {
        cout << "No chat selected." << endl;
        return;
    }

    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getId() == id) {
            GroupChat* groupChat = dynamic_cast<GroupChat*>(chats[i]);
            groupChat->addUser(getUserByUsername(username));
            cout << "User added to group chat!" << endl;
            return;
        }
    }

    cout << "Group chat not found." << endl;
}

void ChatSystem::leaveGroupChat(const unsigned int id) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    if (!selectedChat) {
        cout << "No chat selected." << endl;
        return;
    }

    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getId() == id) {
            GroupChat* groupChat = dynamic_cast<GroupChat*>(chats[i]);
            groupChat->kickUser(loggedUser);
            cout << "You left the group chat!" << endl;
            return;
        }
    }

    cout << "Group chat not found." << endl;
}

void ChatSystem::kickFromGroupChat(const unsigned int id, const MyString& username) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    if (!selectedChat) {
        cout << "No chat selected." << endl;
        return;
    }

    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getId() == id) {
            GroupChat* groupChat = dynamic_cast<GroupChat*>(chats[i]);
            groupChat->kickUser(getUserByUsername(username));
            cout << "User kicked from group chat!" << endl;
            return;
        }
    }

    cout << "Group chat not found." << endl;
}

void ChatSystem::setGroupChatAdmin(const unsigned int id, const MyString& username) {
    if (!loggedUser) {
         cout << "You are not logged in." <<  endl;
        return;
    }

    if (!selectedChat) {
         cout << "No chat selected." <<  endl;
        return;
    }

    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getId() == id) {
            GroupChat* groupChat = dynamic_cast<GroupChat*>(chats[i]);
            groupChat->setAdmin(getUserByUsername(username));
            cout << "User set as admin!" << endl;
            return;
        }
    }

    cout << "Group chat not found." << endl;
}

void ChatSystem::deleteUser(const MyString& username) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i]->getUsername() == username) {
            users.remove(i);
            cout << "User deleted!" << endl;
            return;
        }
    }

    cout << "User not found." << endl;
}

void ChatSystem::deleteGroupChat(const unsigned int id) {
    if (!loggedUser) {
        cout << "You are not logged in." << endl;
        return;
    }

    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getId() == id) {
            chats.remove(i);
            cout << "Group chat deleted!" << endl;
            return;
        }
    }

    cout << "Group chat not found." << endl;
}

void ChatSystem::viewAllChats() {
    for (size_t i = 0; i < chats.getSize(); i++) {
        cout << chats[i]->getId() << ": ";
        if (chats[i]->isGroupChat()) {
            cout << chats[i]->getName(*loggedUser) << endl;
        } else {
            const IndividualChat* individualChat = dynamic_cast<IndividualChat*>(chats[i]);
            cout << individualChat->getFullName() << endl;
        }
    }
}