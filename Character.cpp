#include "Character.h"

Character::Character(std::wstring name, int health, int attack, int defense) :
    name(name), health(health), attack(attack), defense(defense) {}

std::wstring Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

int Character::getDefense() const {
    return defense;
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}