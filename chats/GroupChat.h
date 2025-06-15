#pragma once

#include "Chat.h"

class GroupChat : public Chat {
private:
    MyString name;
    MyString admin;
    Vector<MyString> pendingRequests;
    bool adminApproval = false;
public:
    GroupChat() = default;
    explicit GroupChat(MyString name, Vector<MyString> participants, MyString admin, bool adminApproval = false);

    Chat* clone() const override;

    MyString getAdmin() const;
    void setAdmin(MyString admin);
    bool isAdminApproval() const;
    void setAdminApproval(bool approval);
    const Vector<MyString>& getPendingRequests() const;

    void addPendingRequest(const MyString& username);
    void removePendingRequest(const MyString& username);

    void kickParticipant(const MyString& username);

    void addParticipant(const MyString& username) override;
    MyString getName(const User* loggedUser) const override;
    void serialize(ostream& os, bool binary) const override;
    void deserialize(istream& is, bool binary) override;
};