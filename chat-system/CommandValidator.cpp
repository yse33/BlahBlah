#include "CommandValidator.h"

bool CommandValidator::validateCommandSyntax(const Vector<MyString>& args) {
    if (args.isEmpty()) {
        cout << "No command provided!" << endl;
        return false;
    }

    if (args[0] == "login") {
        if (args.getSize() != 3) {
            cout << "Usage: login <username> <password>" << endl;
            return false;
        }
    }
    else if (args[0] == "create-account") {
        if (args.getSize() != 3) {
            cout << "Usage: create-account <username> <password>" << endl;
            return false;
        }
    }
    else if (args[0] == "logout") {
        if (args.getSize() != 1) {
            cout << "Usage: logout" << endl;
            return false;
        }
    }
    else if (args[0] == "view-chats") {
        if (args.getSize() != 1) {
            cout << "Usage: view-chats" << endl;
            return false;
        }
    }
    else if (args[0] == "select-chat") {
        if (args.getSize() != 2) {
            cout << "Usage: select-chat <chatID>" << endl;
            return false;
        }
    }
    else if (args[0] == "send-message") {
        if (args.getSize() < 2) {
            cout << "Usage: send-message <message>" << endl;
            return false;
        }
    }
    else if (args[0] == "create-chat") {
        if (args.getSize() != 2) {
            cout << "Usage: create-chat <username>" << endl;
            return false;
        }
    }
    else if (args[0] == "create-group") {
        if (args.getSize() < 2) {
            cout << "Usage: create-group <groupName> [participants...]" << endl;
            return false;
        }
    }
    else if (args[0] == "add-to-group") {
        if (args.getSize() != 3) {
            cout << "Usage: add-to-group-chat <chatID> <username>" << endl;
            return false;
        }
    }
    else if (args[0] == "leave-group") {
        if (args.getSize() != 2) {
            cout << "Usage: leave-group <chatID>" << endl;
            return false;
        }
    }
    else if (args[0] == "kick-from-group") {
        if (args.getSize() != 3) {
            cout << "Usage: kick-from-group <chatID> <username>" << endl;
            return false;
        }
    }
    else if (args[0] == "set-group-admin") {
        if (args.getSize() != 3) {
            cout << "Usage: set-group-admin <chatID> <username>" << endl;
            return false;
        }
    }
    else if (args[0] == "group-stats") {
        if (args.getSize() != 2) {
            cout << "Usage: group-stats <chatID>" << endl;
            return false;
        }
    }
    else if (args[0] == "delete-user") {
        if (args.getSize() != 2) {
            cout << "Usage: delete-user <username>" << endl;
            return false;
        }
    }
    else if (args[0] == "delete-group") {
        if (args.getSize() != 2) {
            cout << "Usage: delete-group <chatID>" << endl;
            return false;
        }
    }
    else if (args[0] == "view-all-chats") {
        if (args.getSize() != 1) {
            cout << "Usage: view-all-chats" << endl;
            return false;
        }
    }
    else {
        cout << "Invalid command!" << endl;
        return false;
    }

    return true;
}

bool CommandValidator::validateUserAuthentication(const User* user, const bool desiredLoginState) {
    if (!user == desiredLoginState) {
        if (desiredLoginState) cout << "You are not logged in!" << endl;
        else cout << "You are already logged in!" << endl;
        return false;
    }
    return true;
}

bool CommandValidator::validateUserAuthenticationAndAuthorization(const User* user, const bool requireAdmin) {
    if (!validateUserAuthentication(user)) return false;
    if (requireAdmin) {
        const Admin* admin = dynamic_cast<const Admin*>(user);
        if (!admin) {
            cout << "You do not have permission to perform this action!" << endl;
            return false;
        }
        return true;
    }
    return true;
}