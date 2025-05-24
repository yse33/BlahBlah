#include "IndividualChat.h"
#include "../users/User.h"

IndividualChat::IndividualChat(MyVector<User> participants) : Chat(std::move(participants)) {}

Chat* IndividualChat::clone() const {
    return new IndividualChat(*this);
}

MyString IndividualChat::getFullName() const {
    return participants[0]->getUsername() + "-" + participants[1]->getUsername();
}

bool IndividualChat::isGroupChat() const {
    return false;
}

MyString IndividualChat::getName(const User& loggedUser) const {
    if (participants[0]->getUsername() == loggedUser.getUsername()) {
        return participants[1]->getUsername();
    }
    return participants[0]->getUsername();
}
