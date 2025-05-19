#include "Message.h"
#include "../users/User.h"

Message::Message(User* sender, MyString text, const time_t timestamp)
    : sender(sender), text(std::move(text)), timestamp(timestamp) {}

ostream& operator<<(ostream& os, const Message& message) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", localtime(&message.timestamp));

    os << "[" << buffer << "] " << message.sender->getUsername() << ": " << message.text << endl;
    return os;
}
