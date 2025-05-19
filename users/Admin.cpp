#include "Admin.h"

Admin::Admin(const MyString &username, const MyString &password)
    : User(username, password) {}

//TODO: Add check for unique admin id
Admin::Admin(MyString username, MyString password, const unsigned int id)
    : User(std::move(username), std::move(password)), id(id) {}