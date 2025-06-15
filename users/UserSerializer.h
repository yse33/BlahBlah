#pragma once

#include <iostream>
#include "User.h"
#include "Admin.h"

class UserSerializer {
private:
    ostream& os;
    istream& is;
public:
    explicit UserSerializer(ostream& os, istream& is);

    void serialize(const User* user) const;
    void deserialize(User* user) const;
};