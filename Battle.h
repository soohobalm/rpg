#ifndef BATTLE_H
#define BATTLE_H

#include <windows.h>

// Player�� Monster Ŭ���� ���� ����
class Player;
class Monster;

class Battle {
public:
    Battle(Player& player, Monster& monster);
    void start();

private:
    Player& player;
    Monster& monster;
    bool escape;

    void showBattleScene() const;
    void playerTurn();
    void monsterTurn();
    void handlePlayerAction(int choice);
    bool isBattleOver() const;
    void end();
    void endTurn(); // �� ���� �� ���� ���� ���� ó���ϴ� �Լ�
};

#endif