#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    Player(std::wstring name);

    int attack(Character& target);
    void defend();
    void gainExp(int exp);
    void levelUp();
    int getLevel() const;
    int getExp() const;
    void resetDefense(); // 방어력 원래대로 복구

private:
    int level;
    int exp;
    int maxExp;
    int baseDefense; // 방어력 증가 이전의 기본 방어력 저장
};

#endif