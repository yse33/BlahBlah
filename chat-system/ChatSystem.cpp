#include "ChatSystem.h"
#include "CommandValidator.h"

#include "../commands/ViewChatsCommand.h"
#include "../commands/SelectChatCommand.h"
#include "../commands/SendMessageCommand.h"
#include "../commands/CreateChatCommand.h"
#include "../commands/CreateGroupCommand.h"
#include "../commands/AddUserToGroupCommand.h"
#include "../commands/LeaveGroupCommand.h"
#include "../commands/GroupStatsCommand.h"
#include "../commands/KickFromGroupCommand.h"
#include "../commands/SetGroupAdminCommand.h"
#include "../commands/DeleteUserCommand.h"
#include "../commands/DeleteGroupCommand.h"
#include "../commands/ViewAllChatsCommand.h"

Container<Chat>& ChatSystem::getChats() {
    return chats;
}

Container<User>& ChatSystem::getUsers() {
    return users;
}

User* ChatSystem::getLoggedUser() const {
    return loggedUser;
}

Chat* ChatSystem::getSelectedChat() const {
    return selectedChat;
}

void ChatSystem::setLoggedUser(User* user) {
    loggedUser = user;
}

void ChatSystem::setSelectedChat(Chat* chat) {
    selectedChat = chat;
}

Vector<unsigned int> ChatSystem::getUserChatIds() const {
    Vector<unsigned int> chatIds;
    for (size_t i = 0; i < users.getSize(); i++) {
        Vector<unsigned int> userChats = users[i]->getChats();
        for (size_t j = 0; j < userChats.getSize(); j++) {
            if (!chatIds.contains(userChats[j])) {
                chatIds.push(userChats[j]);
            }
        }
    }
    return chatIds;
}

void ChatSystem::load() {
    fileSystem.readUsers(users, binary);
    Vector<unsigned int> chatIds = getUserChatIds();
    fileSystem.readChats(chats, chatIds, binary);
}

void ChatSystem::save() const {
    if (!users.isEmpty()) fileSystem.writeUsers(users, binary);
    if (!chats.isEmpty()) fileSystem.writeChats(chats, binary);
}

ChatSystem::ChatSystem(MyString filepath, const bool binary) : fileSystem(std::move(filepath)), binary(binary) {
    fileSystem.checkFiles(binary);
    load();
    getCommand();
}

void ChatSystem::getCommand() {
    while (true) {
        MyString commandLine;
        getline(cin, commandLine);

        if (commandLine == "exit") {
            cout << "Exiting..." << endl;
            save();
            break;
        }

        executeCommand(commandLine);
    }
}

void ChatSystem::executeCommand(const MyString& commandLine) {
    Vector args(commandLine.split(' '));
    if (!CommandValidator::validateCommandSyntax(args)) return;

    Command* command = nullptr;

    if (args[0] == "login") {
        if (!CommandValidator::validateUserAuthentication(loggedUser, false)) return;
        login(args[1], args[2]);
    }
    else if (args[0] == "create-account") {
        if (!CommandValidator::validateUserAuthentication(loggedUser, false)) return;
        registerAccount(args[1], args[2]);
    }
    else if (args[0] == "logout") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        logout();
    }
    else if (args[0] == "view-chats") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new ViewChatsCommand(this);
    }
    else if (args[0] == "select-chat") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new SelectChatCommand(this, stoi(args[1].getString()));
    }
    else if (args[0] == "send-message") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;

        const size_t start = args[0].getLength() + 1;
        const MyString message = commandLine.substring(start, commandLine.getLength() - start);
        command = new SendMessageCommand(this, Message(loggedUser->getName(), message));
    }
    else if (args[0] == "create-chat") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new CreateChatCommand(this, args[1]);
    }
    else if (args[0] == "create-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;

        Vector<MyString> participants;
        for (size_t i = 2; i < args.getSize(); i++) {
            participants.push(args[i]);
        }
        command = new CreateGroupCommand(this, args[1], participants);
    }
    else if (args[0] == "add-to-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new AddUserToGroupCommand(this, stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "leave-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new LeaveGroupCommand(this, stoi(args[1].getString()));
    }
    else if (args[0] == "group-stats") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new GroupStatsCommand(this, stoi(args[1].getString()));
    }
    else if (args[0] == "kick-from-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new KickFromGroupCommand(this, stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "set-group-admin") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        command = new SetGroupAdminCommand(this, stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "delete-user") {
        command = new DeleteUserCommand(this, args[1]);
    }
    else if (args[0] == "delete-group") {
        command = new DeleteGroupCommand(this, stoi(args[1].getString()));
    }
    else if (args[0] == "view-all-chats") {
        command = new ViewAllChatsCommand(this);
    }

    if (loggedUser) {
        if (loggedUser->canExecute(command)) {
            if (command) command->execute();
        }
        else {
            cout << "You do not have permission to execute this command!" << endl;
        }
    }
    delete command;
}

void ChatSystem::login(const MyString& username, const MyString& password) {
    User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        handleAccountCreation(username, password);
        return;
    }

    if (user->getPassword() != password) {
        cout << "Invalid password!" << endl;
        return;
    }

    loggedUser = user;
    cout << "Welcome, " << loggedUser->getName() << "!" << endl;
}

void ChatSystem::handleAccountCreation(const MyString& username, const MyString& password) {
    char choice;
    while (true) {
        cout << "Account not found. Create? (y/n)" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 'y':
            case 'Y':
                registerAccount(username, password);
                return;
            case 'n':
            case 'N':
                cout << "Account creation canceled!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }
}

void ChatSystem::registerAccount(const MyString& username, const MyString& password) {
    const User* existingUser = users.getByName(username);
    if (existingUser) {
        cout << "Username already exists. Please choose a different one!" << endl;
        return;
    }

    users.push(User(username, password));
    cout << "Account created!" << endl;

    loggedUser = users.peek();
    cout << "Welcome, " << loggedUser->getName() << "!" << endl;
}

void ChatSystem::logout() {
    cout << "Goodbye, " << loggedUser->getName() << "!" << endl;
    loggedUser = nullptr;
}