#pragma once

#include "cbattle.h"

#include <optional>
#include <string>

class CEnemy;
class CPlayer
{
public:
    CPlayer();
    void print() const;

    void addGold(const int i);
    void addHp(const int i);
    void dealDamage(const int i, const bool bNoShield = false);
    void addMaxHp(const int i);

    bool isDead() const;

    unsigned int level() const;
    int gold() const;

    void addXp(const int i);
    void levelUp();

    void preBattle(CEnemy* enemy);
    std::optional<CBattle::EWeapons> battleAction(CEnemy* enemy, bool& endRound);
    void postBattle(CEnemy* enemy);

    std::string hpAsString() const;

    unsigned int initiative() const;

private:
    int _hp = 10;
    int _maxHp = 10;
    int _gold = 0;

    unsigned int _level = 1;
    unsigned int _xp = 0;

    unsigned int _initiative = 1;

    unsigned int xpForNextLevel() const;

    static std::string increasedOrDecreased(const int i);
    static std::string lostOrGained(const int i);
};
