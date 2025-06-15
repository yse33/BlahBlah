#include "chat-system/ChatSystem.h"

#include <iostream>

using namespace std;

int main() {
    int binary;
    while (true) {
        cout << "Choose file format (0 for text, 1 for binary):" << endl;
        cin >> binary;
        cin.ignore();
        if (binary == 0 || binary == 1) break;
        cout << "Invalid choice. Please try again." << endl;
    }

    ChatSystem chatSystem(MyString("../"), static_cast<bool>(binary));
    return 0;
}
