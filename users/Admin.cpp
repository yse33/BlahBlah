#include "Admin.h"

#include <utility>

unsigned int Admin::adminCount = 0;

Admin::Admin(MyString username, MyString password)
    : User(std::move(username), std::move(password)) {
    id = ++adminCount;
}

//TODO: Add check for unique admin id
Admin::Admin(MyString username, MyString password, const unsigned int id)
    : User(std::move(username), std::move(password)), id(id) {}