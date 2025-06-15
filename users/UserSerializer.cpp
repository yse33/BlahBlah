// #include "UserSerializer.h"
//
// #include "UserFactory.h"
//
// UserSerializer::UserSerializer(ostream& os, istream& is) : os(os), is(is) {}
//
// void UserSerializer::serialize(const User* user) const {
//     if (!user) return;
//
//     const Admin *admin = dynamic_cast<const Admin *>(user);
//     if (admin) {
//         os << "1" << endl;
//         os << admin->getId() << endl;
//     } else {
//         os << "0" << endl;
//     }
//
//     os << user->getName() << endl;
//     os << user->getPassword() << endl;
//     os << user->getChats().getSize() << endl;
//     for (size_t i = 0; i < user->getChats().getSize(); ++i) {
//         os << user->getChats()[i]->getId() << endl;
//     }
// }
//
// void UserSerializer::deserialize(User* user) const {
//     if (!user) return;
//
//     int isAdmin;
//     is >> isAdmin;
//     is.ignore();
//
//     user = UserFactory::getUser(isAdmin);
//     if (!user) throw std::runtime_error("Invalid user type specified!");
//
//     unsigned int id;
//     is >> id;
//     is.ignore();
//
//     MyString name, password;
//     getline(is, name);
//     getline(is, password);
//
//     user->setId(id);
//     user->setName(name);
//     user->setPassword(password);
//
//     size_t chatCount;
//     is >> chatCount;
//     is.ignore();
//
//     for (size_t i = 0; i < chatCount; ++i) {
//         unsigned int chatId;
//         is >> chatId;
//         is.ignore();
//         user->addChat(chatId);
//     }
// }