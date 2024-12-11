#include "Player.h"
#include "Character.h"
#include <iostream>
#include <algorithm>

namespace PlayerConst {
    const int INITIAL_HEALTH = 100;
    const int INITIAL_ATTACK = 10;
    const int INITIAL_DEFENSE = 5;
    const int INITIAL_LEVEL = 1;
    const int INITIAL_EXP = 0;
    const int EXP_PER_LEVEL = 10;
}

Player::Player(std::wstring name) :
    Character(name, PlayerConst::INITIAL_HEALTH, PlayerConst::INITIAL_ATTACK, PlayerConst::INITIAL_DEFENSE),
    level(PlayerConst::INITIAL_LEVEL),
    exp(PlayerConst::INITIAL_EXP),
    maxExp(PlayerConst::EXP_PER_LEVEL) {
    baseDefense = PlayerConst::INITIAL_DEFENSE;
}

int Player::attack(Character& target) {
    // max 매크로 정의 해제 (28번째 줄)
#ifdef max
#undef max
#endif
    int damage = std::max(0, attack - target.getDefense());
    target.takeDamage(damage);
    std::wcout << name << L"의 공격! " << target.getName() << L"에게 " << damage << L"의 데미지를 입혔습니다." << std::endl;
    return damage;
}

void Player::defend() {
    std::wcout << name << L"이(가) 방어 태세를 취했습니다." << std::endl;
    // 방어 로직: 일시적으로 방어력 증가
    defense += 3;
    std::wcout << name << L"의 방어력이 일시적으로 증가했습니다." << std::endl;
}

void Player::gainExp(int exp) {
    this->exp += exp;
    std::wcout << name << L"이(가) " << exp << L"의 경험치를 획득했습니다." << std::endl;
    while (this->exp >= maxExp) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    exp -= maxExp;
    maxExp *= 2;
    attack += 2;
    defense += 1; // 53번째 줄
    baseDefense = defense;
    health = PlayerConst::INITIAL_HEALTH + (level - 1) * 10;
    std::wcout << name << L"이(가) 레벨업했습니다! 현재 레벨: " << level << std::endl;
}

int Player::getLevel() const {
    return level;
}

int Player::getExp() const {
    return exp;
}

void Player::resetDefense() {
    defense = baseDefense;
}