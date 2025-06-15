#pragma once

#include "User.h"
#include "Admin.h"

class UserFactory {
public:
    UserFactory() = default;

    static User* getUser(int userType);
};
