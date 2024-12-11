#include "Monster.h"

Monster::Monster(std::wstring name, std::wstring asciiArt, int health, int attack, int defense, int exp) :
    Character(name, health, attack, defense),
    asciiArt(asciiArt), exp(exp) {}

std::wstring Monster::getAsciiArt() const {
    return asciiArt;
}

int Monster::getExp() const {
    return exp;
}