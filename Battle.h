#ifndef BATTLE_H
#define BATTLE_H

#include <windows.h>

// Player와 Monster 클래스 전방 선언
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
    void endTurn(); // 턴 종료 시 방어력 복구 등을 처리하는 함수
};

#endif