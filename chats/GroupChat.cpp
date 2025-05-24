#include "GroupChat.h"
#include "../users/User.h"

#include <utility>

GroupChat::GroupChat(MyString  name, MyVector<User> participants, User* admin)
    : Chat(std::move(participants)), name(std::move(name)), admin(admin), adminApproval(true) {}

Chat* GroupChat::clone() const {
    return new GroupChat(*this);
}

MyString GroupChat::getName(const User& loggedUser) const {
    return name;
}

bool GroupChat::isAdminApproval() const {
    return adminApproval;
}

void GroupChat::setAdminApproval(const bool approval) {
    adminApproval = approval;
}

void GroupChat::addPendingRequest(const MyString& request) {
    pendingRequests.push(request);
}

void GroupChat::removePendingRequest(const MyString& request) {
    for (size_t i = 0; i < pendingRequests.getSize(); ++i) {
        if (*pendingRequests[i] == request) {
            pendingRequests.remove(i);
            break;
        }
    }
}

void GroupChat::setAdmin(User* admin) {
    this->admin = admin;
}

void GroupChat::addUser(User* user) {
    if (adminApproval) {
        pendingRequests.push(user->getUsername());
    } else {
        participants.push(user);
    }
}

void GroupChat::kickUser(const User* user) {
    for (size_t i = 0; i < participants.getSize(); ++i) {
        if (participants[i]->getUsername() == user->getUsername()) {
            participants.remove(i);
            break;
        }
    }
}

bool GroupChat::isGroupChat() const {
    return true;
}