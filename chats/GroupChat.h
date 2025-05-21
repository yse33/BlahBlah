#pragma once
#include "Chat.h"

class GroupChat : public Chat {
private:
    MyString name;
    User* admin;
    MyVector<MyString> pendingRequests;
    bool adminApproval;
public:
    explicit GroupChat(MyVector<User*> participants, User* admin);

    MyString getName() const;

    bool isAdminApproval() const;
    void setAdminApproval(bool approval);

    void addPendingRequest(const MyString& request);
    void removePendingRequest(const MyString& request);

    void setAdmin(User* admin);

    void addUser(User* user);
    void kickUser(const User* user);

    bool isGroupChat() const override;
};