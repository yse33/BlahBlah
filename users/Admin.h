#pragma once

#include "User.h"

class Admin : public User {
private:
    static unsigned int adminCount;
    unsigned int id = 0;
public:
    Admin() = default;
    Admin(const MyString &username, const MyString &password);
    Admin(MyString username, MyString password, unsigned int id);
};