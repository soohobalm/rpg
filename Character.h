#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(std::wstring name, int health, int attack, int defense);

    virtual std::wstring getName() const;
    virtual int getHealth() const;
    virtual int getAttack() const;
    virtual int getDefense() const;
    virtual bool isAlive() const;

    virtual void takeDamage(int damage);

protected:
    std::wstring name;
    int health;
    int attack;
    int defense;
};

#endif