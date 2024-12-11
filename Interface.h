#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Dungeon.h"

class Interface {
public:
    Interface(Dungeon* dungeon);

    void drawMap(int floor);
    void displayMessage(const std::wstring& message);

private:
    Dungeon* dungeon;
};

#endif