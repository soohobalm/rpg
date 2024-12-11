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
    std::wcout << L"���� ����!" << std::endl;
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
    std::wcout << L"1. ���� 2. ��� 3. ����" << std::endl;
    std::wcout << L"� �ൿ�� ���Ͻðڽ��ϱ�? ";
    int choice;

    while (!(std::wcin >> choice) || choice < 1 || choice > 3) {
        if (std::cin.fail()) {
            std::wcout << L"�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���." << std::endl;
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
        }
        else {
            std::wcout << L"�߸��� �����Դϴ�. 1, 2, 3 �߿��� �������ּ���." << std::endl;
        }
        std::wcout << L"� �ൿ�� ���Ͻðڽ��ϱ�? ";
    }

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    handlePlayerAction(choice);
}

void Battle::monsterTurn() {
    if (monster.isAlive()) {
        std::wcout << monster.getName() << L"�� ����!" << std::endl;
        // max ��ũ�� ���� ���� (44��° ��)
#ifdef max
#undef max
#endif
        int damage = std::max(0, monster.getAttack() - player.getDefense());
        player.takeDamage(damage);
        std::wcout << player.getName() << L"���� " << damage << L"�� �������� �������ϴ�." << std::endl;

        Sleep(2000);
    }
}

void Battle::handlePlayerAction(int choice) {
    switch (choice) {
    case 1:
        // max ��ũ�� ���� ���� (52��° ��)
#ifdef max
#undef max
#endif
        monster.takeDamage(player.attack(monster));
        break;
    case 2:
        player.defend();
        break;
    case 3:
        std::wcout << L"�������� �����ƽ��ϴ�." << std::endl;
        escape = true;
        break;
    default:
        std::wcout << L"�߸��� �����Դϴ�." << std::endl;
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
    std::wcout << L"���� ����!" << std::endl;
}

// �� ���� �� ó��
void Battle::endTurn() {
    player.resetDefense();
}