#define NOMINMAX
#include <windows.h> // windows.h�� NOMINMAX�� ������ �Ŀ� ���ԵǾ�� �մϴ�.
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <random>
#include <limits>

#include "Interface.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "Battle.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::random_device rd;
    int seed = rd();

    // Dungeon ��ü ���� (24��° ��)
    Dungeon dungeon(5);
    dungeon.generate(seed);

    // Interface ��ü ���� (31��° ��)
    Interface interface(&dungeon);
    Player player(L"�÷��̾�");

    int currentFloor = 0;
    bool playing = true;

    while (playing) {
        interface.drawMap(currentFloor);

        wchar_t input;
        std::wcout << L"Move (w/a/s/d): ";
        while (!(std::wcin >> input) || (input != L'w' && input != L'a' && input != L's' && input != L'd')) {
            std::wcout << L"�߸��� �Է��Դϴ�. w, a, s, d �� �ϳ��� �Է��ϼ���." << std::endl;
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"Move (w/a/s/d): ";
        }

        int dx = 0, dy = 0;
        switch (input) {
        case L'w': dy = -1; break;
        case L's': dy = 1; break;
        case L'a': dx = -1; break;
        case L'd': dx = 1; break;
        }

        if (dx != 0 || dy != 0) {
            if (dungeon.movePlayer(dx, dy, currentFloor, player)) {
                if (dungeon.checkRandomEncounter(currentFloor)) {
                    Monster monster(L"������", L"������", 10, 5, 1, 5);
                    Battle battle(player, monster);
                    battle.start();

                    if (!player.isAlive()) {
                        playing = false;
                    }
                }

                char stairType = dungeon.checkStairs(currentFloor);
                if (stairType == Dungeon::DOWNSTAIR) {
                    if (dungeon.changeFloor(currentFloor, stairType)) {
                        std::pair<int, int> newPlayerPos = dungeon.getPlayerPosition(currentFloor);
                        if (newPlayerPos.first == -1 && newPlayerPos.second == -1) {
                            const int MAX_ATTEMPTS = 100;
                            int attempts = 0;
                            int newX, newY;
                            do {
                                newX = dungeon.getGenerator()() % Dungeon::MAP_WIDTH;
                                newY = dungeon.getGenerator()() % Dungeon::MAP_HEIGHT;
                                attempts++;
                            } while (attempts < MAX_ATTEMPTS && dungeon.isWall(newX, newY, currentFloor));

                            if (attempts == MAX_ATTEMPTS) {
                                std::cerr << "Error: Could not find a valid starting position on the next floor." << std::endl;
                                return false;
                            }
                            dungeon.setPlayerPosition(newX, newY, currentFloor);
                        }
                        interface.drawMap(currentFloor);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        // 82��° ��
        if (currentFloor == 4 || !player.isAlive()) {
            if (currentFloor == 4) {
                std::wcout << L"���� 4���� �����߽��ϴ�! ������ �����մϴ�." << std::endl;
            }
            else {
                std::wcout << L"�÷��̾ ����߽��ϴ�. ������ �����մϴ�." << std::endl;
            }
            playing = false;
        }
    }

    return 0;
}