#include "Dungeon.h"
#include "Interface.h"
#include <iostream>
#include <algorithm>

bool Dungeon::Room::isInside(int px, int py) const {
    return px >= x && px < x + width && py >= y && py < y + height;
}

Dungeon::Dungeon(int numFloors) : numFloors(numFloors) {
    maps.resize(numFloors, std::vector<std::vector<char>>(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, EMPTY)));
    rooms.resize(numFloors);
    playerPositions.resize(numFloors, { -1, -1 });
    downStairPositions.resize(numFloors, { -1, -1 });
}

Dungeon::~Dungeon() {}

void Dungeon::generate(int seed) {
    generator.seed(seed);

    for (int floor = 0; floor < numFloors; ++floor) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                maps[floor][y][x] = WALL;
            }
        }

        generateRooms(floor);
        connectRooms(floor);
        placeStairs(floor);

        if (floor == 0) {
            playerPositions[floor] = { rooms[floor][0].x + 1, rooms[floor][0].y + 1 };
        }
    }
}

void Dungeon::generateRooms(int floor) {
    rooms[floor].clear();
    for (int i = 0; i < MAX_ROOM_ATTEMPTS; ++i) {
        int w = generator() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
        int h = generator() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
        int x = generator() % (MAP_WIDTH - w - 1) + 1;
        int y = generator() % (MAP_HEIGHT - h - 1) + 1;

        Room newRoom(x, y, w, h);

        bool canPlace = true;
        for (const auto& existingRoom : rooms[floor]) {
            if (newRoom.x < existingRoom.x + existingRoom.width &&
                newRoom.x + newRoom.width > existingRoom.x &&
                newRoom.y < existingRoom.y + existingRoom.height &&
                newRoom.y + newRoom.height > existingRoom.y) {
                canPlace = false;
                break;
            }
        }

        if (canPlace) {
            for (int ry = y; ry < y + h; ++ry) {
                for (int rx = x; rx < x + w; ++rx) {
                    maps[floor][ry][rx] = EMPTY;
                }
            }
            rooms[floor].push_back(newRoom);
        }
    }
}

void Dungeon::connectRooms(int floor) {
    for (size_t i = 0; i < rooms[floor].size() - 1; ++i) {
        int x1 = rooms[floor][i].x + rooms[floor][i].width / 2;
        int y1 = rooms[floor][i].y + rooms[floor][i].height / 2;
        int x2 = rooms[floor][i + 1].x + rooms[floor][i + 1].width / 2;
        int y2 = rooms[floor][i + 1].y + rooms[floor][i + 1].height / 2;

        int cornerX = (generator() % 2 == 0) ? x1 : x2;
        int cornerY = (cornerX == x1) ? y2 : y1;

        for (int x = std::min(x1, cornerX); x <= std::max(x1, cornerX); ++x) {
            maps[floor][y1][x] = EMPTY;
        }
        for (int y = std::min(y1, cornerY); y <= std::max(y1, cornerY); ++y) {
            maps[floor][y][cornerX] = EMPTY;
        }
        for (int x = std::min(x2, cornerX); x <= std::max(x2, cornerX); ++x) {
            maps[floor][y2][x] = EMPTY;
        }
        for (int y = std::min(y2, cornerY); y <= std::max(y2, cornerY); ++y) {
            maps[floor][y][cornerX] = EMPTY;
        }
    }
}

void Dungeon::placeStairs(int floor) {
    if (floor < numFloors - 1) {
        int roomIndex;
        do {
            roomIndex = generator() % rooms[floor].size();
        } while (roomIndex == 0);

        int stairX = rooms[floor][roomIndex].x + generator() % rooms[floor][roomIndex].width;
        int stairY = rooms[floor][roomIndex].y + generator() % rooms[floor][roomIndex].height;

        maps[floor][stairY][stairX] = DOWNSTAIR;
        downStairPositions[floor] = { stairX, stairY };
    }
    else {
        downStairPositions[floor] = { -1, -1 };
    }
}

bool Dungeon::movePlayer(int dx, int dy, int currentFloor, Player& player) {
    int newX = playerPositions[currentFloor].first + dx;
    int newY = playerPositions[currentFloor].second + dy;

    if (isValidPosition(newX, newY, currentFloor) && !isWall(newX, newY, currentFloor)) {
        playerPositions[currentFloor].first = newX;
        playerPositions[currentFloor].second = newY;
        return true;
    }
    else {
        std::wcout << L"막다른 길입니다." << std::endl;
        return false;
    }
}

std::pair<int, int> Dungeon::getPlayerPosition(int floor) const {
    if (isValidPosition(0, 0, floor)) {
        return playerPositions[floor];
    }
    else {
        return { -1, -1 };
    }
}

void Dungeon::setPlayerPosition(int x, int y, int floor) {
    if (isValidPosition(x, y, floor)) {
        playerPositions[floor] = { x, y };
    }
    else {
        std::cerr << "Error: setPlayerPosition called with invalid floor number: " << floor << std::endl;
    }
}

bool Dungeon::checkRandomEncounter(int floor) const {
    if (!isValidPosition(0, 0, floor)) {
        return false;
    }
    return generator() % MONSTER_ENCOUNTER_RATE == 0;
}

char Dungeon::checkStairs(int floor) const {
    if (!isValidPosition(0, 0, floor)) {
        return EMPTY;
    }

    int x = playerPositions[floor].first;
    int y = playerPositions[floor].second;

    if (isDownStair(x, y, floor)) {
        return DOWNSTAIR;
    }
    else {
        return EMPTY;
    }
}

bool Dungeon::isDownStair(int x, int y, int floor) const {
    return (floor < numFloors - 1 && x == downStairPositions[floor].first && y == downStairPositions[floor].second);
}

bool Dungeon::changeFloor(int& currentFloor, char stairType) {
    if (!isValidPosition(0, 0, currentFloor)) {
        return false;
    }

    if (stairType == DOWNSTAIR && (playerPositions[currentFloor] == downStairPositions[currentFloor])) {
        int nextFloor = currentFloor + 1;

        if (nextFloor < numFloors) {
            currentFloor = nextFloor;
            return true;
        }
        else {
            std::cerr << "Error: Stair position not found." << std::endl;
            return false;
        }
    }
    else {
        std::wcout << L"계단 위에 있지 않습니다." << std::endl;
        return false;
    }
    return false;
}

bool Dungeon::isValidPosition(int x, int y, int floor) const {
    return floor >= 0 && floor < numFloors && x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}

bool Dungeon::isWall(int x, int y, int floor) const {
    return !isValidPosition(x, y, floor) || maps[floor][y][x] == WALL;
}

char Dungeon::getMapElement(int x, int y, int floor) const {
    return maps[floor][y][x];
}