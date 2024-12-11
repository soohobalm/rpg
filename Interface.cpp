#include "Interface.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

Interface::Interface(Dungeon* dungeon) : dungeon(dungeon) {
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        std::cerr << "Error setting console mode to UTF-16." << std::endl;
    }
}

void Interface::drawMap(int floor) {
    system("cls");

    std::pair<int, int> playerPos = dungeon->getPlayerPosition(floor);

    for (int y = 0; y < Dungeon::MAP_HEIGHT; ++y) {
        for (int x = 0; x < Dungeon::MAP_WIDTH; ++x) {
            if (x == playerPos.first && y == playerPos.second) {
                std::wcout << Dungeon::PLAYER;
            }
            else {
                std::wcout << dungeon->getMapElement(x, y, floor);
            }
        }
        std::wcout << std::endl;
    }
}

void Interface::displayMessage(const std::wstring& message) {
    std::wcout << message << std::endl;
}