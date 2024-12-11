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
    void resetDefense(); // ���� ������� ����

private:
    int level;
    int exp;
    int maxExp;
    int baseDefense; // ���� ���� ������ �⺻ ���� ����
};

#endif