#include "IndividualChat.h"
#include "../users/User.h"

IndividualChat::IndividualChat(Vector<MyString> participants) : Chat(std::move(participants)) {}

Chat* IndividualChat::clone() const {
    return new IndividualChat(*this);
}

MyString IndividualChat::getFullName() const {
    return participants[0] + "-" + participants[1];
}

void IndividualChat::addParticipant(const MyString& username) {
    cout << participants.getSize() << endl;
    if (participants.getSize() >= 2) {
        throw std::runtime_error("Individual chat can only have two participants.");
    }
    participants.push(username);
}

MyString IndividualChat::getName(const User* loggedUser) const {
    if (participants[0] == loggedUser->getName()) {
        return participants[1];
    }
    return participants[0];
}

void IndividualChat::serialize(ostream& os, const bool binary) const {
    if (!binary) {
        os << "0" << endl;
        os << id << endl;
        os << participants.getSize() << endl;
        for (size_t i = 0; i < participants.getSize(); i++) {
            os << participants[i] << endl;
        }
        os << messages.getSize() << endl;
        for (size_t i = 0; i < messages.getSize(); i++) {
            messages[i].serialize(os, binary);
        }
    }
    else {
        os.write("0", 1);

        os.write(reinterpret_cast<const char*>(&id), sizeof(id));

        const size_t participantCount = participants.getSize();
        os.write(reinterpret_cast<const char*>(&participantCount), sizeof(participantCount));
        for (size_t i = 0; i < participantCount; i++) {
            size_t participantLength = participants[i].getLength();
            os.write(reinterpret_cast<const char*>(&participantLength), sizeof(participantLength));
            os.write(participants[i].getString(), static_cast<std::streamsize>(participantLength));
        }

        const size_t messageCount = messages.getSize();
        os.write(reinterpret_cast<const char*>(&messageCount), sizeof(messageCount));
        for (size_t i = 0; i < messageCount; i++) {
            messages[i].serialize(os, binary);
        }
    }
}

void IndividualChat::deserialize(istream& is, const bool binary) {
    if (!binary) {
        is >> id;
        is.ignore();

        size_t participantCount;
        is >> participantCount;
        is.ignore();
        for (size_t i = 0; i < participantCount; i++) {
            MyString participant;
            getline(is, participant);
            participants.push(participant);
        }

        size_t messageCount;
        is >> messageCount;
        is.ignore();
        for (size_t i = 0; i < messageCount; i++) {
            Message message;
            message.deserialize(is, binary);
            messages.push(message);
        }
    }
    else {
        is.read(reinterpret_cast<char*>(&id), sizeof(id));

        size_t participantCount;
        is.read(reinterpret_cast<char*>(&participantCount), sizeof(participantCount));
        for (size_t i = 0; i < participantCount; i++) {
            size_t participantLength;
            is.read(reinterpret_cast<char*>(&participantLength), sizeof(participantLength));
            char* participantBuffer = new char[participantLength + 1];
            is.read(participantBuffer, static_cast<std::streamsize>(participantLength));
            participantBuffer[participantLength] = '\0';
            participants.push(MyString(participantBuffer));
            delete[] participantBuffer;
        }

        size_t messageCount;
        is.read(reinterpret_cast<char*>(&messageCount), sizeof(messageCount));
        for (size_t i = 0; i < messageCount; i++) {
            Message message;
            message.deserialize(is, binary);
            messages.push(message);
        }
    }
}