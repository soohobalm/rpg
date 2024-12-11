#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <limits>
#include <windows.h>
#include <algorithm>

Battle::Battle(Player& player, Monster& monster) :
    player(player), monster(monster), escape(false) {}

void Battle::start() {
    std::wcout << L"전투 시작!" << std::endl;
    while (!isBattleOver()) {
        showBattleScene();
        playerTurn();
        if (isBattleOver()) break;

        monsterTurn();
        if (isBattleOver()) break;
        endTurn();
    }
    end();
}

void Battle::showBattleScene() const {
    std::wcout << L"========================" << std::endl;
    std::wcout << monster.getAsciiArt() << std::endl;
    std::wcout << monster.getName() << L" (HP: " << monster.getHealth() << L")" << std::endl;
    std::wcout << L"========================" << std::endl;
    std::wcout << player.getName() << L" (HP: " << player.getHealth() << L" LV: " << player.getLevel() << L")" << std::endl;
    std::wcout << L"========================" << std::endl;
}

void Battle::playerTurn() {
    std::wcout << L"1. 공격 2. 방어 3. 도망" << std::endl;
    std::wcout << L"어떤 행동을 취하시겠습니까? ";
    int choice;

    while (!(std::wcin >> choice) || choice < 1 || choice > 3) {
        if (std::cin.fail()) {
            std::wcout << L"잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
        }
        else {
            std::wcout << L"잘못된 선택입니다. 1, 2, 3 중에서 선택해주세요." << std::endl;
        }
        std::wcout << L"어떤 행동을 취하시겠습니까? ";
    }

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    handlePlayerAction(choice);
}

void Battle::monsterTurn() {
    if (monster.isAlive()) {
        std::wcout << monster.getName() << L"의 공격!" << std::endl;
        // max 매크로 정의 해제 (44번째 줄)
#ifdef max
#undef max
#endif
        int damage = std::max(0, monster.getAttack() - player.getDefense());
        player.takeDamage(damage);
        std::wcout << player.getName() << L"에게 " << damage << L"의 데미지를 입혔습니다." << std::endl;

        Sleep(2000);
    }
}

void Battle::handlePlayerAction(int choice) {
    switch (choice) {
    case 1:
        // max 매크로 정의 해제 (52번째 줄)
#ifdef max
#undef max
#endif
        monster.takeDamage(player.attack(monster));
        break;
    case 2:
        player.defend();
        break;
    case 3:
        std::wcout << L"전투에서 도망쳤습니다." << std::endl;
        escape = true;
        break;
    default:
        std::wcout << L"잘못된 선택입니다." << std::endl;
        break;
    }
}

bool Battle::isBattleOver() const {
    return !player.isAlive() || !monster.isAlive() || escape;
}

void Battle::end() {
    if (!monster.isAlive()) {
        player.gainExp(monster.getExp());
    }
    std::wcout << L"전투 종료!" << std::endl;
}

// 턴 종료 시 처리
void Battle::endTurn() {
    player.resetDefense();
}