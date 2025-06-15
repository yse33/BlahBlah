#include "UserFactory.h"

User* UserFactory::getUser(const int userType) {
    if (userType == 0) {
        return new User();
    }
    if (userType == 1) {
        return new Admin();
    }
    return nullptr;
}