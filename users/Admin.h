#pragma once

#include "User.h"

class Admin : public User {
private:
    static unsigned int adminCount;
    unsigned int id = 0;
public:
    Admin() = default;
    Admin(MyString username, MyString password);

    User* clone() const override;

    unsigned int getId() const;

    void serialize(ostream& os, bool binary) const override;
    void deserialize(istream& is, bool binary) override;
};