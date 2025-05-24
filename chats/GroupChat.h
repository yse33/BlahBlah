#pragma once
#include "Chat.h"

class GroupChat : public Chat {
private:
    MyString name;
    User* admin = nullptr;
    MyVector<MyString> pendingRequests;
    bool adminApproval = false;
public:
    explicit GroupChat(MyString  name, MyVector<User> participants, User* admin);

    Chat* clone() const override;

    bool isAdminApproval() const;
    void setAdminApproval(bool approval);

    void addPendingRequest(const MyString& request);
    void removePendingRequest(const MyString& request);

    void setAdmin(User* admin);

    void addUser(User* user);
    void kickUser(const User* user);

    MyString getName(const User& loggedUser) const override;
    bool isGroupChat() const override;
};