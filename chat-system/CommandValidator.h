#pragma once

#include "../util/MyString.h"
#include "../users/User.h"
#include "../users/Admin.h"

class CommandValidator {
public:
    static bool validateCommandSyntax(const Vector<MyString>& args);
    static bool validateUserAuthentication(const User* user, bool desiredLoginState = true);
    static bool validateUserAuthenticationAndAuthorization(const User* user, bool requireAdmin = false);
};