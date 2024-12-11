#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <random>
#include <utility>
#include "Player.h"
#include "Monster.h"

class Interface;

class Dungeon {
public:
    Dungeon(int numFloors);
    ~Dungeon();

    void generate(int seed);
    bool movePlayer(int dx, int dy, int currentFloor, Player& player);
    std::pair<int, int> getPlayerPosition(int floor) const;
    void setPlayerPosition(int x, int y, int floor);
    bool checkRandomEncounter(int floor) const;
    char checkStairs(int floor) const;
    bool changeFloor(int& currentFloor, char stairType);
    bool isValidPosition(int x, int y, int floor) const;
    bool isWall(int x, int y, int floor) const;
    std::mt19937& getGenerator() { return generator; }
    char getMapElement(int x, int y, int floor) const;

    static const int MAP_WIDTH = 30;
    static const int MAP_HEIGHT = 10;
    static const char EMPTY = '.';
    static const char WALL = '#';
    static const char PLAYER = '@';
    static const char DOWNSTAIR = '>';

private:
    static const int MAX_ROOM_ATTEMPTS = 20;
    static const int MIN_ROOM_SIZE = 3;
    static const int MAX_ROOM_SIZE = 6;
    static const int MONSTER_ENCOUNTER_RATE = 10;

    int numFloors;
    std::vector<std::vector<std::vector<char>>> maps;
    mutable std::mt19937 generator;
    std::vector<std::pair<int, int>> playerPositions;
    std::vector<std::pair<int, int>> downStairPositions;

    struct Room {
        int x, y, width, height;
        Room(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
        bool isInside(int px, int py) const;
    };

    std::vector<std::vector<Room>> rooms;

    void generateRooms(int floor);
    void connectRooms(int floor);
    void placeStairs(int floor);
    bool isDownStair(int x, int y, int floor) const;
};

#endif