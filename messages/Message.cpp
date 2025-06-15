#include "Message.h"
#include "../users/User.h"

Message::Message(MyString sender, MyString text, const time_t timestamp)
    : sender(std::move(sender)), text(std::move(text)), timestamp(timestamp) {}

void Message::serialize(ostream& os, const bool binary) const {
    if (!binary) {
        os << timestamp << endl;
        os << sender << endl;
        os << text << endl;
    }
    else {
        os.write(reinterpret_cast<const char*>(&timestamp), sizeof(timestamp));

        const size_t senderLength = sender.getLength();
        os.write(reinterpret_cast<const char*>(&senderLength), sizeof(senderLength));
        os.write(sender.getString(), static_cast<std::streamsize>(senderLength));

        const size_t textLength = text.getLength();
        os.write(reinterpret_cast<const char*>(&textLength), sizeof(textLength));
        os.write(text.getString(), static_cast<std::streamsize>(textLength));
    }
}

void Message::deserialize(istream& is, const bool binary) {
    if (!binary) {
        is >> timestamp;
        is.ignore();
        getline(is, sender);
        getline(is, text);
    }
    else {
        is.read(reinterpret_cast<char*>(&timestamp), sizeof(timestamp));

        size_t senderLength;
        is.read(reinterpret_cast<char*>(&senderLength), sizeof(senderLength));
        char* senderBuffer = new char[senderLength + 1];
        is.read(senderBuffer, static_cast<std::streamsize>(senderLength));
        senderBuffer[senderLength] = '\0';
        sender = MyString(senderBuffer);
        delete[] senderBuffer;

        size_t textLength;
        is.read(reinterpret_cast<char*>(&textLength), sizeof(textLength));
        char* textBuffer = new char[textLength + 1];
        is.read(textBuffer, static_cast<std::streamsize>(textLength));
        textBuffer[textLength] = '\0';
        text = MyString(textBuffer);
        delete[] textBuffer;
    }
}

ostream& operator<<(ostream& os, const Message& message) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", localtime(&message.timestamp));

    os << "[" << buffer << "] " << message.sender << ": " << message.text << endl;
    return os;
}
