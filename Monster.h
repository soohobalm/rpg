#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

class Monster : public Character {
public:
    Monster(std::wstring name, std::wstring asciiArt, int health, int attack, int defense, int exp);

    std::wstring getAsciiArt() const;
    int getExp() const;

private:
    std::wstring asciiArt;
    int exp;
};

#endif