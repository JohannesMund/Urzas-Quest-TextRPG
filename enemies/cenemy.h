#pragma once

#include "cbattle.h"

#include <optional>
#include <string>

class CEnemy
{
public:
    CEnemy();

    virtual ~CEnemy()
    {
    }

    virtual void preBattle();
    virtual void preBattleAction();
    virtual void battleAction(bool& endRound);
    virtual void postBattleAction();
    virtual void postBattle();
    virtual void spoilsOfWar() const;

    virtual std::string name() const;
    std::string weapon() const;

    unsigned int level() const;
    virtual unsigned int damage() const;
    unsigned int initiative() const;

    bool isDead() const;
    bool hasExtendedWeaponChoice() const;

    void addHp(const int i);
    void dealDamage(const int i);
    unsigned int hp() const;

    std::optional<CBattle::EWeapons> peek();

    void printBossBattleHeader() const;

protected:
    unsigned int _level;
    int _hp;
    unsigned int _initiative;
    unsigned int _count;

    bool _extendedWeaponChoice = false;

    std::string _name;
    std::string _weapon;

    static unsigned int basicXP(const unsigned int level);

private:
    std::optional<CBattle::EWeapons> _battleDecision;
};
