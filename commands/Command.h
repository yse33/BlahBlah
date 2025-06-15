#pragma once

class ChatSystem;

class Command {
protected:
    ChatSystem* chatSystem = nullptr;
public:
    explicit Command(ChatSystem* chatSystem) : chatSystem(chatSystem) {}
    virtual void execute() = 0;
    virtual ~Command() = default;
};