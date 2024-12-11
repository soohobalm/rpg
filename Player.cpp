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
    // max ��ũ�� ���� ���� (28��° ��)
#ifdef max
#undef max
#endif
    int damage = std::max(0, attack - target.getDefense());
    target.takeDamage(damage);
    std::wcout << name << L"�� ����! " << target.getName() << L"���� " << damage << L"�� �������� �������ϴ�." << std::endl;
    return damage;
}

void Player::defend() {
    std::wcout << name << L"��(��) ��� �¼��� ���߽��ϴ�." << std::endl;
    // ��� ����: �Ͻ������� ���� ����
    defense += 3;
    std::wcout << name << L"�� ������ �Ͻ������� �����߽��ϴ�." << std::endl;
}

void Player::gainExp(int exp) {
    this->exp += exp;
    std::wcout << name << L"��(��) " << exp << L"�� ����ġ�� ȹ���߽��ϴ�." << std::endl;
    while (this->exp >= maxExp) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    exp -= maxExp;
    maxExp *= 2;
    attack += 2;
    defense += 1; // 53��° ��
    baseDefense = defense;
    health = PlayerConst::INITIAL_HEALTH + (level - 1) * 10;
    std::wcout << name << L"��(��) �������߽��ϴ�! ���� ����: " << level << std::endl;
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