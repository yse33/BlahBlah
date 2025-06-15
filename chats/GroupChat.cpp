#include "GroupChat.h"

#include <utility>
#include "../users/User.h"

GroupChat::GroupChat(MyString name, Vector<MyString> participants, MyString admin, const bool adminApproval)
    : Chat(std::move(participants)), name(std::move(name)), admin(std::move(admin)), adminApproval(adminApproval) {}

Chat* GroupChat::clone() const {
    return new GroupChat(*this);
}

MyString GroupChat::getName(const User* loggedUser) const {
    return name;
}

bool GroupChat::isAdminApproval() const {
    return adminApproval;
}

MyString GroupChat::getAdmin() const {
    return admin;
}

void GroupChat::setAdmin(MyString admin) {
    this->admin = std::move(admin);
}

void GroupChat::setAdminApproval(const bool approval) {
    adminApproval = approval;
}

void GroupChat::addPendingRequest(const MyString& username) {
    pendingRequests.push(username);
}

const Vector<MyString>& GroupChat::getPendingRequests() const {
    return pendingRequests;
}

void GroupChat::removePendingRequest(const MyString& username) {
    pendingRequests.remove(username);
}

void GroupChat::addParticipant(const MyString& username) {
    if (adminApproval) {
        pendingRequests.push(username);
    } else {
        participants.push(username);
    }
}

void GroupChat::kickParticipant(const MyString& username) {
    participants.remove(username);
}

void GroupChat::serialize(ostream& os, const bool binary) const {
    if (!binary) {
        os << "1" << endl;
        os << id << endl;
        os << name << endl;
        os << participants.getSize() << endl;
        for (size_t i = 0; i < participants.getSize(); i++) {
            os << participants[i] << endl;
        }
        os << pendingRequests.getSize() << endl;
        for (size_t i = 0; i < pendingRequests.getSize(); i++) {
            os << pendingRequests[i] << endl;
        }
        os << admin << endl;
        os << adminApproval << endl;
        os << messages.getSize() << endl;
        for (size_t i = 0; i < messages.getSize(); i++) {
            messages[i].serialize(os, binary);
        }
    }
    else {
        os.write("1", 1);

        os.write(reinterpret_cast<const char*>(&id), sizeof(id));

        const size_t nameLength = name.getLength();
        os.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        os.write(name.getString(), static_cast<std::streamsize>(nameLength));

        const size_t participantCount = participants.getSize();
        os.write(reinterpret_cast<const char*>(&participantCount), sizeof(participantCount));
        for (size_t i = 0; i < participantCount; i++) {
            size_t participantLength = participants[i].getLength();
            os.write(reinterpret_cast<const char*>(&participantLength), sizeof(participantLength));
            os.write(participants[i].getString(), static_cast<std::streamsize>(participantLength));
        }

        const size_t pendingRequestCount = pendingRequests.getSize();
        os.write(reinterpret_cast<const char*>(&pendingRequestCount), sizeof(pendingRequestCount));
        for (size_t i = 0; i < pendingRequestCount; i++) {
            size_t requestLength = pendingRequests[i].getLength();
            os.write(reinterpret_cast<const char*>(&requestLength), sizeof(requestLength));
            os.write(pendingRequests[i].getString(), static_cast<std::streamsize>(requestLength));
        }

        const size_t adminLength = admin.getLength();
        os.write(reinterpret_cast<const char*>(&adminLength), sizeof(adminLength));
        os.write(admin.getString(), static_cast<std::streamsize>(adminLength));

        os.write(reinterpret_cast<const char*>(&adminApproval), sizeof(adminApproval));

        const size_t messageCount = messages.getSize();
        os.write(reinterpret_cast<const char*>(&messageCount), sizeof(messageCount));
        for (size_t i = 0; i < messageCount; i++) {
            messages[i].serialize(os, binary);
        }
    }
}

void GroupChat::deserialize(istream& is, const bool binary) {
    if (!binary) {
        is >> id;
        is.ignore();

        getline(is, name);

        size_t participantCount;
        is >> participantCount;
        is.ignore();
        for (size_t i = 0; i < participantCount; i++) {
            MyString participant;
            getline(is, participant);
            participants.push(participant);
        }

        size_t pendingRequestCount;
        is >> pendingRequestCount;
        is.ignore();
        for (size_t i = 0; i < pendingRequestCount; i++) {
            MyString request;
            getline(is, request);
            pendingRequests.push(request);
        }

        getline(is, admin);

        is >> adminApproval;
        is.ignore();

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

        size_t nameLength;
        is.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        char* nameBuffer = new char[nameLength + 1];
        is.read(nameBuffer, static_cast<std::streamsize>(nameLength));
        nameBuffer[nameLength] = '\0';
        name = MyString(nameBuffer);
        delete[] nameBuffer;

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

        size_t pendingRequestCount;
        is.read(reinterpret_cast<char*>(&pendingRequestCount), sizeof(pendingRequestCount));
        for (size_t i = 0; i < pendingRequestCount; i++) {
            size_t requestLength;
            is.read(reinterpret_cast<char*>(&requestLength), sizeof(requestLength));
            char* requestBuffer = new char[requestLength + 1];
            is.read(requestBuffer, static_cast<std::streamsize>(requestLength));
            requestBuffer[requestLength] = '\0';
            pendingRequests.push(MyString(requestBuffer));
            delete[] requestBuffer;
        }

        size_t adminLength;
        is.read(reinterpret_cast<char*>(&adminLength), sizeof(adminLength));
        char* adminBuffer = new char[adminLength + 1];
        is.read(adminBuffer, static_cast<std::streamsize>(adminLength));
        adminBuffer[adminLength] = '\0';
        admin = MyString(adminBuffer);
        delete[] adminBuffer;

        is.read(reinterpret_cast<char*>(&adminApproval), sizeof(adminApproval));

        size_t messageCount;
        is.read(reinterpret_cast<char*>(&messageCount), sizeof(messageCount));
        for (size_t i = 0; i < messageCount; i++) {
            Message message;
            message.deserialize(is, binary);
            messages.push(message);
        }
    }
}