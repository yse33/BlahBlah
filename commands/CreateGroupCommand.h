#pragma once

#include "Command.h"
#include "../util/MyString.h"

class CreateGroupCommand : public Command {
private:
    MyString groupName;
    Vector<MyString> participants;
public:
    CreateGroupCommand(ChatSystem* chatSystem, MyString groupName, Vector<MyString> participants);

    void execute() override;
};
