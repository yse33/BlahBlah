#include "ChatFactory.h"

Chat* ChatFactory::getChat(const int chatType) {
    if (chatType == 0) {
        return new IndividualChat();
    }
    if (chatType == 1) {
        return new GroupChat();
    }
    return nullptr;
}