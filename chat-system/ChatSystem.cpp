#include "ChatSystem.h"
#include "CommandValidator.h"

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
        viewChats();
    }
    else if (args[0] == "select-chat") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        selectChat(stoi(args[1].getString()));
    }
    else if (args[0] == "send-message") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;

        const size_t start = args[0].getLength() + 1;
        const MyString message = commandLine.substring(start, commandLine.getLength() - start);
        sendMessage(Message(loggedUser->getName(), message));
    }
    else if (args[0] == "create-chat") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        createIndividualChat(args[1]);
    }
    else if (args[0] == "create-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;

        Vector<MyString> participants;
        for (size_t i = 2; i < args.getSize(); i++) {
            participants.push(args[i]);
        }
        createGroupChat(args[1], participants);
    }
    else if (args[0] == "add-to-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        addToGroupChat(stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "leave-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        leaveGroupChat(stoi(args[1].getString()));
    }
    else if (args[0] == "kick-from-group") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        kickFromGroupChat(stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "set-group-admin") {
        if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        setGroupChatAdmin(stoi(args[1].getString()), args[2]);
    }
    else if (args[0] == "delete-user") {
        //if (!CommandValidator::validateUserAuthenticationAndAuthorization(loggedUser, ADMIN)) return;
        deleteUser(args[1]);
    }
    else if (args[0] == "delete-group") {
        //if (!CommandValidator::validateUserAuthenticationAndAuthorization(loggedUser, ADMIN)) return;
        deleteGroupChat(stoi(args[1].getString()));
    }
    else if (args[0] == "view-all-chats") {
        //if (!CommandValidator::validateUserAuthentication(loggedUser)) return;
        viewAllChats();
    }
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

void ChatSystem::viewChats() const {
    Vector<unsigned int> chatIds = loggedUser->getChats();
    if (chatIds.isEmpty()) {
        cout << "No chats available!" << endl;
        return;
    }

    cout << "Chats:" << endl;
    for (size_t i =0; i < chatIds.getSize(); i++) {
        const Chat* chat = chats.getById(chatIds[i]);
        cout << chat->getId() << " | " << chat->getName(loggedUser) << endl;
    }
}

void ChatSystem::selectChat(const unsigned int chatId) {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    if (!chat->isParticipant(loggedUser->getName())) {
        cout << "You are not a participant in this chat!" << endl;
        return;
    }

    selectedChat = chat;
    cout << "Chat " << selectedChat->getName(loggedUser) << ":" << endl;
    selectedChat->showMessages();
}

void ChatSystem::sendMessage(const Message& message) const {
    if (!selectedChat) {
        cout << "No chat selected!" << endl;
        return;
    }

    selectedChat->addMessage(message);
}

void ChatSystem::createIndividualChat(const MyString &username) {
    User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    if (username == loggedUser->getName()) {
        cout << "You cannot create a chat with yourself!" << endl;
        return;
    }

    Vector<MyString> participants;
    participants.push(loggedUser->getName());
    participants.push(username);

    chats.push(new IndividualChat(participants));

    loggedUser->addChat(chats.peek()->getId());
    user->addChat(chats.peek()->getId());

    cout << "Chat with " << username << " created!" << endl;
}


void ChatSystem::createGroupChat(const MyString& name, Vector<MyString>& participants) {
    if (participants.getSize() < 2) {
        cout << "At least two participants are required to create a group chat!" << endl;
        return;
    }

    for (size_t i = 0; i < participants.getSize(); i++) {
        const User* user = users.getByName(participants[i]);
        if (!user) {
            cout << "User with username " << participants[i] << " does not exist!" << endl;
            return;
        }
        if (user->getName() == loggedUser->getName()) {
            cout << "You cannot add yourself to a group chat!" << endl;
            return;
        }
    }

    participants.push(loggedUser->getName());
    chats.push(new GroupChat(name, participants, loggedUser->getName()));

    for (size_t i = 0; i < participants.getSize(); i++) {
        User* user = users.getByName(participants[i]);
        user->addChat(chats.peek()->getId());
    }

    cout << "Group chat " << chats.peek()->getName(loggedUser) << " created!" << endl;
}

void ChatSystem::addToGroupChat(const unsigned int chatId, const MyString& username) const {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
    if (!groupChat) {
        cout << "Chat with ID " << chatId << " is not a group chat!" << endl;
        return;
    }

    if (chat->isParticipant(user->getName())) {
        cout << "User is already a participant in this chat!" << endl;
        return;
    }

    groupChat->addParticipant(user->getName());
    user->addChat(chatId);
}

void ChatSystem::leaveGroupChat(const unsigned int chatId) const {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
    if (!groupChat) {
        cout << "Chat with ID " << chatId << " is not a group chat!" << endl;
        return;
    }

    if (!groupChat->isParticipant(loggedUser->getName())) {
        cout << "You are not a participant in this group chat!" << endl;
        return;
    }

    groupChat->kickParticipant(loggedUser->getName());
    loggedUser->removeChat(chatId);
}

void ChatSystem::kickFromGroupChat(const unsigned int chatId, const MyString& username) const {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
    if (!groupChat) {
        cout << "Chat with ID " << chatId << " is not a group chat!" << endl;
        return;
    }

    if (chat->isParticipant(user->getName())) {
        cout << "User is not a participant in this chat!" << endl;
        return;
    }

    groupChat->kickParticipant(user->getName());
    user->removeChat(chatId);
}

void ChatSystem::setGroupChatAdmin(const unsigned int chatId, const MyString& username) const {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    const User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
    if (!groupChat) {
        cout << "Chat with ID " << chatId << " is not a group chat!" << endl;
        return;
    }

    if (chat->isParticipant(user->getName())) {
        cout << "User is not a participant in this chat!" << endl;
        return;
    }

    groupChat->setAdmin(user->getName());
}

void ChatSystem::deleteUser(const MyString& username) {
    const User* user = users.getByName(username);
    if (!user) {
        cout << "User with username " << username << " does not exist!" << endl;
        return;
    }

    for (size_t i = 0; i < user->getChats().getSize(); i++) {
        Chat* chat = chats.getById(user->getChats()[i]);
        if (chat) {
            GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
            if (groupChat) {
                groupChat->kickParticipant(user->getName());
            } else {
                chats.removeById(user->getChats()[i]);
            }
        }
    }
    users.removeByName(user->getName());
}

void ChatSystem::deleteGroupChat(const unsigned int chatId) {
    Chat* chat = chats.getById(chatId);
    if (!chat) {
        cout << "Chat with ID " << chatId << " does not exist!" << endl;
        return;
    }

    const GroupChat* groupChat = dynamic_cast<GroupChat*>(chat);
    if (!groupChat) {
        cout << "Chat with ID " << chatId << " is not a group chat!" << endl;
        return;
    }

    for (size_t i = 0; i < groupChat->getParticipants().getSize(); i++) {
        User* user = users.getByName(groupChat->getParticipants()[i]);
        if (user) {
            user->removeChat(chatId);
        }
    }
    chats.removeById(chatId);
}

void ChatSystem::viewAllChats() const {
    for (size_t i = 0; i < chats.getSize(); i++) {
        cout << chats[i]->getName(loggedUser) << endl;
    }
}